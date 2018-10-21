#ifndef MY_MAIN_MENU_STATE_HPP
#define MY_MAIN_MENU_STATE_HPP

#include <SFML/Graphics.hpp>

#include <vector>

#include "definitions.h"
#include "game.hpp"
#include "state.hpp"

namespace Engine
{
class MainMenuState : public State {
  public:
	explicit MainMenuState( gameDataRef );
	~MainMenuState( );

	void Init( );

	void HandleInput( );
	void Update( float );
	void Draw( float );

  private:
	gameDataRef m_Data;

	sf::Sprite m_Bg;
	sf::Sprite m_Title;
	sf::Sprite m_PlayButton;

	std::vector<sf::Sprite> m_Sprites;

  private:
	void AddTexture( const char *, const char *, sf::Sprite &, const float = 0,
	                 const float = 0 );
};
}  // namespace Engine

#endif
