#include "../inc/collision.hpp"

#include <iostream>

namespace Engine
{
Collision::Collision( ) {}

bool Collision::CheckSpritesCollision( const sf::Sprite &sprite_1,
                                       const sf::Sprite &sprite_2 ) {
	sf::FloatRect rect_1( sprite_1.getGlobalBounds( ) );
	sf::FloatRect rect_2( sprite_2.getGlobalBounds( ) );

	// std::printf( "\n\nX: %f, Y: %f, Width: %f, Height: %f\n"
	//             "X: %f, Y: %f, Width: %f, Height: %f\n\n",
	//             rect_1.left, rect_1.top, rect_1.width, rect_1.height, rect_2.left,
	//             rect_2.top, rect_2.width, rect_2.height );

	if ( rect_1.intersects( rect_2 ) ) return true;
	return false;
}

bool Collision::CheckSpritesCollision( sf::Sprite sprite_1, const float size_1,
                                       sf::Sprite sprite_2, const float size_2 ) {
	sprite_1.scale( size_1, size_1 );
	sprite_2.scale( size_2, size_2 );

	sf::FloatRect rect_1( sprite_1.getGlobalBounds( ) );
	sf::FloatRect rect_2( sprite_2.getGlobalBounds( ) );

	if ( rect_1.intersects( rect_2 ) ) return true;
	return false;
}
}  // namespace Engine
