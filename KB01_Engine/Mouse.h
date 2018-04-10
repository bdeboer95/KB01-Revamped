#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "Device.h"
#include "InputListener.h"
#include "Observee.h"

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

private:
	MouseState mouseState; //the buttons that have been pressed or the amount the mouse was moved to the right or left
	void ResetStruct();
};  	

#endif