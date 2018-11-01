#include "../inc/game_over_state.hpp"
#include "../inc/game_state.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif

namespace Engine
{
GameState::GameState( gameDataRef data )
    : m_Data( data ), m_GameState( READY ), m_BirdOnLand( false ), m_Score( 0 ) {}
GameState::~GameState( ) {
	delete ( m_Pipe );
	delete ( m_Land );
	delete ( m_Bird );
	delete ( m_Flash );
	delete ( m_Hud );
	delete ( m_Sound );
}

void GameState::Init( ) {
	AddTexture( "game_state_bg", GAME_BG_FILE_PATH, m_Bg );
	LoadTexture( "pipe_up", PIPE_UP_FILE_PATH );
	LoadTexture( "pipe_down", PIPE_DOWN_FILE_PATH );
	LoadTexture( "land", LAND_FILE_PATH );
	LoadTexture( "score_pipe", INVISIBLE_PIPE_FILE_PATH );

	LoadTexture( "bird_frame_1", BIRD_FRAME_1_FILE_PATH );
	LoadTexture( "bird_frame_2", BIRD_FRAME_2_FILE_PATH );
	LoadTexture( "bird_frame_3", BIRD_FRAME_3_FILE_PATH );
	LoadTexture( "bird_frame_4", BIRD_FRAME_4_FILE_PATH );

	LoadFont( "flappy_font", FLAPPY_FONT_FILE_PATH );

	m_Pipe  = new Pipe( m_Data );
	m_Land  = new Land( m_Data );
	m_Bird  = new Bird( m_Data );
	m_Flash = new Flash( m_Data );
	m_Hud   = new Hud( m_Data );
	m_Sound = new Sound( );

	m_Hud->UpdateScore( m_Score );

	m_Collision = Collision( );
}

void GameState::HandleInput( ) {
	sf::Event event;
	while ( m_Data->window.pollEvent( event ) ) {
		if ( sf::Event::Closed == event.type ) m_Data->window.close( );
		if ( sf::Event::KeyPressed == event.type )
			if ( event.key.code == sf::Keyboard::Space ) {
				if ( m_GameState != GAMEOVER ) {
					m_Bird->Tap( );
					m_Sound->Wing( );
					if ( m_GameState != PLAYING ) m_GameState = PLAYING;
				}
			} else if ( event.key.code == sf::Keyboard::Escape )
				m_Data->window.close( );
	}
}

void GameState::Update( float frame_time ) {
	if ( m_GameState == GAMEOVER ) {
		m_Flash->Show( frame_time );
		if ( !m_BirdOnLand )
			CheckCollision( );
		else if ( m_Clock.getElapsedTime( ).asSeconds( ) > GAME_OVER_DELAY ) {
			UpdateBestScoreFile( );

			m_Data->machine.AddState(
			    std::make_unique<GameOverState>( m_Data, m_Score ) );
		}
	}

	if ( m_GameState != GAMEOVER ) {
		m_Land->Move( frame_time );
		m_Bird->Animate( frame_time );

		if ( CheckCollision( ) ) {
			m_Sound->Hit( );
			m_GameState = GAMEOVER;
		}
		if ( CheckScore( ) ) {
			m_Sound->Point( );
			UpdateScore( );
		}
	}

	if ( m_GameState == PLAYING ) {
		m_Pipe->Move( frame_time );

		if ( m_Clock.getElapsedTime( ).asSeconds( ) > PIPE_SPAWN_FREQ ) {
			m_Pipe->Spawn( );
			m_Clock.restart( );
		}
	}

	m_Bird->Update( frame_time );
}

void GameState::Draw( float frame_time ) {
	m_Data->window.clear( );

	m_Data->window.draw( m_Bg );
	m_Pipe->Draw( );
	m_Land->Draw( );
	m_Bird->Draw( );
	m_Flash->Draw( );
	m_Hud->Draw( );

	m_Data->window.display( );
}

/*** Private methods ***/

bool GameState::CheckScore( ) {
	if ( m_GameState == GAMEOVER ) return false;

	const sf::Sprite bird_sprite = m_Bird->GetSprite( );

	for ( const sf::Sprite &pipe : m_Pipe->GetScoreSprites( ) )
		if ( m_Collision.CheckSpritesCollision( bird_sprite, pipe ) ) {
			m_Pipe->PopScorePipe( );
			return true;
		}

	return false;
}

bool GameState::CheckCollision( ) {
	const sf::Sprite bird_sprite = m_Bird->GetSprite( );

	for ( const sf::Sprite &land : m_Land->GetSprites( ) )
		if ( m_Collision.CheckSpritesCollision( bird_sprite, BIRD_COLLISION_SCALE, land,
		                                        1.f ) ) {
			m_Clock.restart( );
			m_Bird->StopTheBird( );
			m_BirdOnLand = true;
			return true;
		}

	for ( const sf::Sprite &pipe : m_Pipe->GetSprites( ) )
		if ( m_Collision.CheckSpritesCollision( bird_sprite, BIRD_COLLISION_SCALE, pipe,
		                                        1.f ) )
			return true;

	return false;
}

void GameState::UpdateScore( ) {
	++m_Score;
	m_Hud->UpdateScore( m_Score );
}

void GameState::CheckDataDirectory( ) {
#ifdef _WIN32
	DWORD dwAttrib = GetFileAttributes( DATA_DIRECTORY );
	if ( dwAttrib == INVALID_FILE_ATTRIBUTES )
		if ( !CreateDirectoryA( DATA_DIRECTORY, NULL ) )
			printf( "Cannot create directory %s\n", DATA_DIRECTORY );
#else
	DIR *dir = opendir( DATA_DIRECTORY );
	if ( !dir )
		if ( !mkdir( DATA_DIRECTORY, S_IRWXU | S_IRWXG | S_IRWXO ) )
			printf( "Cannot create directory %s\n", DATA_DIRECTORY );
	dir.close( );
#endif
}

void GameState::UpdateBestScoreFile( ) {
	CheckDataDirectory( );

	uint32       temp_best_score = 0;
	std::fstream file( BEST_SCORE_FILE_PATH,
	                   std::ios::in | std::ios::out | std::ios::binary );
	if ( file.is_open( ) ) {
		file.read( reinterpret_cast<char *>( &temp_best_score ), sizeof temp_best_score );
		if ( m_Score > temp_best_score ) {
			file.seekp( 0 );
			file.write( reinterpret_cast<char *>( &m_Score ), sizeof m_Score );
		}
		file.close( );
	} else {
		std::fstream file( BEST_SCORE_FILE_PATH, std::ios::out | std::ios::binary );
		file.write( reinterpret_cast<char *>( &m_Score ), sizeof m_Score );
		file.close( );
	}
}

void GameState::AddTexture( const char *tex_name, const char *file_path,
                            sf::Sprite &sprite ) {
	LoadTexture( tex_name, file_path );
	sprite.setTexture( m_Data->asset.GetTexture( tex_name ) );
}

void GameState::LoadTexture( const char *tex_name, const char *file_path ) {
	m_Data->asset.LoadTexture( tex_name, file_path );
}

void GameState::LoadFont( const char *font_name, const char *file_path ) {
	m_Data->asset.LoadFont( font_name, file_path );
}

}  // namespace Engine
