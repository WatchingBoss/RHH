#include <iostream>

#include "../inc/game.hpp"

namespace Engine
{
Game::Game( int width, int height, const char *title )
    : m_FrameTime( 1.f / 60.f ), m_Clock( ) {
	m_Data->window.create( sf::VideoMode( width, height ), title,
	                       sf::Style::Close | sf::Style::Titlebar );

//	TODO: Add state to stack in machine object

	RunGame( );
}

Game::~Game( ) {}

void Game::RunGame( ) {
	float current_time = m_Clock.getElapsedTime( ).asSeconds( );
	float accumulator  = 0.f;

	int number = 0;

	while ( m_Data->window.isOpen( ) ) {
		m_Data->machine.ProcessStateChanges( );

		float new_time   = m_Clock.getElapsedTime( ).asSeconds( ),
		      frame_time = new_time - current_time;

		if ( frame_time > 0.25f ) frame_time = 0.25f;
		current_time = new_time;
		accumulator += frame_time;

		while ( accumulator >= m_FrameTime ) {
			m_Data->machine.GetActiveState( )->HandleInput( );
			m_Data->machine.GetActiveState( )->Update( m_FrameTime );

			accumulator -= m_FrameTime;
		}

		float interpolation = accumulator / m_FrameTime;
		m_Data->machine.GetActiveState( )->Update( interpolation );

		std::printf("Iteration of game loop: %d\n", ++number);
	}
}
}  // namespace Engine
