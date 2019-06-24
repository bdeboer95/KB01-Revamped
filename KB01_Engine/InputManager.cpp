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

/// <summary>
/// Initializes a new instance of the <see cref="InputManager"/> class.
/// </summary>
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


/// <summary>
/// Creates the device.
/// </summary>
/// <param name="_hwnd">The _HWND.</param>
void InputManager::CreateDevice(HWND _hwnd)
{
	CreateMouse(_hwnd);
	CreateKeyboard(_hwnd);
}

/// <summary>
/// Creates the mouse.
/// </summary>
/// <param name="_hwnd">The HWND.</param>
/// <returns></returns>
Mouse* InputManager::CreateMouse(HWND _hwnd)
{
	Mouse* mouse = new Mouse(_hwnd);
	devices.push_back(mouse);
	return mouse;
}

/// <summary>
/// Creates the keyboard.
/// </summary>
/// <param name="_hwnd">The HWND.</param>
/// <returns></returns>
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
/// Updates all the listeners that there may be notifications from the input devices
/// </summary>
void InputManager::Update()
{
	for (int i = 0; i < devices.size(); i++)
	{
		devices[i]->NotifyListeners(listeners);
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
	for (int i = 0; i < devices.size(); ++i)
	{
		if (static_cast<Mouse*>(devices[i]))
		{
			return static_cast<Mouse*>(devices[i]);
		}
	}
}

/// <summary>
/// Gets the keyboard.
/// </summary>
/// <returns></returns>
Keyboard* InputManager::GetKeyboard()
{
	for (int i = 0; i < devices.size(); ++i)
	{
		if (static_cast<Keyboard*>(devices[i])) 
		{
			return static_cast<Keyboard*>(devices[i]);
		}
	}
}