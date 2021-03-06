#ifndef MY_GAME_OVER_STATE_HPP
#define MY_GAME_OVER_STATE_HPP

#include <SFML/Graphics.hpp>

#include <array>

#include "definitions.h"
#include "game.hpp"
#include "state.hpp"

namespace Engine
{
class GameOverState : public State {
  public:
	explicit GameOverState( gameDataRef, uint32 );
	~GameOverState( );

	void Init( );

	void HandleInput( );
	void Update( float );
	void Draw( float );

  private:
	gameDataRef m_Data;

	std::array<sf::Sprite, 4> m_Sprites;
	sf::Sprite                m_Medal;

	uint32 m_Score, m_BestScore;

	sf::Text m_ScoreText, m_BestScoreText;

  private:
	void AddTexture( const char *, const char *, sf::Sprite & );
	void LoadTexture( const char *, const char * );

	void SpecifyScoreText( const sf::Sprite );
	void SetMedal( const sf::Sprite );
};
}  // namespace Engine

#endif
