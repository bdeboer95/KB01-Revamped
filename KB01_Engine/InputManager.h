#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

#include "InputListener.h"
#include "Device.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <vector>

class InputManager 
{
private:
	std::vector<InputListener*> listeners;
	std::vector<Device*>		devices;

	void						DeleteAllListeners();
	void					    DeleteAllDevices();
//std::vector<Device*>		GetDevices();
public:
								InputManager(HWND _hwnd);
								InputManager();
								~InputManager();
	
	Keyboard*					CreateKeyboard(HWND _hwnd);
	Mouse*						CreateMouse(HWND _handler);
	HRESULT						AddListener(InputListener* listenerPtr);
	void						NotifyListeners(byte state[]);
	void						CreateDevice(HWND _hwnd);
	void						Update();
	Mouse*						GetMouse();
	Keyboard*				    GetKeyboard();

};

#endif