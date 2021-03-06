#ifndef __SCENE_H__
#define __SCENE_H__

#include "Entity.h"
#include <vector>
#include "Skybox.h"
#include "Terrain.h"

class Camera;

/**
**Name: Scene
**Description: The scene is the complete picture that the user sees while playing the game, including the sky, the ground and the entities onit
**
*/
class Scene
{
private: 
	Terrain* _terrain; //the ground element for the game
	Skybox* _skybox; //the sky element for the game
	Camera* _camera; //the camera through which the player of the game is looking through
	std::vector<Entity*> entityModels; //The collection with entities that are displayed on the scene, f.e a tiger or a person
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
};

#endif