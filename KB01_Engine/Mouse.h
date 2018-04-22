#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "Device.h"
#include "InputListener.h"
#include "d3dx9.h"
#include "Vector2.h"
struct MouseState {
	LONG    lX;
	LONG    lY;
	LONG    lZ;
	BYTE    rgbButtons[4];
};

class Mouse : public Device
{

public:


	Mouse(HWND _hwnd);
	~Mouse();

	bool InitDevice();
	bool AcquireDevice();
	void ReleaseDevice();
	HRESULT PollDevice();
	void NotifyListeners(std::vector<InputListener*> listeners);
	MouseState GetMouseState(); //get the current buttons and positioning of the mouse	
	Vector2 mouseCoordinates;
private:
	MouseState mouseState; //the buttons that have been pressed or the amount the mouse was moved to the right or left

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

	void SetMouseBuffer();
	void ResetStruct();
};

#endif