/* ===========================================================
	$File: $
	$Date: $
	$Revision: $
	$Creator: $
	$Notice: $
   ===========================================================*/

#include <windows.h>

int CALLBACK
WinMain(	HINSTANCE hInstance,
			HINSTANCE hPrevInstance,
			LPSTR     lpCmdLine,
			int       nCmdShow)
{
  MessageBoxA(0, "This is copy HH", "HH",
				 MB_OK|MB_ICONINFORMATION);
  return(0);
}

