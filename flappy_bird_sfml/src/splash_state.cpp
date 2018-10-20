#include "../inc/splash_state.hpp"
#include "../inc/main_menu_state.hpp"

#include <iostream>
#include <sstream>

namespace Engine
{
SplashState::SplashState( gameDataRef data ) : m_Data( data ) {}
SplashState::~SplashState( ) {}

void SplashState::Init( ) {
	const char *splash_bg = "splash_state_bg";
	m_Data->asset.LoadTexture( splash_bg, SPLASH_BG_FILE_PATH );
	m_Bg.setTexture( m_Data->asset.GetTexture( splash_bg ) );
}

void SplashState::HandleInput( ) {
	sf::Event event;
	while ( m_Data->window.pollEvent( event ) )
		if ( sf::Event::Closed == event.type ) m_Data->window.close( );
}

void SplashState::Update( float frame_time ) {
	if ( m_Clock.getElapsedTime( ).asSeconds( ) > SPLASH_STATE_SHOW_TIME )
		m_Data->machine.AddState( std::make_unique<MainMenuState>( m_Data ), true );
}

void SplashState::Draw( float frame_time ) {
	m_Data->window.clear( );
	m_Data->window.draw( m_Bg );
	m_Data->window.display( );
}

}  // namespace Engine
