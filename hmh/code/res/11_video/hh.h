#if !defined(HH_H)
/* ===========================================================
	$File: $
	$Date: $
	$Revision: $
	$Creator: Santa Claus $
	$Notice: $
   ===========================================================*/

/*
	TODO(santa): Services that the platform layer provides to the game
*/

/*
	NOTE(santa): Services that the game provides to the platform layer.
	(this may expand in the future - sound on separate thread, etc.)
*/

// FOUR THINGS - timing, controller/keyboard input, bitmap buffer to use, sound buffer to use

struct game_offscreen_buffer
{
	// NOTE(santa): Pixels are alwasy 32-bits wide, Memory Order BB GG RR XX
	void *Memory;
	int Width;
	int Height;
	int Pitch;
};

internal void GameUpdateAndRender(game_offscreen_buffer *Buffer, int BlueOffset, int GreenOffset);

#define HH_H
#endif
