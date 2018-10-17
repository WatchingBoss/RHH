#ifndef MY_STATE_MACHINE_HPP
#define MY_STATE_MACHINE_HPP

#include <memory>
#include <stack>

#include "state.hpp"

namespace Engine
{
using stateRef = std::unique_ptr<State>;

class StateMachine {
  public:
	StateMachine( );
	~StateMachine( );

	void        AddState( stateRef, bool = true );
	inline void RemoveState( ) { m_isRemoving = true; }

	void ProcessStateChanges( );

	inline stateRef &GetActiveState( ) { return m_States.top( ); }

  private:
	std::stack<stateRef> m_States;
	stateRef             m_NewState;

	bool m_isRemoving, m_isAdding, m_isReplacing;
};
}  // namespace Engine

#endif
