#ifndef MY_SPLASH_STATE_HPP
#define MY_SPLASH_STATE_HPP

#include <SFML/Graphics.hpp>

#include "game.hpp"
#include "state.hpp"
#include "definitions.h"

namespace Engine
{
class SplashState : public State {
  public:
	explicit SplashState( gameDataRef );
	~SplashState();

	void Init( );

	void HandleInput( );
	void Update(float);
	void Draw(float);

  private:
	gameDataRef m_Data;
	sf::Clock m_Clock;

	sf::Texture m_BgTexture;
	sf::Sprite m_Bg;
};
}  // namespace Engine

#endif
