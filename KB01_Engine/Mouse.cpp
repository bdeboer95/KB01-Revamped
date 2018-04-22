#include "Mouse.h"
#include "Log.h"
#include "InputListener.h"
#include <iostream> //TODO
#include <math.h>

/// <summary>
/// Initializes a new instance of the <see cref="Mouse"/> class.
/// </summary>
/// <param name="_hwnd">The _HWND.</param>
Mouse::Mouse(HWND _hwnd)
{
	const int MOUSEBUFFER = 16;
	//Data needed to set the mouse 
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = MOUSEBUFFER;
	mouseCoordinates.x = 0;
	mouseCoordinates.y = 0;

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
			mouseCoordinates.x = GetMouseState().lX;
			mouseCoordinates.y = GetMouseState().lY;
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
///Gets the current positioning and buttonclicks of the mouses
/// </summary>
/// <returns></returns>
MouseState Mouse::GetMouseState()
{
	device->GetDeviceState(sizeof(mouseState), (LPVOID)&mouseState);
	return mouseState;
}

/// <summary>
/// Notifies all the inputlisteners that a key has been pressed
/// </summary>
/// <returns></returns>
void Mouse::NotifyListeners(std::vector<InputListener*> listeners)
{
	RECT rect;
	int width = 0;
	int height = 0;
	if (GetWindowRect(window, &rect))
	{
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}
	MouseState currentState = GetMouseState();
	float distance = mouseCoordinates.x + currentState.lX;
	float distanceY = mouseCoordinates.y + currentState.lY;
	/*std::cout << GetMouseState().lX << std::endl;*/

	for (int i = 0; i < listeners.size(); i++)
	{
		if (distance < mouseCoordinates.x || distance < mouseCoordinates.x ||distanceY < mouseCoordinates.y ||distanceY > mouseCoordinates.y) {
			float deltaY = GetMouseState().lY - mouseCoordinates.y;
			float deltaX = GetMouseState().lX - mouseCoordinates.x;
			float angle = (float)atan2(deltaY, deltaX);

			float rotationY = cos(angle) * 0.01f;
			float rotationX = sin(angle) * 0.01f;
			if (rotationY >= 6.28f)
				rotationY = 0.0f;

			if (rotationX >= 6.28f)
				rotationX = 0.0f;
			
			listeners[i]->Notify(TRANSFORMATIONEVENT::ROTATE_LEFT, rotationX, rotationY);
			mouseCoordinates.x = currentState.lX;
			mouseCoordinates.y = currentState.lY;
		}
	}
}
/*mouseCoordinates.x -= GetMouseState().lX;

mouseCoordinates.y += GetMouseState().lY;*/





//	if (mouseCoordinates.y < 0) {
//		mouseCoordinates.x = 0;
//	listeners[i]->Notify(TRANSFORMATIONEVENT::ROTATE_LEFT, 0.001f, 1.0f);*/
//}



//	if (mouseCoordinates.x > height) {
//		mouseCoordinates.y += (float)height;
//		
//		/*listeners[i]->Notify(TRANSFORMATIONEVENT::ROTATE_LEFT, 0.001f, 1.0f);*/
//	}
//	
//	if (mouseCoordinates.y < 0) {
//		mouseCoordinates.y += 0;
///*		listeners[i]->Notify(TRANSFORMATIONEVENT::ROTATE_LEFT, 0.001f, 1.0f);*/
//	}

	//listeners[i]->Notify(TRANSFORMATIONEVENT::ROTATE_LEFT, rotationX, rotationY);

	/*if (IsKeyDown(KEYCODE::S)) {
		listeners[i]->Notify(TRANSFORMATIONEVENT::MOVE_FORWARD);
	}
	if (IsKeyDown(KEYCODE::D)) {
		listeners[i]->Notify(TRANSFORMATIONEVENT::MOVE_LEFT);
	}
	if (IsKeyDown(KEYCODE::A)) {
		listeners[i]->Notify(TRANSFORMATIONEVENT::MOVE_RIGHT);
	}*/

	//}
	/*for (int i = 0; i < listeners.size(); i++) {
		if (GetMouseState().lX < 0) {
			listeners[i]->Notify(TRANSFORMATIONEVENT::MOVE_RIGHT);
		}
		if (GetMouseState().lX > 0) {
			listeners[i]->Notify(TRANSFORMATIONEVENT::MOVE_LEFT);
		}
	}*/
	/*for (int i = 0; i < listeners.size(); i++) {

	}*/



	//}

	///// <summary>
	///// Gets the mouse input.
	///// </summary>
	///// <returns></returns>
	//Mouse::MouseStruct Mouse::GetMouseInput()
	//{
	//	if (!SUCCEEDED(device->Poll()))
	//	{
	//		AcquireDevice();
	//	}
	//
	//	SetMouseBuffer();
	//
	//	return bufferedMouse;
	//}