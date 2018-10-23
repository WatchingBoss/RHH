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

bool Collision::ChechSpritesCollision( sf::Sprite sprite_1, const float size_1,
                                       sf::Sprite sprite_2, const float size_2 ) {
	sprite_1.scale( size_1, size_1 );
	sprite_2.scale( size_2, size_2 );

	sf::FloatRect rect_1( sprite_1.getGlobalBounds( ) );
	sf::FloatRect rect_2( sprite_2.getGlobalBounds( ) );

	if ( rect_1.intersects( rect_2 ) ) return true;
	return false;
}
}  // namespace Engine
