#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Scene.h"
#include "Camera.h"
#include "InputManager.h"
#include "WindowManager.h"

class SceneManager
{
private:
	std::vector<Scene*> scenes;
	int rotation; 
	void DeleteAllScenes();

public:
	SceneManager();
	~SceneManager();

	void SplitScenes(std::vector<Scene*> _splitScenes, RECT _rectangleBackBuffer);
	Scene* CreateScene(int _levelIndex, HWND _hWnd, std::string _level);
	void Cleanup();
	void DrawScene(Renderer* _renderer);
	HRESULT	PrepareScenes(ResourceManager* resourceManager, Renderer* _renderer);
	std::vector<Scene*> GetScenesByLevelIndex(int _levelIndex);
	void SetRotation(int _rotation);
	int GetRotation();
	void AddListener(InputManager* _inputManager);

};

#endif