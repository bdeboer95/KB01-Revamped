#ifndef __WINDOWMANAGERFACADE_H__
#define __WINDOWMANAGERFACADE_H__

#include "InputManager.h"

class InputManagerFacade
{
private:
	InputManager* inputManager;
public:
	InputManagerFacade();
	~InputManagerFacade();

	void CreateDevices(HWND _handler, int amountOfKeyboards);
};
 
#endif
