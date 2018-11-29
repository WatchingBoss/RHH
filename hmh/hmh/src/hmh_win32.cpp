#include <windows.h>

#include "hmh_win32.h"

constexpr char *WindowClassName = "HandmadeHeroWindowClass";

LRESULT CALLBACK MainWindowCallback( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
	LRESULT result = 0;

	switch ( msg ) {
		case WM_SIZE: OutputDebugStringA( "SIZE\n" ); break;
		case WM_CLOSE: DestroyWindow( hwnd ); break;
		case WM_DESTROY: PostQuitMessage( 0 ); break;
		case WM_ACTIVATEAPP: OutputDebugStringA( "ACTIVATEAPP\n" ); break;
		case WM_PAINT: {
			PAINTSTRUCT Paint;
			HDC         dc = BeginPaint( hwnd, &Paint );

			int X      = Paint.rcPaint.left;
			int Y      = Paint.rcPaint.top;
			int width  = Paint.rcPaint.right - X;
			int height = Paint.rcPaint.bottom - Y;

			static DWORD op = WHITENESS;
			PatBlt( dc, X, Y, width, height, op );

			op == WHITENESS ? op = BLACKNESS : op = WHITENESS;

			EndPaint( hwnd, &Paint );
		}
		default: result = DefWindowProc( hwnd, msg, wParam, lParam );
	}
	return result;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nCmdShow ) {
	WNDCLASS WindowClass      = {};
	WindowClass.lpfnWndProc   = MainWindowCallback;
	WindowClass.hInstance     = hInstance;
	WindowClass.lpszClassName = WindowClassName;

	if ( RegisterClassA( &WindowClass ) ) {
		HWND WindowHandle = CreateWindowExA( NULL, WindowClassName, "Like handmade hero",
		                                     WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		                                     CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		                                     CW_USEDEFAULT, NULL, NULL, hInstance, NULL );
		if ( WindowHandle ) {
			MSG Message = {};
			while ( GetMessage( &Message, NULL, 0, 0 ) > 0 ) {
				TranslateMessage( &Message );
				DispatchMessage( &Message );
			}
		} else
			MessageBox( NULL, "CreateWindowEx", "Error", MB_OK );
	} else
		MessageBox( NULL, "RegisterClass", "Error", MB_OK );

	return 0;
}
