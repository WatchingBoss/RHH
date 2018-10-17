

#include <SFML/Graphics.hpp>

#define MW_WIDTH 1024
#define MW_HEIGHT 720

int main( ) {
	sf::RenderWindow window( sf::VideoMode( MW_WIDTH, MW_HEIGHT ), "Like a flappy bird" );

	sf::CircleShape circle( 240.f );
	circle.setFillColor( sf::Color::Blue );

	while ( window.isOpen( ) ) {
		sf::Event event;
		while ( window.pollEvent( event ) ) {
			if ( event.type == sf::Event::Closed ) window.close( );
		}

		window.clear( );
		window.draw( circle );
		window.display( );
	}

	return 0;
}
