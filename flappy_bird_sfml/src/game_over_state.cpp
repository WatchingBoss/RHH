#include "../inc/game_over_state.hpp"
#include "../inc/game_state.hpp"

#include <iostream>
#include <sstream>

namespace Engine
{
GameOverState::GameOverState( gameDataRef data ) : m_Data( data ) {}
GameOverState::~GameOverState( ) {}

void GameOverState::Init( ) {
	sf::Sprite bg, title, body, retry;

	AddTexture( "game_over_state_bg", GAME_OVER_BG_FILE_PATH, bg );
	AddTexture( "game_over_state_title", GAME_OVER_TITLE_FILE_PATH, title );
	AddTexture( "game_over_state_body", GAME_OVER_BODY_FILE_PATH, body );
	AddTexture( "game_over_state_retry", PLAY_BUTTON_FILE_PATH, retry );

	sf::Vector2u win_dim = m_Data->window.getSize( );
	float        win_x   = static_cast<float>( win_dim.x );
	float        win_y   = static_cast<float>( win_dim.y );

	body.setPosition( win_x / 2 - body.getGlobalBounds( ).width / 2,
	                  win_y / 2 - body.getGlobalBounds( ).height / 2 );
	title.setPosition( win_x / 2 - title.getGlobalBounds( ).width / 2,
	                   body.getPosition( ).y - title.getGlobalBounds( ).height * 1.3f );
	retry.setPosition( win_x / 2 - retry.getGlobalBounds( ).width / 2,
	                   body.getPosition( ).y + retry.getGlobalBounds( ).height * 2.f );

	m_Sprites.at( 0 ) = bg;
	m_Sprites.at( 1 ) = title;
	m_Sprites.at( 2 ) = body;
	m_Sprites.at( 3 ) = retry;
}

void GameOverState::HandleInput( ) {
	sf::Event event;
	while ( m_Data->window.pollEvent( event ) ) {
		if ( sf::Event::Closed == event.type ) m_Data->window.close( );
		if ( m_Data->input.IsSpriteClicked( m_Sprites.at( 3 ), sf::Mouse::Left,
		                                    m_Data->window ) )
			m_Data->machine.AddState( std::make_unique<GameState>( m_Data ), true );
		else if ( sf::Event::KeyPressed == event.type )
			if ( event.key.code == sf::Keyboard::Space )
				m_Data->machine.AddState( std::make_unique<GameState>( m_Data ), true );
	}
}

void GameOverState::Update( float frame_time ) {}

void GameOverState::Draw( float frame_time ) {
	m_Data->window.clear( );

	for ( const sf::Sprite &sprite : m_Sprites ) m_Data->window.draw( sprite );

	m_Data->window.display( );
}

/*** Private methods ***/

void GameOverState::AddTexture( const char *tex_name, const char *file_path,
                                sf::Sprite &sprite ) {
	LoadTexture( tex_name, file_path );
	sprite.setTexture( m_Data->asset.GetTexture( tex_name ) );
}

void GameOverState::LoadTexture( const char *tex_name, const char *file_path ) {
	m_Data->asset.LoadTexture( tex_name, file_path );
}

void GameOverState::LoadFont( const char *font_name, const char *file_path ) {
	m_Data->asset.LoadFont( font_name, file_path );
}

}  // namespace Engine
