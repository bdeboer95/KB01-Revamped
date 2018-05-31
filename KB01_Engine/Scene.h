#ifndef __SCENE_H__
#define __SCENE_H__

#include "Entity.h"
#include <vector>
#include "Skybox.h"
#include "Terrain.h"

class Camera;
class Scene
{
private: 
	Terrain* _terrain;
	Skybox* _skybox;
	Camera* _camera;
	std::vector<Entity*> _entityModels;
	std::vector<std::string> _meshNames;
	std::vector<std::string> _textureNames;
	std::vector<float> _positioning;
	HWND _hWnd;
	int _levelIndex;
	bool _splitted = false;
	//D3DVIEWPORT9 _viewPort;

public:
	Scene(int _levelIndex, HWND _hWnd, std::string _level);
	~Scene();

	Terrain* GetTerrain(); //gets the terrain entity on the scene
	Entity* CreateEntityModel(std::string _meshName, std::string _textureName,float _positionX, float _positionY, float _positionZ);
	void CreateViewPort(RECT _rect);
	HRESULT SetupGeometry(ResourceManager* _resourceManager, Renderer* _renderer);
	void DeleteViewPort();
	void SetUpCamera(Renderer* _renderer);
	int GetLevelIndex();
	Skybox* GetSkyBox();
	HWND GetHandler();
	void Render(Renderer* _renderer);
	void ChangeRotation(Renderer* _renderer, int _rotation);
	std::vector<Entity*> GetEntityModels();
	void ReadLevelFile(std::string fileName);

};

#endif