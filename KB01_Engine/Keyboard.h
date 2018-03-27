#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "Device.h"

class Keyboard : public Device
{
public:
	Keyboard(HWND _hwnd);
	~Keyboard();

	bool InitDevice();
	bool AcquireDevice();
	void ReleaseDevice();
	HRESULT PollDevice();
	byte* GetKeyboardState();
};

#endif