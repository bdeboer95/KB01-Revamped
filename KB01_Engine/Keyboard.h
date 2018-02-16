#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "Device.h"
#include <dinput.h>
#include <iostream>

class Keyboard : public Device
{
private:
	LPDIRECTINPUT8 directInput;		// DirectInput interface
	LPDIRECTINPUTDEVICE8 keyboard;	// Keyboard device
	HWND hwnd;
	byte state[256]; //defines the keyboard states

public:
	Keyboard();
	Keyboard(HWND _hwnd);
	~Keyboard();

	bool InitDevice();
	bool AcquireDevice();
	void ReleaseDevice();
	HRESULT PollDevice();
	byte* DeviceState();
	byte KeyAlreadyPressed();
};

#endif