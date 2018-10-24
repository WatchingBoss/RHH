#include "../inc/bird.hpp"

#include <cstdio>

namespace Engine
{
Bird::Bird( gameDataRef data )
    : m_Data( data ), m_AnimationIterator( 0 ), m_BirdState( STILL ), m_Rotation( 0 ) {
	FillTextures( );
	m_BirdSprite.setTexture( m_BirdAnimation.at( m_AnimationIterator ) );

	m_BirdSprite.setOrigin( m_BirdSprite.getGlobalBounds( ).width / 2,
	                        m_BirdSprite.getGlobalBounds( ).height / 2 );

	m_BirdSprite.setPosition( 100.f,
	                          static_cast<float>( m_Data->window.getSize( ).y / 3 ) );
}

Bird::~Bird( ) {}

void Bird::Animate( const float frame_time ) {
	const int frames_number = m_BirdAnimation.size( );
	int &     a_iter        = m_AnimationIterator;  // Just make it shorter
	if ( m_Clock.getElapsedTime( ).asSeconds( ) >
	     BIRD_ANIMATION_DURATION / frames_number ) {
		a_iter < frames_number - 1 ? ++a_iter : a_iter = 0;

		m_BirdSprite.setTexture( m_BirdAnimation.at( a_iter ) );

		m_Clock.restart( );
	}
}

void Bird::Update( const float frame_time ) {
	if ( m_BirdState == FALLING || m_BirdState == FLYING ) {
		if ( m_BirdState == FALLING ) {
			m_BirdSprite.move( 0, GRAVITY * frame_time );

			if ( m_Rotation < 25.f ) m_Rotation += ROTATION_SPEED * frame_time;
		} else {
			m_BirdSprite.move( 0, -FLYING_SPEED * frame_time );

			if ( m_Rotation > -25.f ) m_Rotation -= ROTATION_SPEED * frame_time;
		}

		m_BirdSprite.setRotation( m_Rotation );

		if ( m_MovementClock.getElapsedTime( ).asSeconds( ) > FLYING_DURATION ) {
			m_MovementClock.restart( );
			m_BirdState = FALLING;
		}
	}
}

void Bird::Tap( ) {
	m_MovementClock.restart( );
	m_BirdState = FLYING;
}

void Bird::Draw( ) { m_Data->window.draw( m_BirdSprite ); }

/*** Private methods ***/

void Bird::FillTextures( ) {
	for ( int i = 0; i < 4; ++i ) {
		constexpr size_t name_size       = 15;
		char             name[name_size] = { 0 };
		std::snprintf( name, name_size, "bird_frame_%d", i + 1 );
		m_BirdAnimation.at( i ) = m_Data->asset.GetTexture( name );
	}
}

}  // namespace Engine
