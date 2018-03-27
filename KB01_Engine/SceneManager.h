#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Scene.h"
#include "InputManager.h"

class SceneManager 
{
private:
	std::vector<Scene*> scenes;
	void				DeleteAllScenes();

public:
	SceneManager();
	~SceneManager();

	void				SplitScenes(std::vector<Scene*> _splitScenes, RECT _rectangleBackBuffer);
	Scene*				CreateScene(int _levelIndex, HWND _hWnd, std::string _level);
	void				Cleanup();
	void				DrawScene(Renderer* _renderer);
	HRESULT				PrepareScenes(ResourceManager* resourceManager, Renderer* _renderer);
	std::vector<Scene*> GetScenesByLevelIndex(int _levelIndex);
	void				AddListener(InputManager* _inputManager);
};

#endif