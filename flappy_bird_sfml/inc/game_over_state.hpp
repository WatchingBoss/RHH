#ifndef MY_GAME_OVER_STATE_HPP
#define MY_GAME_OVER_STATE_HPP

#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "state.hpp"
#include "definitions.h"

namespace Engine
{
class GameOverState : public State {
  public:
	explicit GameOverState( gameDataRef );
	~GameOverState();

	void Init( );

	void HandleInput( );
	void Update(float);
	void Draw(float);

  private:
	gameDataRef m_Data;

	sf::Sprite m_Bg;
};
}  // namespace Engine

#endif
