#ifndef MY_BIRD_HPP
#define MY_BIRD_HPP

#include <SFML/Graphics.hpp>

#include <array>

#include "definitions.h"
#include "game.hpp"

namespace Engine
{
class Bird {
  public:
	Bird( gameDataRef );
	~Bird( );

	void DrawBird( );
	void Animate( const float );

	void Update( const float );
	void Tap( );

  private:
	gameDataRef m_Data;

	sf::Clock m_Clock, m_MovementClock;

	int                        m_AnimationIterator;
	sf::Sprite                 m_BirdSprite;
	std::array<sf::Texture, 4> m_BirdAnimation;

	BIRD_STATE m_BirdState;

  private:
	void FillTextures( );
};
}  // namespace Engine

#endif
