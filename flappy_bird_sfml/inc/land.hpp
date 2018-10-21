#ifndef MY_LAND_HPP
#define MY_LAND_HPP

#include <SFML/Graphics.hpp>

#include <array>

#include "game.hpp"
#include "definitions.h"

namespace Engine{
class Land{
  public:
	Land(gameDataRef);
	~Land();

	void MoveLand(const float);
	void DrawLand();

  private:
	gameDataRef m_Data;

	std::array<sf::Sprite, 2> m_LandSprites;
	
};
}

#endif
