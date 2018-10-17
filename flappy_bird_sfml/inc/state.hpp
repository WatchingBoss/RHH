#ifndef MY_STATE_HPP
#define MY_STATE_HPP

namespace Flappy
{
class State {
  public:
	virtual void Init( ) = 0;

	virtual void HandleInput( ) = 0;
	virtual void Update( )      = 0;
	virtual void Draw( float )  = 0;

	virtual void Pause( ) {}
	virtual void Resume( ) {}
};
}  // namespace Flappy

#endif
