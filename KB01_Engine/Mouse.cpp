#include "Mouse.h"
#include "Log.h"

/// <summary>
/// Initializes a new instance of the <see cref="Mouse"/> class.
/// </summary>
/// <param name="_hwnd">The _HWND.</param>
Mouse::Mouse(HWND _hwnd)
{
	const int MOUSEBUFFER	= 16;
	//Data needed to set the mouse 
	dipdw.diph.dwSize		= sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj		= 0;
	dipdw.diph.dwHow		= DIPH_DEVICE;
	dipdw.dwData			= MOUSEBUFFER;

	input = NULL;
	device = NULL;
	window = _hwnd;
	ResetStruct();

	InitDevice();

	Log::Instance()->LogMessage("Mouse - Created.", Log::MESSAGE_INFO);
}

/// <summary>
/// Finalizes an instance of the <see cref="Mouse"/> class.
/// </summary>
Mouse::~Mouse()
{
	ReleaseDevice();
	Log::Instance()->LogMessage("~Mouse - Mouse cleaned up!", Log::MESSAGE_INFO);
}

/// <summary>
/// Sets the mouse buffer.
/// </summary>
void Mouse::SetMouseBuffer()
{
	DIDEVICEOBJECTDATA od;
	DWORD elements = 1;

	HRESULT hr = device->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), &od, &elements, 0);

	switch (od.dwOfs)
	{
	case DIMOFS_X:
		bufferedMouse.positionX += static_cast<long>(od.dwData);
		break;
	case DIMOFS_Y:
		bufferedMouse.positionY += static_cast<long>(od.dwData);
		break;
	case DIMOFS_BUTTON1:
		if (static_cast<long>(od.dwData) == 0)
		{
			bufferedMouse.button1 = false;
		}
		else
		{
			bufferedMouse.button1 = true;
		}
		break;
	case DIMOFS_BUTTON2:
		if (static_cast<long>(od.dwData) == 0)
		{
			bufferedMouse.button2 = false;
		}
		else
		{
			bufferedMouse.button2 = true;
		}
		break;
	case DIMOFS_BUTTON3:
		if (static_cast<long>(od.dwData) == 0)
		{
			bufferedMouse.button3 = false;
		}
		else
		{
			bufferedMouse.button3 = true;
		}
		break;
	case DIMOFS_BUTTON4:
		if (static_cast<long>(od.dwData) == 0)
		{
			bufferedMouse.button4 = false;
		}
		else
		{
			bufferedMouse.button4 = true;
		}
		break;
	case DIMOFS_BUTTON5:
		if (static_cast<long>(od.dwData) == 0)
		{
			bufferedMouse.button5 = false;
		}
		else
		{
			bufferedMouse.button5 = true;
		}
		break;
	case DIMOFS_BUTTON6:
		if (static_cast<long>(od.dwData) == 0)
		{
			bufferedMouse.button6 = false;
		}
		else
		{
			bufferedMouse.button6 = true;
		}
		break;
	case DIMOFS_BUTTON7:
		if (static_cast<long>(od.dwData) == 0)
		{
			bufferedMouse.button7 = false;
		}
		else
		{
			bufferedMouse.button7 = true;
		}
		break;
	case DIMOFS_Z:
		bufferedMouse.z += static_cast<long>(od.dwData);
		break;
	}
}

/// <summary>
/// Resets the structure.
/// </summary>
void Mouse::ResetStruct()
{
	bufferedMouse.positionX = 0;
	bufferedMouse.positionY = 0;
	bufferedMouse.z = 0;
	bufferedMouse.button0 = false;
	bufferedMouse.button1 = false;
	bufferedMouse.button2 = false;
	bufferedMouse.button3 = false;
	bufferedMouse.button4 = false;
	bufferedMouse.button5 = false;
	bufferedMouse.button6 = false;
	bufferedMouse.button7 = false;
}

/// <summary>
/// Initializes the device.
/// </summary>
/// <returns></returns>
bool Mouse::InitDevice()
{
	HRESULT create = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&input, NULL);
	
	if (input == NULL)
	{
		Log::Instance()->LogMessage("Mouse - DirectInput is NULL.", Log::MESSAGE_ERROR);
		return false;
	}

	create = input->CreateDevice(GUID_SysMouse, &device, NULL);
	
	if FAILED(create)
	{
		Log::Instance()->LogMessage("Mouse - Failed to CreateDevice.", Log::MESSAGE_ERROR);
		ReleaseDevice();
		return false;
	}

	create = device->SetCooperativeLevel(window, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	
	if FAILED(create)
	{
		Log::Instance()->LogMessage("Mouse - Failed to SetCooperativeLevel.", Log::MESSAGE_ERROR);
		ReleaseDevice();
		return false;
	}

	create = device->SetDataFormat(&c_dfDIMouse);
	
	if FAILED(create)
	{
		Log::Instance()->LogMessage("Mouse - Failed to SetDataFormat.", Log::MESSAGE_ERROR);
		ReleaseDevice();
		return false;
	}

	create = device->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	
	if FAILED(create)
	{
		Log::Instance()->LogMessage("Mouse - Failed to SetProperty.", Log::MESSAGE_ERROR);
		return false;
	}

	create = device->Acquire();
	
	if FAILED(create)
	{
		Log::Instance()->LogMessage("Mouse - Failed to Acquire mouse.", Log::MESSAGE_ERROR);
		return false;
	}

	AcquireDevice();

	return false;
}

/// <summary>
/// Acquires the device.
/// </summary>
/// <returns></returns>
bool Mouse::AcquireDevice()
{
	int times = 5;

	for (int i = 0; i < times; ++i)
	{
		if (SUCCEEDED(device->Acquire()))
		{
			Log::Instance()->LogMessage("Mouse - Succesfully Acquired.", Log::MESSAGE_INFO);
			return true;
		}
	}

}

/// <summary>
/// Releases the device.
/// </summary>
void Mouse::ReleaseDevice()
{
	if (input)
	{
		Log::Instance()->LogMessage("Mouse - Released DirectInput.", Log::MESSAGE_INFO);
		input->Release();
		input = NULL;
	}

	if (device)
	{
		Log::Instance()->LogMessage("Mouse - Released mouse.", Log::MESSAGE_INFO);
		device->Unacquire();
		device->Release();
		device = NULL;
	}
}

/// <summary>
/// Polls the device.
/// </summary>
/// <returns></returns>
HRESULT Mouse::PollDevice()
{
	return device->Poll();
}

/// <summary>
/// Devices the state.
/// </summary>
/// <returns></returns>
DIMOUSESTATE Mouse::GetMouseState()
{
	DIMOUSESTATE mouseState;
	device->GetDeviceState(sizeof(mouseState), (LPVOID)&mouseState);
	return mouseState;
}

/// <summary>
/// Gets the mouse input.
/// </summary>
/// <returns></returns>
Mouse::MouseStruct Mouse::GetMouseInput()
{
	if (!SUCCEEDED(device->Poll()))
	{
		AcquireDevice();
	}

	SetMouseBuffer();

	return bufferedMouse;
}