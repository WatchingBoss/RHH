#ifndef MY_COLLISION_HPP
#define MY_COLLISION_HPP

#include <SFML/Graphics.hpp>

namespace Engine
{
class Collision {
  public:
	Collision( );

	bool ChechSpritesCollision( const sf::Sprite &, const sf::Sprite & );
};
}  // namespace Engine

#endif
