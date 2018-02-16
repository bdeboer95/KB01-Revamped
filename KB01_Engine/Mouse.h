#ifndef __MOUSE_H__
#define __MOUSE_H__

#define MOUSEL	0
#define MOUSER	1
#define MOUSEM	2

#include "Device.h"
#include <dinput.h>

class Mouse : public Device
{
private:

	struct MouseStruct
	{
		int positionX = 0;
		int positionY = 0;
		int z = 0;
		bool button0 = false;
		bool button1 = false;
		bool button2 = false;
		bool button3 = false;
		bool button4 = false;
		bool button5 = false;
		bool button6 = false;
		bool button7 = false;
	};

	LPDIRECTINPUT8 directInput;	// DirectInput interface
	LPDIRECTINPUTDEVICE8 mouse;	// Keyboard device
	HWND hwnd;
	DIPROPDWORD dipdw;
	MouseStruct bufferedMouse;
	DIMOUSESTATE mouseState;

	void SetMouseBuffer();
	void ResetStruct();

public:
	Mouse(HWND _hwnd);
	~Mouse();

	bool InitDevice();
	bool AcquireDevice();
	void ReleaseDevice();
	HRESULT PollDevice();
	DIMOUSESTATE DeviceState();
	MouseStruct GetMouseInput();
};

#endif