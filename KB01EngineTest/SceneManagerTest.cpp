#include "stdafx.h"
#include "CppUnitTest.h"
#include "SceneManager.h"
#include "WindowManager.h"

namespace KB01EngineTest
{
	TEST_CLASS(SceneManagerTest)
	{
	public:

		TEST_METHOD(MakeScene)
		{
			SceneManager* sceneManager = new SceneManager();
			WindowManager* windowManager = new WindowManager();
			RECT rect = { 100, 100, 500, 500 };
			Window* window = windowManager->CreateNewWindow(rect, "Window");
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(sceneManager->CreateScene(1, window->GetHandler(), "level1.txt"));
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(1, sceneManager->CreateScene(1, window->GetHandler(), "level1.txt")->GetLevelIndex());
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(window);
		}

	};
}