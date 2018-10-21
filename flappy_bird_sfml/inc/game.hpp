#ifndef MY_FLAPPY_HPP
#define MY_FLAPPY_HPP

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "./asset_manager.hpp"
#include "./input_manager.hpp"
#include "./state_machine.hpp"

namespace Engine
{
struct GameData {
	StateMachine     machine;
	sf::RenderWindow window;
	AssetManager     asset;
	InputManager     input;
};

using gameDataRef = std::shared_ptr<GameData>;

class Game {
  public:
	Game( int, int, const char *);
	~Game( );

  private:
	const float m_FrameTime;
	sf::Clock   m_Clock;
	gameDataRef m_Data = std::make_shared<GameData>( );

  private:
	void RunGame();
};

}  // namespace Flappy

#endif
