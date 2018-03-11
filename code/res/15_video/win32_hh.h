#if !defined(WIN32_HH_H)
/* ===========================================================
	$File: $
	$Date: $
	$Revision: $
	$Creator: Egor Smirnov (Santa) $
	$Notice: $
   ===========================================================*/

struct win32_offscreen_buffer
{
	// NOTE(santa): Pixels are alwasy 32-bits wide, Memory Order BB GG RR XX
	BITMAPINFO Info;
	void *Memory;
	int Width;
	int Height;
	int Pitch;
};

struct win32_window_dimension
{
	int Width;
	int Height;
};


struct win32_sound_output
{
	int SamplesPerSecond;
	uint32 RunningSampleIndex; 
	int BytesPerSample;
	int SecondaryBufferSize;
	real32 tSine;
	int LatencySampleCount;
};

#define WIN32_HH_H
#endif
