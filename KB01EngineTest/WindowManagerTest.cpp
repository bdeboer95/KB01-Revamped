#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\KB01_engine\Window.h"
#include "..\KB01_engine\WindowManager.h"
#include <string>
#include "..\KB01_engine\Log.h"

namespace KB01EngineTest
{
	TEST_CLASS(WindowManagerTest)
	{
	public:

		TEST_METHOD(CreateNewWindow)
		{
			WindowManager* windowManager = new WindowManager();
			RECT rect = { 100, 100, 100, 500 };
			Window* window = windowManager->CreateNewWindow(rect, "WindowManagerTest_CreateWindow");
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(window);
		}

		TEST_METHOD(CreateMultipleWindows)
		{
			WindowManager* windowManager5 = new WindowManager();
			RECT rect7 = { 200, 200, 600, 600 };
			RECT rect8 = { 300, 300, 700, 700 };
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(windowManager5->CreateNewWindow(rect7, "WindowManagerTest - CreateMultipleWindows"));
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(windowManager5->CreateNewWindow(rect8, "WindowManagerTest - CreateMultipleWindows"));
		}

		TEST_METHOD(GetActiveWindow)
		{
			WindowManager* windowManager2 = new WindowManager();
			RECT rect2 = { 100, 100, 100, 500 };
			windowManager2->CreateNewWindow(rect2, "WindowManagerTest - GetActiveWindow");
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(windowManager2->GetActiveWindow());
		}

	};
}