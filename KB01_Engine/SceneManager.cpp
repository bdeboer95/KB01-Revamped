//-----------------------------------------------------------------------------
// File: ResourceManager.cpp
//
// Desc: 
//-----------------------------------------------------------------------------

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
/// Splits the scenes.
/// </summary>
/// <param name="_splitScenes">The _split scenes.</param>
/// <param name="_rectangleBackBuffer">The _rectangle back buffer.</param>
void SceneManager::SplitScenes(std::vector<Scene*> _splitScenes, RECT _rectangleBackBuffer)
{
	// Represents the backbuffer on the window
	RECT rectangleSplitScene;
	for (int i = 0; i < _splitScenes.size(); i++)
	{
		rectangleSplitScene.left = 0;

		if (i != 0)
		{
			rectangleSplitScene.top = i*(_rectangleBackBuffer.bottom / _splitScenes.size());
		}
		else
		{
			rectangleSplitScene.top = 0;
		}

		rectangleSplitScene.right = _rectangleBackBuffer.right;
		rectangleSplitScene.bottom = _rectangleBackBuffer.bottom / _splitScenes.size();

		_splitScenes[i]->CreateViewPort(rectangleSplitScene);
	}
}

/// <summary>
/// Creates the scene.
/// </summary>
/// <param name="_levelIndex">Index of the _level.</param>
Scene* SceneManager::CreateScene(int _levelIndex, HWND _hWnd, std::string _level)
{
	Scene* scene = new Scene(_levelIndex, _hWnd, _level);
	scenes.push_back(scene);

	Log::Instance()->LogMessage("Scene created", Log::MessageType::MESSAGE_INFO);
	return scene;
}

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
/// Gets the index of the scenes by level.
/// </summary>
/// <param name="_levelIndex">Index of the _level.</param>
/// <returns></returns>
std::vector<Scene*> SceneManager::GetScenesByLevelIndex(int _levelIndex)
{
	std::vector<Scene*> indexScenes;

	for each(Scene* scene in scenes)
	{
		if (scene->GetLevelIndex() == _levelIndex)
		{
			indexScenes.push_back(scene);
		}
	}

	return indexScenes;
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
/// Cleanups this instance.
/// </summary>
void SceneManager::Cleanup()
{

}

/// <summary>
/// Adds the listener.
/// </summary>
/// <param name="_inputManager">The _input manager.</param>
void SceneManager::AddListener(InputManager* _inputManager)
{
	for each (Scene* scene in scenes)
	{
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