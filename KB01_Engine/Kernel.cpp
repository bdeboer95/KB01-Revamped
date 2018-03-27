//-----------------------------------------------------------------------------
// File: Kernel.cpp
//

//
// Desc: 
//-----------------------------------------------------------------------------
#include "Kernel.h"

#include <iostream>
#include <vector>

#include "wtypes.h"

#define KEYDOWN(name, key) (name[key])
#define MSTATE(name, key) (name[key])

/// <summary>
/// Initializes a new instance of the <see cref="Kernel"/> class.
/// </summary>
Kernel::Kernel()
{
	Log::Instance()->LogMessage("Kernel - Created.", Log::MESSAGE_INFO);
	Init();
}

/// <summary>
/// Finalizes an instance of the <see cref="Kernel"/> class.
/// </summary>
Kernel::~Kernel()
{
	DeleteAllManagers();
	Log::Instance()->LogMessage("~Kernel - Everything is cleaned up!", Log::MESSAGE_INFO);
	std::exit(0);
}

/// <summary>
/// Initializes this instance.
/// </summary>
void Kernel::Init()
{
	windowManager = new WindowManager();
	sceneManager = new SceneManager();
	resourceManager = new ResourceManager();
	inputManager = new InputManager();
	renderer = new RendererDx();

	Log::Instance()->LogMessage("Kernel - Scene-, Resource-, WindowManager created.", Log::MESSAGE_INFO);
}

/// <summary>
/// Loads the level.
/// </summary>
/// <param name="_level">The _level.</param>
void Kernel::LoadLevel(const std::string &_level)
{
	Log::Instance()->LogMessage("Kernel - Loading level...", Log::MESSAGE_INFO);

	//Create windows
	//Source: http://stackoverflow.com/questions/8690619/how-to-get-screen-resolution-in-c
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	RECT rect = { 100, 100, 500, 500 };
	HWND hwnd1 = windowManager->CreateNewWindow(rect, "Choo Choo")->GetHandler(); //std::string, OS--> LPWCSTR
	renderer->InitDevice(hwnd1);
	HWND hwndC = GetConsoleWindow();
	sceneManager->CreateScene(1, hwnd1, _level); //WORdt een methode
	//sceneManager->CreateScene(1, hwnd1, "level1.txt");
	/*sceneManager->CreateScene(0, 255, 255, 1, hwnd1);
	sceneManager->CreateScene(228, 164, 228, 1, hwnd1);*/
	//windowManager->AddScenesToWindow(sceneManager->GetScenesByLevelIndex(1), windowManager->GetActiveWindow()); //windowmanager kan er zelf bij //getscenesbyname (levelfile)
	//sceneManager->SplitScenes(sceneManager->GetScenesByLevelIndex(1),windowManager->GetActiveWindow()->GetRectangleBackBuffer(renderer));
	//RECT rect1 = { 600, 100, 500, 500 };

	//sceneManager->CreateScene( 2, windowManager->CreateNewWindow(desktop, "I'm a train")->GetHandler());
	////sceneManager->CreateScene(240, 164, 240, 2);
	//windowManager->AddScenesToWindow(sceneManager->GetScenesByLevelIndex(2), windowManager->GetActiveWindow());
	//sceneManager->SplitScenes(sceneManager->GetScenesByLevelIndex(2), windowManager->GetActiveWindow()->GetRectangleBackBuffer());
	//RECT rect2 = { 1100, 100, 500, 500 };
	//windowManager->CreateNewWindow(rect2, L"Rolling Rolling Rolling");
	//sceneManager->CreateScene(228, 164, 228, 3);
	//windowManager->AddScenesToWindow(sceneManager->GetScenesByLevelIndex(3), windowManager->GetActiveWindow());
	resourceManager->InitResourceLoader(renderer->GetDevice());
	if (SUCCEEDED(sceneManager->PrepareScenes(resourceManager, renderer)))
	{
		Log::Instance()->LogMessage("Kernel - Scenes are successfully prepared.", Log::MESSAGE_INFO);
	}
	else
	{
		Log::Instance()->LogMessage("Kernel - Failed to prepare the scenes.", Log::MESSAGE_ERROR);
	}

	inputManager = new InputManager(windowManager->GetActiveWindow()->GetHandler());

	if (SUCCEEDED(inputManager->AddListener(this)))
	{
		Log::Instance()->LogMessage("Kernel - Added as listener.", Log::MESSAGE_INFO);
	} 
	else
	{
		Log::Instance()->LogMessage("Kernel - Failed to be added as a listener", Log::MESSAGE_ERROR);
	}

	sceneManager->AddListener(inputManager);

	Log::Instance()->LogMessage("Kernel - Level is successfully loaded.", Log::MESSAGE_INFO);
}

/// <summary>
/// Runs this instance.
/// </summary>
/// <returns></returns>
bool Kernel::Run()
{
	if (!windowManager)
	{
		Log::Instance()->LogMessage("Kernel - WindowManager not responding. Shutting down now.", Log::MESSAGE_ERROR);
		system("pause");
		return false;
	}

	if (!sceneManager)
	{
		Log::Instance()->LogMessage("Kernel - SceneManager not responding. Shutting down now.", Log::MESSAGE_ERROR);
		system("pause");
		return false;
	}

	if (!resourceManager)
	{
		Log::Instance()->LogMessage("Kernel - ResourceManager not responding. Shutting down now.", Log::MESSAGE_ERROR);
		system("pause");
		return false;
	}

	return true;
}

/// <summary>
/// Steps this instance.
/// </summary>
void Kernel::Step()
{
	windowManager->UpdateWindows();
	inputManager->Update();
	sceneManager->DrawScene(renderer);
}
/// <summary>
/// Notifies the specified state.
/// </summary>
/// <param name="state">The state.</param>
void Kernel::Notify(byte state[])
{
	if (KEYDOWN(DIK_A, state))
	{
		std::cout << "DIK_A pressed." << std::endl;
	}

	if (inputManager->GetMouse()->GetMouseState().rgbButtons[0])
	{
		/*std::cout << "LINKS" << std::endl;*/
}

	if (inputManager->GetMouse()->GetMouseState().rgbButtons[1])
{
		std::cout << "RECHTS" << std::endl;;
	}

	if (KEYDOWN(DIK_D, state))
	{
		//windowManager->DeleteWindow(GetActiveWindow());
	}

	if (KEYDOWN(DIK_ESCAPE, state))
	{
		windowManager->DeleteAllWindows();
		delete this;
	}
}

/// <summary>
/// Deletes all managers.
/// </summary>
void Kernel::DeleteAllManagers()
{
	delete windowManager;
	delete resourceManager;
	delete sceneManager;
	delete inputManager;

	delete renderer;

	Log::Instance()->LogMessage("Kernel - Renderer and Managers are deleted.", Log::MESSAGE_INFO);
}