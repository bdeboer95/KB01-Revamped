#include "stdafx.h"
#include "CppUnitTest.h"
#include "RendererDx.h"
#include "Window.h"
#include "WindowManager.h"

namespace KB01EngineTest
{
	TEST_CLASS(RendererDxTest)
	{
	public:

		TEST_METHOD(InitDevice)
		{
			Renderer* renderer = new RendererDx();
			WindowManager* windowManager = new WindowManager();
			RECT rect = { 100, 100, 500, 500 };
			Window* window = windowManager->CreateNewWindow(rect, "window");
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(renderer->GetDevice());
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(true, renderer->InitDevice(window->GetHandler()));
		}

	};
}