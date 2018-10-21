#include "../inc/pipe.hpp"
#include "../inc/definitions.h"

namespace Engine
{
Pipe::Pipe( gameDataRef data ) : m_Data( data ), m_Gen( m_Device( ) ) {
	int land_height = m_Data->asset.GetTexture( "land" ).getSize( ).y;
	std::uniform_int_distribution<> range(0, land_height);
	m_Range = range;
}

Pipe::~Pipe( ) {}

void Pipe::SpawnPipes( ) {
	float y_offset = PipeSpawnOffsetY( );

	SpawnBottomPipe( y_offset );
	SpawnTopPipe( y_offset );
	SpawnInvisiblePipe( y_offset );
}

void Pipe::SpawnBottomPipe( const float y_offset ) {
	sf::Sprite sprite( m_Data->asset.GetTexture( "pipe_up" ) );
	sprite.setPosition( static_cast<float>( m_Data->window.getSize( ).x ),
	                    m_Data->window.getSize( ).y - sprite.getGlobalBounds( ).height -
	                        y_offset );
	m_PipeSprites.push_back( sprite );
}

void Pipe::SpawnTopPipe( const float y_offset ) {
	sf::Sprite sprite( m_Data->asset.GetTexture( "pipe_down" ) );
	sprite.setPosition( static_cast<float>( m_Data->window.getSize( ).x ), -y_offset );
	m_PipeSprites.push_back( sprite );
}

void Pipe::SpawnInvisiblePipe( const float y_offset ) {
	sf::Sprite sprite( m_Data->asset.GetTexture( "pipe_up" ) );
	sprite.setPosition( static_cast<float>( m_Data->window.getSize( ).x ),
	                    m_Data->window.getSize( ).y - sprite.getGlobalBounds( ).height -
	                        y_offset );

	sprite.setColor( sf::Color( 0, 0, 0, 0 ) );

	m_PipeSprites.push_back( sprite );
}

void Pipe::MovePipes( const float frame_time ) {
	int i = 0;
	for ( sf::Sprite &pipe : m_PipeSprites ) {
		sf::Vector2f pos      = pipe.getPosition( );
		float        movement = PIPE_MOVEMENT_SPEED * frame_time;
		pipe.move( -movement, 0 );

		if ( pos.x < -pipe.getGlobalBounds( ).width ) m_PipeSprites.pop_front( );
	}
}

void Pipe::DrawPipes( ) {
	for ( sf::Sprite &pipe : m_PipeSprites ) m_Data->window.draw( pipe );
}

}  // namespace Engine
