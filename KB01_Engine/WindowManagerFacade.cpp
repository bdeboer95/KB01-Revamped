#include "WindowManagerFacade.h"

/// <summary>
/// Initializes a new instance of the <see cref="WindowManagerFacade"/> class.
/// </summary>
WindowManagerFacade::WindowManagerFacade()
{
	kernel = new Kernel();
	windowManager = new WindowManager();
	sceneManager = new SceneManager();
	renderer = new RendererDx();
	resourceManager = new ResourceManager();
}

/// <summary>
/// Finalizes an instance of the <see cref="WindowManagerFacade"/> class.
/// </summary>
WindowManagerFacade::~WindowManagerFacade()
{
	//TODO
}

/// <summary>
/// Creates the input.
/// </summary>
void WindowManagerFacade::CreateInput()
{
	inputManager = new InputManager(windowManager->GetActiveWindow()->GetHandler());
	inputManager->AddListener(kernel);
	sceneManager->AddListener(inputManager);
}

/// <summary>
/// Creates the new window.
/// </summary>
/// <param name="_name">The _name.</param>
/// <param name="_top">The _top.</param>
/// <param name="_left">The _left.</param>
/// <param name="_bottom">The _bottom.</param>
/// <param name="_right">The _right.</param>
/// <param name="_amountOfScenes">The _amount of scenes.</param>
/// <param name="_levelIndex">Index of the _level.</param>
void WindowManagerFacade::CreateNewWindow(std::string _name, int _top, int _left, int _bottom, int _right, int _amountOfScenes, int _levelIndex)
{
	/*if (_top < 0 || _left < 0 || _bottom < 0 || _right < 0 || _amountOfScenes < 0 || _levelIndex < 0)
	{
		int mb = MessageBox(NULL, L"Specified negative window values.", L"Error", MB_ICONERROR);

		switch (mb)
		{
		case IDOK:
			Log::Instance()->LogMessage("WindowManagerFacade - Specified negative window values.", Log::MESSAGE_ERROR);
			std::exit(0);
		}
	}

	RECT rect = { _top, _left, _bottom, _right };

	for (int i = 0; i < _amountOfScenes; ++i)
	{
		sceneManager->CreateScene(_levelIndex, windowManager->CreateNewWindow(rect, _name)->GetHandler(), "level1.txt");
	}

	windowManager->AddScenesToWindow(sceneManager->GetScenesByLevelIndex(_levelIndex), windowManager->GetActiveWindow());
	
	if (_amountOfScenes > 1)
	{
		sceneManager->SplitScenes(sceneManager->GetScenesByLevelIndex(_levelIndex), windowManager->GetActiveWindow()->GetRectangleBackBuffer(renderer));
	}

	resourceManager->InitResourceLoader(renderer);
	sceneManager->PrepareScenes(resourceManager, renderer);

	if (!inputManager)
	{
		CreateInput();
	}*/
}

/// <summary>
/// Updates the windows.
/// </summary>
void WindowManagerFacade::UpdateWindows()
{
	while (TRUE)
	{
		windowManager->UpdateWindows();
		sceneManager->DrawScene(renderer);
		inputManager->Update();
	}
}