#include "../inc/game_over_state.hpp"

#include <iostream>
#include <sstream>

namespace Engine
{
GameOverState::GameOverState( gameDataRef data ) : m_Data( data ) {}
GameOverState::~GameOverState( ) {}

void GameOverState::Init( ) {
	const char *game_over_bg = "game_over_state_bg";
	m_Data->asset.LoadTexture( game_over_bg, GAME_OVER_BG_FILE_PATH );
	m_Bg.setTexture( m_Data->asset.GetTexture( game_over_bg ) );
}

void GameOverState::HandleInput( ) {
	sf::Event event;
	while ( m_Data->window.pollEvent( event ) )
		if ( sf::Event::Closed == event.type ) m_Data->window.close( );
}

void GameOverState::Update( float frame_time ) {}

void GameOverState::Draw( float frame_time ) {
	m_Data->window.clear( );
	m_Data->window.draw( m_Bg );
	m_Data->window.display( );
}

}  // namespace Engine
