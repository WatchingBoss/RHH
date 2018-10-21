#ifndef MY_GAME_STATE_HPP
#define MY_GAME_STATE_HPP

#include <SFML/Graphics.hpp>

#include "definitions.h"
#include "game.hpp"
#include "pipe.hpp"
#include "state.hpp"
#include "land.hpp"
#include "bird.hpp"

namespace Engine
{
class GameState : public State {
  public:
	explicit GameState( gameDataRef );
	~GameState( );

	void Init( );

	void HandleInput( );
	void Update( float );
	void Draw( float );

  private:
	gameDataRef m_Data;

	sf::Clock m_Clock;

	bool m_GameOver;

	sf::Sprite m_Bg;

	Pipe *m_Pipe;
	Land *m_Land;
	Bird *m_Bird;

  private:
	void AddTexture( const char *, const char *, sf::Sprite &);
	void LoadTexture( const char *, const char *);
};
}  // namespace Engine

#endif
