#ifndef __DEVICE_H__
#define __DEVICE_H__

#include <dinput.h>
#include <vector>
#include "TransformationEvent.h"
class InputListener;
class Device
{
	
protected:
	HWND window;
	LPDIRECTINPUT8 input;
	LPDIRECTINPUTDEVICE8 device;

public:

	virtual ~Device() {};
	virtual bool InitDevice() = 0;
	virtual bool AcquireDevice() = 0;
	virtual void ReleaseDevice() = 0;
	virtual HRESULT PollDevice() = 0;
	virtual void NotifyListeners(std::vector<InputListener*> listeners) = 0; //Notify all inputlisteners if the device state has been changed
};

#endif