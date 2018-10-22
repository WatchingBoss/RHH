#ifndef MY_LAND_HPP
#define MY_LAND_HPP

#include <SFML/Graphics.hpp>

#include <array>

#include "definitions.h"
#include "game.hpp"

constexpr int LAND_NUM = 2;

namespace Engine
{
class Land {
  public:
	Land( gameDataRef );
	~Land( );

	void MoveLand( const float );
	void DrawLand( );

	const std::array<sf::Sprite, LAND_NUM> &GetSprites( ) const;

  private:
	gameDataRef m_Data;

	std::array<sf::Sprite, LAND_NUM> m_LandSprites;
};
}  // namespace Engine

#endif
