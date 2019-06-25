#ifndef __SCENE_H__
#define __SCENE_H__

#include "Entity.h"
#include <vector>
#include "Skybox.h"
#include "Terrain.h"

class Camera;
class EntityModel;

/// <summary>
/// The scene is the complete picture that the user sees while playing the game, including the sky, the ground and the entities on it
/// </summary>
class Scene
{
private: 
	Terrain*					_terrain;							//the ground element for the game
	Skybox*						_skybox;							//the sky element for the game
	Camera*						 _camera;							//the camera through which the player of the game is looking through
	std::vector<Entity*>		_entityModels;						//The collection with entities that are displayed on the scene, f.e a tiger or a person
	std::vector<std::string>	_meshNames;
	HWND						_hWnd;
								
	void						LoadSceneFromFile(std::string level);
	void						GetEntityModelFromFile(std::string line);
	void						GetTerrainFromFile(std::string line);
	void						GetSkyBoxFromFile(std::string line);
								
public:							
								Scene(HWND hWnd, std::string level);														//Constructor
								~Scene();																						//Destructor
	Terrain*					GetTerrain();														//gets the terrain entity on the scene
	Entity*						CreateEntityModel(std::string meshName, std::string textureName,float _positionX, float _positionY, float _positionZ, Vector3 scaleVector);
	HRESULT						SetupGeometry(ResourceManager* resourceManager, Renderer* renderer);
	void						SetUpCamera(Renderer* renderer);
	Skybox*						GetSkyBox();
	HWND						GetHandler();
	void						Render(Renderer* renderer); //Render all the entities that a scene contains one for one
	std::vector<Entity*>		GetEntityModels();			//Get the entity models belonging to that scene
};

#endif