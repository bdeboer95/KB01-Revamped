#include "stdafx.h"
#include "CppUnitTest.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "Kernel.h"

namespace KB01EngineTest
{

	TEST_CLASS(InputManagerTest)
	{
	public:

		/// <summary>
		/// Creates the new keyboard.
		/// </summary>
		TEST_METHOD(CreateNewKeyboard)
		{
			InputManager* inputManager = new InputManager();
			WindowManager* windowManager = new WindowManager();
			RECT rect = { 100, 100, 600, 600 };
			Window* window = windowManager->CreateNewWindow(rect, "InputManagerTest - CreateNewKeyboard");
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(inputManager->CreateKeyboard(window->GetHandler()));
			Log::Instance()->LogMessage("InputManagerTest", Log::MESSAGE_INFO);
		}

		TEST_METHOD(CreateNewMouse)
		{
			InputManager* inputManager2 = new InputManager();
			WindowManager* windowManager2 = new WindowManager();
			RECT rect2 = { 200, 200, 500, 500 };
			Window* window = windowManager2->CreateNewWindow(rect2, "InputManagerTest - CreateNewMouse");
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(inputManager2->CreateMouse(window->GetHandler()));
		}
	};
}