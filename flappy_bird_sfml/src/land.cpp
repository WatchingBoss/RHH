#include "../inc/land.hpp"

namespace Engine
{
Land::Land( gameDataRef data ) : m_Data( data ) {
	sf::Sprite land_1( m_Data->asset.GetTexture( "land" ) );
	sf::Sprite land_2( m_Data->asset.GetTexture( "land" ) );

	land_1.setPosition( 0, m_Data->window.getSize( ).y - land_1.getGlobalBounds( ).height );
	land_2.setPosition( land_1.getGlobalBounds( ).width,
	                    m_Data->window.getSize( ).y - land_1.getGlobalBounds( ).height );

	m_LandSprites.at( 0 ) = land_1;
	m_LandSprites.at( 1 ) = land_2;
}

Land::~Land( ) {}

void Land::MoveLand( const float frame_time ) {
	for ( sf::Sprite &land : m_LandSprites ) {
		float movement = PIPE_MOVEMENT_SPEED * frame_time;
		land.move( -movement, 0.f );

		if ( land.getPosition( ).x < -land.getGlobalBounds( ).width ) {
			sf::Vector2f pos( static_cast<float>( m_Data->window.getSize( ).x ),
			                  static_cast<float>( land.getPosition( ).y ) );
			land.setPosition( pos );
		}
	}
}

void Land::DrawLand( ) {
	for ( sf::Sprite &land : m_LandSprites ) m_Data->window.draw( land );
}
}  // namespace Engine
