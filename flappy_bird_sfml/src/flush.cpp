#include "../inc/flash.hpp"

namespace Engine
{
Flash::Flash( gameDataRef data )
    : m_Data( data ), m_Red( 250 ), m_Green( 250 ), m_Blue( 250 ), m_Alpha( 0 ),
      m_FlashOn( true ) {
	m_Shape = sf::RectangleShape( sf::Vector2f( m_Data->window.getSize( ) ) );
	m_Shape.setFillColor( sf::Color( m_Red, m_Green, m_Blue, m_Alpha ) );
}

Flash::~Flash( ) {}

void Flash::Show( const float frame_time ) {
	int alpha = m_Shape.getFillColor( ).a;

	if ( m_FlashOn ) {
		alpha += static_cast<uint8>( FLASH_SPEED * frame_time );
		if ( alpha >= 255 ) m_FlashOn = false;
	} else if ( !m_FlashOn ) {
		alpha -= static_cast<uint8>( FLASH_SPEED * frame_time );
		if ( alpha < 0 ) alpha = 0;
	}

	m_Alpha = static_cast<uint8>( alpha );
	m_Shape.setFillColor( sf::Color( m_Red, m_Green, m_Blue, m_Alpha ) );
}

void Flash::Draw( ) { m_Data->window.draw( m_Shape ); }
}  // namespace Engine
