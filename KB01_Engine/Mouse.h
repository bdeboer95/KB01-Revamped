#ifndef __MOUSE_H__
#define __MOUSE_H__

#define MOUSEL	0
#define MOUSER	1
#define MOUSEM	2

#include "Device.h"

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

	DIPROPDWORD dipdw;
	MouseStruct bufferedMouse;

	void SetMouseBuffer();
	void ResetStruct();

public:
	Mouse(HWND _hwnd);
	~Mouse();

	bool InitDevice();
	bool AcquireDevice();
	void ReleaseDevice();
	HRESULT PollDevice();
	DIMOUSESTATE GetMouseState();

	MouseStruct GetMouseInput();
};

#endif