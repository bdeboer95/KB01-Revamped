#include "InputManagerFacade.h"


InputManagerFacade::InputManagerFacade()
{
	inputManager = new InputManager();
}


InputManagerFacade::~InputManagerFacade()
{

}

void InputManagerFacade::CreateDevices(HWND _handler, int amountOfKeyboards)
{
	if (amountOfKeyboards <= 0)
	{
		int mb = MessageBox(NULL, L"Specified an invalid amount of keyboards.", L"Error", MB_ICONERROR);

		switch (mb)
		{
		case IDOK:
			Log::Instance()->LogMessage("InputManagerFacade - Specified an invalid amount of keyboards.", Log::MESSAGE_ERROR);
			std::exit(0);
		}
	}

	for (int i = 0; i < amountOfKeyboards; i++)
	{
		inputManager->CreateKeyboard(_handler);
	}
	inputManager->CreateMouse(_handler);
}