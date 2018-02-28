/* ===========================================================
	$File: $
	$Date: $
	$Revision: $
	$Creator: Santa Claus $
	$Notice: $
   ===========================================================*/

#include <windows.h>
#include <stdint.h>
#include <XInput.h>

#define internal        static 
#define local_persist   static
#define global_variable static

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

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

// NOTE(santa): XInputGetState
#define X_INPUT_GET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_STATE *pState)
typedef X_INPUT_GET_STATE(x_input_get_state);
X_INPUT_GET_STATE(XInputGetStateStub)
{
	return(0);
}
global_variable x_input_get_state *XInputGetState_ =  XInputGetStateStub;

// NOTE(santa): XInputSetState
#define X_INPUT_SET_STATE(name) DWORD WINAPI name(DWORD dwUserIndex, XINPUT_VIBRATION *pVibration)
typedef X_INPUT_SET_STATE(x_input_set_state);
X_INPUT_SET_STATE(XInputSetStateStub)
{
	return(0);
}

global_variable x_input_set_state *XInputSetState_ =  XInputSetStateStub;

#define XInputGetState XInputGetState_
#define XInputSetState XInputSetState_

// TODO(santa): This is a global for now.
global_variable bool GlobalRunning;
global_variable win32_offscreen_buffer GlobalBackbuffer;

win32_window_dimension
Win32GetWindowDimension(HWND Window)
{
	win32_window_dimension Result;
	
	RECT ClientRect;
	GetClientRect(Window, &ClientRect);
    Result.Width  = ClientRect.right  - ClientRect.left;
    Result.Height = ClientRect.bottom - ClientRect.top;
	
	return(Result);
}


internal void
RenderWeirdGradient(win32_offscreen_buffer Buffer, int XOffset, int YOffset)
{
	// TODO(santa): Let's see what the optimizer does

	uint8 *Row = (uint8 *)Buffer.Memory;
	for (int Y = 0; Y < Buffer.Height; ++Y)
	{
		uint32 *Pixel = (uint32 *)Row;
		for (int X = 0; X < Buffer.Width; ++X)
		{
			uint8 Blue  = (X + XOffset);
			uint8 Green = (Y + YOffset);
			
			*Pixel++  = ((Green << 8) | Blue); 
		}

		Row += Buffer.Pitch;
	}
}

internal void
Win32ResizeDIBSection(win32_offscreen_buffer *Buffer, int Width, int Height)
{
	//TODO(santa): Bulletproof this.

	if (Buffer->Memory)
	{
		VirtualFree(Buffer->Memory, 0, MEM_RELEASE);
	}

    Buffer->Width     = Width;
    Buffer->Height    = Height;
	int BytesPerPixel = 4;

	// NOTE(santa): When the biHeight field is negative, this is the clue to
	// Windows to treat this bitmap as top-down, not bottom-up, meaning that
	// the first three bytes of the image are the color for the top left pixel
	// int the bitmap, not the bottom left!
	Buffer->Info.bmiHeader.biSize        = sizeof(Buffer->Info.bmiHeader);
	Buffer->Info.bmiHeader.biWidth       = Buffer->Width;
    Buffer->Info.bmiHeader.biHeight      = -Buffer->Height;
	Buffer->Info.bmiHeader.biPlanes      = 1;
	Buffer->Info.bmiHeader.biBitCount    = 32;
	Buffer->Info.bmiHeader.biCompression = BI_RGB;

	int BitmapMemorySize = (Buffer->Width * Buffer->Height) * BytesPerPixel;
    Buffer->Memory = VirtualAlloc(0, BitmapMemorySize, MEM_COMMIT, PAGE_READWRITE);

    Buffer->Pitch = Width * BytesPerPixel;

	// TODO(santa): Probably clear this to black
}	
internal void
Win32DisplayBufferInWindow(HDC DeviceContext,
						   int WindowWidth, int WindowHeight,
						   win32_offscreen_buffer Buffer)
{
	// TODO(santa): Aspect ratio correction
	// TODO(santa): Play with stretch modes
	StretchDIBits(DeviceContext,
				  /*
				  X, Y, Width, Height,
				  X, Y, Width, Height,
				  */
				  0, 0, WindowWidth, WindowHeight,
				  0, 0, Buffer.Width, Buffer.Height,
				  Buffer.Memory,
				  &Buffer.Info,
				  DIB_RGB_COLORS, SRCCOPY);
}

