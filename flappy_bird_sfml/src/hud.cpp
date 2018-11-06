#include "../inc/hud.hpp"

#include <string>

namespace Engine
{
Hud::Hud( gameDataRef data ) : m_Data( data ) {
	m_ScoreText.setFont( m_Data->asset.GetFont( "flappy_font" ) );

	m_ScoreText.setString( "0" );
	m_ScoreText.setCharacterSize( 100 );
	m_ScoreText.setFillColor( sf::Color::Magenta );

	const sf::FloatRect score_rec = m_ScoreText.getGlobalBounds( );
	m_ScoreText.setOrigin( score_rec.width / 2, score_rec.height / 2 );

	const sf::Vector2u win_dim = m_Data->window.getSize( );
	m_ScoreText.setPosition( static_cast<float>( win_dim.x / 2 ),
	                         static_cast<float>( win_dim.y / 10 ) );
}

Hud::~Hud( ) {}

void Hud::Draw( ) { m_Data->window.draw( m_ScoreText ); }

void Hud::UpdateScore( uint32 score ) {
	m_ScoreText.setString( std::to_string( score ) );
}
}  // namespace Engine
