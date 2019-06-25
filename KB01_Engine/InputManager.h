#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

#include "InputListener.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <vector>

/// <summary>
/// The input manager handles all the input devices and the entities that are subscribed to these devices
/// </summary>
class InputManager 
{
private:
	std::vector<InputListener*> listeners;								//all the entities/objects that listen to input from devices
	std::vector<Device*>		devices;								//all the devices that have been registerered

	void						DeleteAllListeners();					//Delete all the input listeners from the array
	void					    DeleteAllDevices();						//Delete all the input devices from the array

public:							
	InputManager();
								InputManager(HWND _hwnd);
								~InputManager();
	
	Keyboard*					CreateKeyboard(HWND _hwnd);
	Mouse*						CreateMouse(HWND _hwnd);
	HRESULT						AddListener(InputListener* listenerPtr);
	//void						NotifyListeners(byte state[]);
	void						CreateDevice(HWND _hwnd);
	void						Update();
	Mouse*						GetMouse();
	Keyboard*				    GetKeyboard();

};

#endif