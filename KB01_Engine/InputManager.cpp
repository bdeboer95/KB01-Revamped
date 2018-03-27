//-----------------------------------------------------------------------------
// File: InputManager.cpp
//
// Desc: 
//-----------------------------------------------------------------------------

#include "InputManager.h"

#include "Window.h"

#include <iostream>

/// <summary>
/// Initializes a new instance of the <see cref="InputManager"/> class.
/// </summary>
/// <param name="_hwnd">The _HWND.</param>
InputManager::InputManager(HWND _hwnd)
{
	CreateDevice(_hwnd);
	Log::Instance()->LogMessage("InputManager - InputManager created.", Log::MESSAGE_INFO);
}

InputManager::InputManager()
{

}

/// <summary>
/// Finalizes an instance of the <see cref="InputManager"/> class.
/// </summary>
InputManager::~InputManager()
{
	DeleteAllListeners();
	DeleteAllDevices();
	Log::Instance()->LogMessage("~InputManager - InputManager cleaned up!", Log::MESSAGE_INFO);
}

///// <summary>
///// Gets the devices.
///// </summary>
///// <returns></returns>
//std::vector<Device*> InputManager::GetDevices()
//{
//	return devices;
//}

/// <summary>
/// Creates the device.
/// </summary>
/// <param name="_hwnd">The _HWND.</param>
void InputManager::CreateDevice(HWND _hwnd)
{
	CreateMouse(_hwnd);
	CreateKeyboard(_hwnd);
}

Mouse* InputManager::CreateMouse(HWND _hwnd)
{
	Mouse* mouse = new Mouse(_hwnd);
	devices.push_back(mouse);
	return mouse;
}

Keyboard* InputManager::CreateKeyboard(HWND _hwnd)
{
	Keyboard* keyboard = new Keyboard(_hwnd);
	devices.push_back(keyboard);
	return keyboard;
}

/// <summary>
/// Adds the listener.
/// </summary>
/// <param name="listenerPtr">The listener PTR.</param>
/// <returns></returns>
HRESULT InputManager::AddListener(InputListener* listenerPtr)
{
	int amount = listeners.size();
	listeners.push_back(listenerPtr);
	
	if (amount < listeners.size())
	{
		return S_OK;
		std::cout << "Amount of listeners: " << listeners.size() << std::endl;
	}

	return E_FAIL;
}

/// <summary>
/// Updates this instance.
/// </summary>
void InputManager::Update()
{
	for (int i = 1; i < devices.size(); ++i)
	{
		if (SUCCEEDED(static_cast<Keyboard*>(devices[i])->PollDevice()))
		{
			NotifyListeners(static_cast<Keyboard*>(devices[i])->GetKeyboardState());
		}
		else
		{
			static_cast<Keyboard*>(devices[i])->AcquireDevice();
		}

		//if (SUCCEEDED(static_cast<Mouse*>(devices[0])->PollDevice()))
		//{
		//	NotifyListeners(static_cast<Mouse*>(devices[0])->GetMouseState().rgbButtons);
		//}
		//else
		//{
		//	static_cast<Mouse*>(devices[0])->AcquireDevice();
		//}
	}
}

/// <summary>
/// Notifies the listeners.
/// </summary>
/// <param name="state">The state.</param>
void InputManager::NotifyListeners(byte state[])
{
	for (unsigned int i = 0; i < listeners.size(); i++)
	{
		listeners[i]->Notify(state);
	}
}

/// <summary>
/// Deletes all listeners.
/// </summary>
void InputManager::DeleteAllListeners()
{
	while (!listeners.empty())
	{
		//delete listeners.back();
		listeners.pop_back();
	}

	Log::Instance()->LogMessage("InputManager - Deleted all listeners.", Log::MESSAGE_INFO);
}

/// <summary>
/// Deletes all devices.
/// </summary>
void InputManager::DeleteAllDevices()
{
	while (!devices.empty())
	{
		//for (int i = 0; i < devices.size(); ++i)
		//{
		//	delete static_cast<Keyboard*>(devices[i]);
		//}

		delete devices.back();
		devices.pop_back();
	}

	Log::Instance()->LogMessage("InputManager - Deleted all devices.", Log::MESSAGE_INFO);
}

/// <summary>
/// Gets the mouse.
/// </summary>
/// <returns></returns>
Mouse* InputManager::GetMouse()
{
	Mouse* mouse= NULL;
	for (int i = 0; i < devices.size(); ++i)
	{
		if (static_cast<Mouse*>(devices[i])) {
			mouse = static_cast<Mouse*>(devices[i]);
	
			Log::Instance()->LogMessage("InputManager - Got a mouse.", Log::MESSAGE_INFO);
			return mouse;
		}
	}
	
}

Keyboard* InputManager::GetKeyboard()
{
	Keyboard* keyboard = NULL;
	for (int i = 0; i < devices.size(); ++i)
	{
		if (static_cast<Keyboard*>(devices[i])) {
			keyboard = static_cast<Keyboard*>(devices[i]);
		}
	}
	return keyboard;

}