#include "../inc/collision.hpp"

namespace Engine
{
Collision::Collision( ) {}

bool Collision::ChechSpritesCollision( const sf::Sprite &sprite_1,
                                       const sf::Sprite &sprite_2 ) {
	sf::FloatRect rect_1( sprite_1.getGlobalBounds( ) );
	sf::FloatRect rect_2( sprite_2.getGlobalBounds( ) );

	if ( rect_1.intersects( rect_2 ) ) return true;
	return false;
}
}  // namespace Engine
