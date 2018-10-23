#ifndef MY_FLUSH_HPP
#define MY_FLUSH_HPP

#include <SFML/Graphics.hpp>

#include "definitions.h"
#include "game.hpp"

namespace Engine
{
class Flash {
  public:
	Flash( gameDataRef );
	~Flash( );

	void Show( const float );
	void Draw( );

  private:
	gameDataRef m_Data;

	sf::RectangleShape m_Shape;

	bool m_FlashOn;

	uint8 m_Red, m_Green, m_Blue, m_Alpha;
};

}  // namespace Engine

#endif
