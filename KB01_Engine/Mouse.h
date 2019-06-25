#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "Device.h"
#include "InputListener.h"
#include "Vector2.h"

/// <summary>
/// The state that the mouse is currently in, if it's pressed or if it moved
/// </summary>
struct MouseState {
	LONG    lX;
	LONG    lY;
	LONG    lZ;
	BYTE    rgbButtons[4];
};

/// <summary>
/// The mouse device and it's states if the user moves or presses certain keys
/// </summary>
class Mouse : public Device
{
private:
	MouseState mouseState;											//the buttons that have been pressed or the amount the mouse was moved to the right or left

	struct MouseStruct
	{
		int positionX = 0;
		int positionY = 0;
		int z = 0;
		bool button0 = false;
		bool button1 = false;
		bool button2 = false;
		bool button3 = false;
		bool button4 = false;
		bool button5 = false;
		bool button6 = false;
		bool button7 = false;
	};

	LPDIRECTINPUT8 directInput;										// DirectInput interface
	LPDIRECTINPUTDEVICE8 mouse;										// Mouse device
	HWND hwnd;														// The window that the mouse is moving on
	DIPROPDWORD dipdw;												// The unsigned long property
	MouseStruct bufferedMouse;										// The mouse buffer

	void SetMouseBuffer();											// Set the mouse buffer
	void ResetStruct();												// Reset the mouse struct

public:
	Mouse(HWND _hwnd);												// Constructor
	~Mouse();														// Destructor

	bool InitDevice();												// Initialize the mouse device
	bool AcquireDevice();											// Acquire the mouse device
	void ReleaseDevice();											// Release the mouse device
	HRESULT PollDevice();											// Constantly check the mouse device	
	void NotifyListeners(std::vector<InputListener*> listeners);	// Notify all the listeners that the mouse has been moved or pressed
	MouseState GetMouseState();										// Get the current buttons and positioning of the mouse	
	Vector2 mouseCoordinates;										// The previously saved mousecoordinates


};

#endif