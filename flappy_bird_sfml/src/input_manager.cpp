#include "../inc/input_manager.hpp"

namespace Engine
{
InputManager::InputManager( ) {}
InputManager::~InputManager( ) {}

bool InputManager::IsSpriteClicked( sf::Sprite &obj, sf::Mouse::Button &button,
                                    sf::RenderWindow &window ) {
	if ( sf::Mouse::isButtonPressed( button ) ) {
		sf::FloatRect temp_rect( obj.getGlobalBounds( ) );
		sf::Vector2i  mouse_pos = sf::Mouse::getPosition( );
		if ( temp_rect.contains( static_cast<float>( mouse_pos.x ),
		                         static_cast<float>( mouse_pos.y ) ) )
			return true;
	}
	return false;
}
}  // namespace Engine
