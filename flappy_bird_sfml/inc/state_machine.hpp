#ifndef MY_STATE_MACHINE_HPP
#define MY_STATE_MACHINE_HPP

#include <memory>
#include <stack>

#include "state.hpp"

namespace Flappy
{
using stateRef = std::unique_ptr<State>;

class StateMachine {
  public:
	StateMachine( );
	~StateMachine( );

	void AddState( stateRef, bool = true );
};
}  // namespace Flappy

#endif
