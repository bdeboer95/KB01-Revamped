#ifndef __SCENEMANAGERFACADE_H__
#define __SCENEMANAGERFACADE_H__

#include "SceneManager.h"

class SceneManagerFacade
{
private: 
	SceneManager* sceneManager;

public:
	SceneManagerFacade();
	~SceneManagerFacade();
	void PrepareScenes(ResourceManager* _resourceManager, Renderer* _renderer);
	void DrawScenes(Renderer* _renderer);
	Scene* CreateScene(int _levelIndex, HWND _handler, std::string _level);
};

#endif