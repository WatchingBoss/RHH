#include "../inc/state_machine.hpp"
#include <iostream>

namespace Engine
{
StateMachine::StateMachine( )
    : m_States( ), m_NewState( ), m_isRemoving( ), m_isAdding( ), m_isReplacing( ) {}

StateMachine::~StateMachine( ) {}

void StateMachine::AddState( stateRef new_state, bool is_replacing ) {
	m_isAdding    = true;
	m_isReplacing = is_replacing;
	m_NewState    = std::move( new_state );
}

void StateMachine::ProcessStateChanges( ) {
	if ( m_isRemoving && !m_States.empty( ) ) {
		m_States.pop( );

		if ( !m_States.empty( ) ) m_States.top( )->Resume( );

		m_isRemoving = false;
	}

	if ( m_isAdding ) {
		if ( !m_States.empty( ) ) {
			if ( m_isReplacing )
				m_States.pop( );
			else
				m_States.top( )->Pause( );
		}

		m_States.push( std::move( m_NewState ) );
		m_States.top( )->Init( );

		m_isAdding = false;
	}
}

stateRef &StateMachine::GetActiveState( ) {
	if ( m_States.empty( ) ) {
		std::cout << "No states in stack" << std::endl;
		exit(EXIT_FAILURE);
	}
	return m_States.top( );
}

}  // namespace Engine
