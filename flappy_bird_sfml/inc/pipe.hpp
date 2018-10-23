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

  private:
	gameDataRef            m_Data;
	std::deque<sf::Sprite> m_PipeSprites;

	std::random_device              m_Device;
	std::mt19937                    m_Gen;
	std::uniform_int_distribution<> m_Range;

  private:
	void SpawnBottomPipe( const float );
	void SpawnTopPipe( const float );
	void SpawnInvisiblePipe( const float );

	inline float PipeSpawnOffsetY( ) { return static_cast<float>( m_Range( m_Gen ) ); }
};
}  // namespace Engine

#endif
