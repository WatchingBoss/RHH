#ifndef MY_INPUT_MANAGER_HPP
#define MY_INPUT_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace Engine
{
class InputManager {
  public:
	InputManager( );
	~InputManager( );

	static bool IsSpriteClicked( sf::Sprite &, const sf::Mouse::Button &, sf::RenderWindow & );

	static inline sf::Vector2i GetMousePosition( sf::RenderWindow &window ) {
		return sf::Mouse::getPosition( window );
	}
};
}  // namespace Engine

#endif
