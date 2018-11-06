#include "../inc/sounds.hpp"

#include <iostream>

namespace Engine
{
Sound::Sound( ) {
	LoadBuffer( );
	SetSounds( );
}

Sound::~Sound( ) {}

/*** Private methods ***/
void Sound::LoadBuffer( ) {
	if ( !m_HitBuffer.loadFromFile( HIT_SOUND_FILE_PATH ) )
		std::cout << "Hit wav not loaded";
	if ( !m_PointBuffer.loadFromFile( POINT_SOUND_FILE_PATH ) )
		std::cout << "Point wav not loaded";
	if ( !m_WingBuffer.loadFromFile( WING_SOUND_FILE_PATH ) )
		std::cout << "Wing wav not loaded";
}

void Sound::SetSounds( ) {
	m_HitSound.setBuffer( m_HitBuffer );
	m_PointSound.setBuffer( m_PointBuffer );
	m_WingSound.setBuffer( m_WingBuffer );
}

}  // namespace Engine
