﻿#include "hmh_win32.h"

#include <windows.h>

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow ) {
	MessageBox( NULL, "This works fine", "Title", MB_OK );

	return 0;
}