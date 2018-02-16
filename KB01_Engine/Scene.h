#ifndef __SCENE_H__
#define __SCENE_H__

#include "Camera.h"
#include "EntityModel.h"
#include <vector>
#include "Skybox.h"
#include "Terrain.h"

class Scene
{
private: 
	Terrain* terrain;
	Skybox* skybox;
	std::vector<Entity*> entityModels;
	std::vector<std::string> meshNames;
	std::vector<std::string> textureNames;
	std::vector<float> positioning;
	HWND hWnd;
	int levelIndex;
	bool splitted = false;
	D3DVIEWPORT9 viewPort;
	
	void SceneLoader(std::string _level);
	void GetEntityModelFromFile(std::string line);
	void GetPositionFromFile(std::string line);
	void GetMeshNameFromFile(std::string line);
	void GetTextureNameFromFile(std::string line);

public:
	Scene(int _levelIndex, HWND _hWnd, std::string _level);
	~Scene();
	EntityModel* CreateEntityModel(std::string _meshName, std::string _textureName,float _positionX, float _positionY, float _positionZ);
	void CreateViewPort(RECT _rect);
	HRESULT SetupGeometry(ResourceManager* _resourceManager, Renderer* _renderer);
	void DeleteViewPort();
	void SetUpCamera(Renderer* _renderer);
	int GetLevelIndex();
	HWND GetHandler();
	void Render(Renderer* _renderer);
	void ChangeRotation(Renderer* _renderer, int _rotation);
	std::vector<Entity*> GetEntityModels();
};

#endif