#include "../inc/game_state.hpp"
#include "../inc/game_over_state.hpp"

#include <iostream>
#include <memory>
#include <sstream>

namespace Engine
{
GameState::GameState( gameDataRef data ) : m_Data( data ), m_GameOver( false ) {}
GameState::~GameState( ) {}

void GameState::Init( ) {
	AddTexture( "game_state_bg", GAME_BG_FILE_PATH, m_Bg );
	LoadTexture( "pipe_up", PIPE_UP_FILE_PATH );
	LoadTexture( "pipe_down", PIPE_DOWN_FILE_PATH );
	LoadTexture( "land", LAND_FILE_PATH );

	LoadTexture( "bird_frame_1", BIRD_FRAME_1_FILE_PATH );
	LoadTexture( "bird_frame_2", BIRD_FRAME_2_FILE_PATH );
	LoadTexture( "bird_frame_3", BIRD_FRAME_3_FILE_PATH );
	LoadTexture( "bird_frame_4", BIRD_FRAME_4_FILE_PATH );

	m_Pipe = new Pipe( m_Data );
	m_Land = new Land( m_Data );
	m_Bird = new Bird( m_Data );
}

void GameState::HandleInput( ) {
	sf::Event event;
	while ( m_Data->window.pollEvent( event ) ) {
		if ( sf::Event::Closed == event.type ) m_Data->window.close( );
		if ( sf::Event::KeyPressed == event.type )
			if ( event.key.code == sf::Keyboard::Space ) m_Bird->Tap( );
	}
}

void GameState::Update( float frame_time ) {
	if ( m_GameOver )
		m_Data->machine.AddState( std::make_unique<GameOverState>( m_Data ), true );

	m_Pipe->MovePipes( frame_time );
	m_Land->MoveLand( frame_time );

	if ( m_Clock.getElapsedTime( ).asSeconds( ) > PIPE_SPAWN_FREQ ) {
		m_Pipe->SpawnPipes( );

		m_Clock.restart( );
	}

	m_Bird->Animate( frame_time );
	m_Bird->Update( frame_time );
}

void GameState::Draw( float frame_time ) {
	m_Data->window.clear( );

	m_Data->window.draw( m_Bg );
	m_Pipe->DrawPipes( );
	m_Land->DrawLand( );
	m_Bird->DrawBird( );

	m_Data->window.display( );
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