LRESULT CALLBACK
Win32MainWindowCallback(HWND   Window,
						UINT   Message,
						WPARAM WParam,
						LPARAM LParam)
{
	LRESULT Result = 0;
	
	switch(Message)
	{		
		case WM_DESTROY:
		{
			// TODO(santa): Handle this as an error - recreate window?
			GlobalRunning = false;
		} break;
		
		case WM_CLOSE:
		{
			// TODO(santa): Handle this with a message to the user?
			GlobalRunning = false;
		} break;
		
		case WM_ACTIVATEAPP:
		{
			OutputDebugStringA("WM_ACTIVATEAPP\n");
		} break;

		case WM_PAINT:
		{
			PAINTSTRUCT Paint;
			HDC DeviceContext = BeginPaint(Window, &Paint);
			int X = Paint.rcPaint.left;
			int Y = Paint.rcPaint.top;
			int Width  = Paint.rcPaint.right  - Paint.rcPaint.left;
			int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
			
			win32_window_dimension Dimension = Win32GetWindowDimension(Window);
			Win32DisplayBufferInWindow(DeviceContext, Dimension.Width, Dimension.Height,
									   GlobalBackbuffer);
			EndPaint(Window, &Paint);
		} break;
		
		default:
		{
//			OutputDebugStringA("WM_default\n");
			Result = DefWindowProc(Window, Message, WParam, LParam);
		} break;
	}
	
	return(Result);
}

int CALLBACK
WinMain(HINSTANCE Instance,
	    HINSTANCE PrevInstance,
		LPSTR     CommandLine,
		int       ShowCode)
{
 	WNDCLASS WindowClass = {};
	
	Win32ResizeDIBSection(&GlobalBackbuffer, 1280, 720);
	 
	WindowClass.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
 	WindowClass.lpfnWndProc = Win32MainWindowCallback;
 	WindowClass.hInstance = Instance;
	// WindowClass.hIcon;
    WindowClass.lpszClassName = "HHWindowClass";

	if (RegisterClassA(&WindowClass))
	{
		HWND Window =
			CreateWindowExA(0,
						   WindowClass.lpszClassName,
						   "Copy handmade hero",
						   WS_OVERLAPPEDWINDOW|WS_VISIBLE,
						   CW_USEDEFAULT,
						   CW_USEDEFAULT,
						   CW_USEDEFAULT,
						   CW_USEDEFAULT,
						   0,
						   0,
						   Instance,
			    		   0); 
		if (Window)
		{
			// NOTE(santa): Since we specified CS_OWNDC, we can just
			// get one device context and use it forever because we
			// are not sharing it with anyone.
			HDC DeviceContext = GetDC(Window);
			
			int XOffset = 0;
			int YOffset = 0;
				
			GlobalRunning = true;
			while(GlobalRunning)
			{
				MSG Message;
				while (PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
				{
					if (Message.message == WM_QUIT)
					{
						GlobalRunning = false;
					}
					
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}
				for (DWORD ControllerIndex = 0;
					 ControllerIndex < XUSER_MAX_COUNT;
					 ++ControllerIndex)
				{
					XINPUT_STATE ControllerState;
				    if(XInputGetState(ControllerIndex, &ControllerState) == ERROR_SUCCESS)
					{
						// NOTE(santa): This controller is plugged in
						// TODO(santa): See if ControllerState.dwPacketNumber increments too rapidly
						XINPUT_GAMEPAD *Pad = &ControllerState.Gamepad;

						bool Up = (Pad->wButtons & XINPUT_GAMEPAD_DPAD_UP);
						bool Down = (Pad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
						bool Left = (Pad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
						bool Right = (Pad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
						bool Start = (Pad->wButtons & XINPUT_GAMEPAD_START);
						bool Back = (Pad->wButtons & XINPUT_GAMEPAD_BACK);
						bool LeftShoulder = (Pad->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
						bool RightShoulder = (Pad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
						bool AButton = (Pad->wButtons & XINPUT_GAMEPAD_A);
						bool BButton = (Pad->wButtons & XINPUT_GAMEPAD_B);
						bool XButton = (Pad->wButtons & XINPUT_GAMEPAD_X);
						bool YButton = (Pad->wButtons & XINPUT_GAMEPAD_Y);

						int16 SticX = Pad->sThumbLX;
						int16 SticY = Pad->sThumbLY;
					}			 
					else
					{
						// NOTE(santa): The controller is not available
					}
				}
				
				RenderWeirdGradient(GlobalBackbuffer, XOffset, YOffset);

				win32_window_dimension Dimension = Win32GetWindowDimension(Window);
			    Win32DisplayBufferInWindow(DeviceContext,
										   Dimension.Width, Dimension.Height,
										   GlobalBackbuffer);
				++XOffset;
				YOffset += 2;
			}
		}
		else
		{
			// TODO(santa): Logging
		}
	}
	else
	{
		// TODO(santa): Logging
	}
	 
    return(0);
}

