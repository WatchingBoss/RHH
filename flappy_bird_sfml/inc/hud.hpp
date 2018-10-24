#ifndef MY_HUD_HPP
#define MY_HUD_HPP

#include <SFML/Graphics.hpp>

#include "definitions.h"
#include "game.hpp"

namespace Engine
{
class Hud {
  public:
	Hud( gameDataRef );
	~Hud( );

	void Draw( );
	void UpdateScore( uint32 );

  private:
	gameDataRef m_Data;

	sf::Text m_ScoreText;
};
}  // namespace Engine

#endif
