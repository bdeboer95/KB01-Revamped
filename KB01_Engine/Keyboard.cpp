#include "Keyboard.h"
#include "Log.h"
#include <dinput.h>
#include <iostream>

/// <summary>
/// Initializes a new instance of the <see cref="Keyboard"/> class.
/// </summary>
Keyboard::Keyboard()
{
	//TODO
}

/// <summary>
/// Initializes a new instance of the <see cref="Keyboard"/> class.
/// </summary>
/// <param name="_hwnd">The _HWND.</param>
Keyboard::Keyboard(HWND _hwnd)
{
	Log::Instance()->LogMessage("Keyboard - Created.", Log::MESSAGE_INFO);
	directInput = NULL;
	keyboard = NULL;
	hwnd = _hwnd;

	InitDevice();
}

/// <summary>
/// Finalizes an instance of the <see cref="Keyboard"/> class.
/// </summary>
Keyboard::~Keyboard()
{
	ReleaseDevice();
	Log::Instance()->LogMessage("~Keyboard - Keyboard cleaned up!", Log::MESSAGE_INFO);
}

/// <summary>
/// Initializes the device.
/// </summary>
/// <returns></returns>
bool Keyboard::InitDevice()
{
	HRESULT create = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, NULL);
	
	if (directInput == NULL)
	{
		//Log error
		Log::Instance()->LogMessage("Keyboard - DirectInput is NULL.", Log::MESSAGE_ERROR);
		return false;
	}

	create = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	
	if FAILED(create)
	{
		Log::Instance()->LogMessage("Keyboard - Failed to CreateDevice.", Log::MESSAGE_ERROR);
		ReleaseDevice();
		return false;
	}

	//http://www.falloutsoftware.com/tutorials/di/di2.htm
	create = keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	
	if FAILED(create)
	{
		Log::Instance()->LogMessage("Keyboard - Failed to SetCooperativeLevel.", Log::MESSAGE_ERROR);
		ReleaseDevice();
		return false;
	}

	create = keyboard->SetDataFormat(&c_dfDIKeyboard);
	
	if FAILED(create)
	{
		Log::Instance()->LogMessage("Keyboard - Failed to SetDataFormat.", Log::MESSAGE_ERROR);
		ReleaseDevice();
		return false;
	}

	create = keyboard->Acquire();
	
	if FAILED(create)
	{
		Log::Instance()->LogMessage("Keyboard - Failed to Acquire keyboard.", Log::MESSAGE_WARNING);
		return false;
	}

	AcquireDevice();

	return true;
}

/// <summary>
/// Acquires the device.
/// </summary>
/// <returns></returns>
bool Keyboard::AcquireDevice()
{
	int times = 5;

	for (int i = 0; i < times; i++)
	{
		if (SUCCEEDED(keyboard->Acquire()))
		{
			Log::Instance()->LogMessage("Keyboard - Succesfully Acquired.", Log::MESSAGE_INFO);
			return true;
		}
	}

	return false;
}

/// <summary>
/// Releases the device.
/// </summary>
void Keyboard::ReleaseDevice()
{
	if (directInput)
	{
		Log::Instance()->LogMessage("Keyboard - Released DirectInput.", Log::MESSAGE_INFO);
		directInput->Release();
		directInput = NULL;
	}

	if (keyboard)
	{
		Log::Instance()->LogMessage("Keyboard - Released keyboard.", Log::MESSAGE_INFO);
		keyboard->Unacquire();
		keyboard->Release();
		keyboard = NULL;
	}
}

/// <summary>
/// Polls the device.
/// </summary>
/// <returns></returns>
HRESULT Keyboard::PollDevice()
{
	return keyboard->Poll();
}

/// <summary>
/// Devices the state.
/// </summary>
/// <returns></returns>
byte* Keyboard::DeviceState()
{
	keyboard->GetDeviceState(sizeof(state), (LPVOID)&state);
	return state;
}

byte Keyboard::KeyAlreadyPressed()
{
	return state[0x1E];
}