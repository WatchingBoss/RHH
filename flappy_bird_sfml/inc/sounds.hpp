#ifndef MY_SOUNDS_HPP
#define MY_SOUNDS_HPP

#include <SFML/Audio.hpp>

#include "definitions.h"

namespace Engine
{
class Sound {
  public:
	Sound( );
	~Sound( );

	inline void Hit( ) { m_HitSound.play( ); }
	inline void Point( ) { m_PointSound.play( ); }
	inline void Wing( ) { m_WingSound.play( ); }

  private:
	sf::SoundBuffer m_HitBuffer, m_PointBuffer, m_WingBuffer;
	sf::Sound       m_HitSound, m_PointSound, m_WingSound;

  private:
	void LoadBuffer( );
	void SetSounds( );
};
}  // namespace Engine

#endif
