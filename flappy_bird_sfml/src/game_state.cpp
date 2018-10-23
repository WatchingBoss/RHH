#include "../inc/game_over_state.hpp"
#include "../inc/game_state.hpp"

#include <iostream>
#include <memory>
#include <sstream>

namespace Engine
{
GameState::GameState( gameDataRef data )
    : m_Data( data ), m_GameState( READY ), m_BirdOnLand( false ) {}
GameState::~GameState( ) {
	delete ( m_Pipe );
	delete ( m_Land );
	delete ( m_Bird );
	delete ( m_Flash );
}

void GameState::Init( ) {
	AddTexture( "game_state_bg", GAME_BG_FILE_PATH, m_Bg );
	LoadTexture( "pipe_up", PIPE_UP_FILE_PATH );
	LoadTexture( "pipe_down", PIPE_DOWN_FILE_PATH );
	LoadTexture( "land", LAND_FILE_PATH );

	LoadTexture( "bird_frame_1", BIRD_FRAME_1_FILE_PATH );
	LoadTexture( "bird_frame_2", BIRD_FRAME_2_FILE_PATH );
	LoadTexture( "bird_frame_3", BIRD_FRAME_3_FILE_PATH );
	LoadTexture( "bird_frame_4", BIRD_FRAME_4_FILE_PATH );

	m_Pipe  = new Pipe( m_Data );
	m_Land  = new Land( m_Data );
	m_Bird  = new Bird( m_Data );
	m_Flash = new Flash( m_Data );

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
					if ( m_GameState != PLAYING ) m_GameState = PLAYING;
				}
			}
	}
}

void GameState::Update( float frame_time ) {
	if ( m_GameState == GAMEOVER ) {
		m_Flash->Show( frame_time );
		if ( !m_BirdOnLand ) {
			m_Bird->Animate( frame_time );
			CheckCollision( );
		}
	}
	//		m_Data->machine.AddState( std::make_unique<GameOverState>( m_Data ), true );

	if ( m_GameState != GAMEOVER ) {
		m_Land->Move( frame_time );
		m_Bird->Animate( frame_time );

		if ( CheckCollision( ) ) { m_GameState = GAMEOVER; }
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

	m_Data->window.display( );
}

/*** Private methods ***/

bool GameState::CheckCollision( ) {
	for ( const sf::Sprite &land : m_Land->GetSprites( ) )
		if ( m_Collision.ChechSpritesCollision( m_Bird->GetSprite( ),
		                                        BIRD_COLLISION_SCALE, land, 1.f ) ) {
			m_Bird->StopTheBird( );
			m_BirdOnLand = true;
			return true;
		}

	for ( const sf::Sprite &pipe : m_Pipe->GetSprites( ) )
		if ( m_Collision.ChechSpritesCollision( m_Bird->GetSprite( ),
		                                        BIRD_COLLISION_SCALE, pipe, 1.f ) )
			return true;

	return false;
}

void GameState::AddTexture( const char *tex_name, const char *file_path,
                            sf::Sprite &sprite ) {
	m_Data->asset.LoadTexture( tex_name, file_path );
	sprite.setTexture( m_Data->asset.GetTexture( tex_name ) );
}

void GameState::LoadTexture( const char *tex_name, const char *file_path ) {
	m_Data->asset.LoadTexture( tex_name, file_path );
}

}  // namespace Engine
