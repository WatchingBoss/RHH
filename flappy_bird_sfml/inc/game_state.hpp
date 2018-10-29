#ifndef MY_GAME_STATE_HPP
#define MY_GAME_STATE_HPP

#include <SFML/Graphics.hpp>

#include "bird.hpp"
#include "collision.hpp"
#include "definitions.h"
#include "flash.hpp"
#include "game.hpp"
#include "hud.hpp"
#include "land.hpp"
#include "pipe.hpp"
#include "state.hpp"

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

	eGAME_STATE m_GameState;

	sf::Clock m_Clock;

	sf::Sprite m_Bg;

	Pipe * m_Pipe;
	Land * m_Land;
	Bird * m_Bird;
	Flash *m_Flash;
	Hud *  m_Hud;

	Collision m_Collision;

	uint32 m_Score;

	bool m_BirdOnLand;

  private:
	void AddTexture( const char *, const char *, sf::Sprite & );
	void LoadTexture( const char *, const char * );
	void LoadFont( const char *, const char * );

	bool CheckCollision( );

	bool CheckScore( );
	void UpdateScore( );

	void CheckDataDirectory( );
	void UpdateBestScoreFile( );
};
}  // namespace Engine

#endif
