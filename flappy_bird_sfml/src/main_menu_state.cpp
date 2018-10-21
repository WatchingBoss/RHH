#include "../inc/main_menu_state.hpp"
#include "../inc/game_state.hpp"

#include <iostream>
#include <sstream>
#include <memory>

namespace Engine
{
void MainMenuState::AddTexture( const char *tex_name, const char *file_path,
                                sf::Sprite &sprite, const float x, const float y ) {
	m_Data->asset.LoadTexture( tex_name, file_path );
	sprite.setTexture( m_Data->asset.GetTexture( tex_name ) );
	if ( x && y )
		sprite.setPosition( x - sprite.getGlobalBounds( ).width / 2,
		                    y - sprite.getGlobalBounds( ).height / 2 );
	m_Sprites.push_back( sprite );
}

MainMenuState::MainMenuState( gameDataRef data ) : m_Data( data ) {}
MainMenuState::~MainMenuState( ) {}

void MainMenuState::Init( ) {
	AddTexture( "main_menu_bg", MAIN_MENU_BG_FILE_PATH, m_Bg );
	AddTexture( "game_title", GAME_TITLE_FILE_PATH, m_Title, MW_WIDTH / 2, MW_HEIGHT / 7 );
	AddTexture( "play_button", PLAY_BUTTON_FILE_PATH, m_PlayButton, MW_WIDTH / 2,
	            MW_HEIGHT / 2 );
}

void MainMenuState::HandleInput( ) {
	sf::Event event;
	while ( m_Data->window.pollEvent( event ) ) {
		if ( sf::Event::Closed == event.type ) m_Data->window.close( );
		if ( m_Data->input.IsSpriteClicked( m_PlayButton, sf::Mouse::Left,
		                                    m_Data->window ) )
			m_Data->machine.AddState(std::make_unique<GameState>(m_Data), true);
	}
}

void MainMenuState::Update( float frame_time ) {}

void MainMenuState::Draw( float frame_time ) {
	m_Data->window.clear( );

	for ( sf::Sprite sprite : m_Sprites ) m_Data->window.draw( sprite );

	m_Data->window.display( );
}

}  // namespace Engine
