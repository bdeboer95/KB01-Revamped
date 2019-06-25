#include "SceneManager.h"
#include "EntityModel.h"
#include "Camera.h"

#include <vector>


/// <summary>
/// Initializes a new instance of the <see cref="SceneManager"/> class.
/// </summary>
SceneManager::SceneManager()
{
	Log::Instance()->LogMessage("SceneManager - SceneManager created", Log::MESSAGE_INFO);
}

/// <summary>
/// Finalizes an instance of the <see cref="SceneManager"/> class.
/// </summary>
SceneManager::~SceneManager()
{
	DeleteAllScenes();
	Log::Instance()->LogMessage("~SceneManager - SceneManager cleaned up!", Log::MESSAGE_INFO);
}



/// <summary>
/// Creates the scene.
/// </summary>
/// <param name="_levelIndex">Index of the _level.</param>
Scene* SceneManager::CreateScene(int _levelIndex, HWND _hWnd, std::string _level)
{
	Scene* scene = new Scene( _hWnd, _level);
	scenes.push_back(scene);

	Log::Instance()->LogMessage("Scene created", Log::MessageType::MESSAGE_INFO);
	return scene;
}
/// <summary>
/// Prepares the scenes by showing the window and setting up the geometry
/// </summary>
/// <param name="_resourceManager"></param>
/// <param name="_renderer"></param>
/// <returns></returns>
HRESULT SceneManager::PrepareScenes(ResourceManager* _resourceManager, Renderer* _renderer)
{
	for each(Scene* scene in scenes)
	{
		if (FAILED(scene->SetupGeometry(_resourceManager, _renderer)))
		{
			Log::Instance()->LogMessage("SceneManager - Failed to setup Geometry.", Log::MESSAGE_ERROR);
			return E_FAIL;
		}

		ShowWindow(scene->GetHandler(), SW_MAXIMIZE);
		UpdateWindow(scene->GetHandler());
	}

	return S_OK;
}

/// <summary>
/// Draws the scene.
/// </summary>
void SceneManager::DrawScene(Renderer* _renderer)
{
	for each(Scene* scene in scenes)
	{
		scene->Render(_renderer);
	}
}


/// <summary>
/// Deletes all scenes.
/// </summary>
void SceneManager::DeleteAllScenes()
{
	while (!scenes.empty())
	{
		delete scenes.back();
		scenes.pop_back();
	}
}

/// <summary>
/// Deletes all pointers and variables that can cause memory leaks
/// </summary>
void SceneManager::Cleanup()
{
	DeleteAllScenes();
}

/// <summary>
/// Adds the listeners.
/// </summary>
/// <param name="_inputManager">The _input manager.</param>
void SceneManager::AddListener(InputManager* _inputManager)
{
	for each (Scene* scene in scenes)
	{
		_inputManager->AddListener(scene->GetSkyBox());
		_inputManager->AddListener(scene->GetTerrain());
		for each (Entity* entityModel in scene->GetEntityModels())
		{
			if (dynamic_cast<EntityModel*>(entityModel))
			{
				EntityModel* e = dynamic_cast<EntityModel*>(entityModel);
				_inputManager->AddListener(e);
			}
		}
	}
}