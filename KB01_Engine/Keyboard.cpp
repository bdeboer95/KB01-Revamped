#include "Keyboard.h"
#include "Log.h"

/// <summary>
/// Initializes a new instance of the <see cref="Keyboard"/> class.
/// </summary>
/// <param name="_hwnd">The _HWND.</param>
Keyboard::Keyboard(HWND _hwnd)
{
	input = NULL;
	device = NULL;
	window = _hwnd;

	InitDevice();

	Log::Instance()->LogMessage("Keyboard - Created.", Log::MESSAGE_INFO);
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
	HRESULT create = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&device, NULL);
	
	if (device == NULL)
	{
		//Log error
		Log::Instance()->LogMessage("Keyboard - DirectInput is NULL.", Log::MESSAGE_ERROR);
		return false;
	}

	create = input->CreateDevice(GUID_SysKeyboard, &device, NULL);
	
	if FAILED(create)
	{
		Log::Instance()->LogMessage("Keyboard - Failed to CreateDevice.", Log::MESSAGE_ERROR);
		ReleaseDevice();
		return false;
	}

	//http://www.falloutsoftware.com/tutorials/di/di2.htm
	create = device->SetCooperativeLevel(window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	
	if FAILED(create)
	{
		Log::Instance()->LogMessage("Keyboard - Failed to SetCooperativeLevel.", Log::MESSAGE_ERROR);
		ReleaseDevice();
		return false;
	}

	create = device->SetDataFormat(&c_dfDIKeyboard);
	
	if FAILED(create)
	{
		Log::Instance()->LogMessage("Keyboard - Failed to SetDataFormat.", Log::MESSAGE_ERROR);
		ReleaseDevice();
		return false;
	}

	create = device->Acquire();
	
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
		if (SUCCEEDED(device->Acquire()))
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
	if (input)
	{
		Log::Instance()->LogMessage("Keyboard - Released DirectInput.", Log::MESSAGE_INFO);
		input->Release();
		input = NULL;
	}

	if (device)
	{
		Log::Instance()->LogMessage("Keyboard - Released keyboard.", Log::MESSAGE_INFO);
		device->Unacquire();
		device->Release();
		device = NULL;
	}
}

/// <summary>
/// Polls the device.
/// </summary>
/// <returns></returns>
HRESULT Keyboard::PollDevice()
{
	return device->Poll();
}

/// <summary>
/// Devices the state.
/// </summary>
/// <returns></returns>
byte* Keyboard::GetKeyboardState()
{
	byte state[256];
	device->GetDeviceState(sizeof(state), (LPVOID)&state);
	return state;
}