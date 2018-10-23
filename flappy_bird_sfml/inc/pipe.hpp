#ifndef MY_PIPE_HPP
#define MY_PIPE_HPP

#include <SFML/Graphics.hpp>

#include <deque>
#include <random>

#include "game.hpp"

namespace Engine
{
class Pipe {
  public:
	Pipe( gameDataRef );
	~Pipe( );

	void Spawn( );
	void Move( const float );

	void Draw( );

	inline const std::deque<sf::Sprite> &GetSprites( ) const { return m_PipeSprites; }
	inline const std::deque<sf::Sprite> &GetScoreSprites( ) const {
		return m_ScoreSprites;
	}
	inline void PopScorePipe( ) { m_ScoreSprites.pop_front( ); }

  private:
	gameDataRef m_Data;

	std::deque<sf::Sprite> m_PipeSprites;
	std::deque<sf::Sprite> m_ScoreSprites;

	std::random_device              m_Device;
	std::mt19937                    m_Gen;
	std::uniform_int_distribution<> m_Range;

  private:
	void SpawnBottomPipe( const float );
	void SpawnTopPipe( const float );
	void SpawnInvisiblePipe( const float );
	void SpawnScoringPipe( );

	inline float PipeSpawnOffsetY( ) { return static_cast<float>( m_Range( m_Gen ) ); }
};
}  // namespace Engine

#endif
