#ifndef MY_COLLISION_HPP
#define MY_COLLISION_HPP

#include <SFML/Graphics.hpp>

namespace Engine
{
class Collision {
  public:
	Collision( );

	bool ChechSpritesCollision( const sf::Sprite &, const sf::Sprite & );
	bool ChechSpritesCollision( sf::Sprite, const float, sf::Sprite, const float );
};
}  // namespace Engine

#endif
