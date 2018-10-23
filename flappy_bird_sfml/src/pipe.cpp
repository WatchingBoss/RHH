#include "../inc/definitions.h"
#include "../inc/pipe.hpp"

namespace Engine
{
Pipe::Pipe( gameDataRef data ) : m_Data( data ), m_Gen( m_Device( ) ) {
	int land_height = m_Data->asset.GetTexture( "land" ).getSize( ).y;
	std::uniform_int_distribution<> range( 0, land_height );
	m_Range = range;
}

Pipe::~Pipe( ) {}

void Pipe::Spawn( ) {
	float y_offset = PipeSpawnOffsetY( );

	SpawnBottomPipe( y_offset );
	SpawnTopPipe( y_offset );
	SpawnInvisiblePipe( y_offset );

	SpawnScoringPipe( );
}

void Pipe::Move( const float frame_time ) {
	const float movement = -PIPE_MOVEMENT_SPEED * frame_time;

	for ( sf::Sprite &pipe : m_PipeSprites ) {
		pipe.move( movement, 0 );
		if ( pipe.getPosition( ).x < -pipe.getGlobalBounds( ).width )
			m_PipeSprites.pop_front( );
	}

	for ( sf::Sprite &pipe : m_ScoreSprites ) pipe.move( movement, 0 );
}

void Pipe::Draw( ) {
	for ( sf::Sprite &pipe : m_PipeSprites ) m_Data->window.draw( pipe );
}

/*** Private methods ***/

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

void Pipe::SpawnScoringPipe( ) {
	sf::Sprite sprite( m_Data->asset.GetTexture( "score_pipe" ) );
	sprite.setPosition( static_cast<float>( m_Data->window.getSize( ).x ), 0 );

	m_ScoreSprites.push_back( sprite );
}

}  // namespace Engine
