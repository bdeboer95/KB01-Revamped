#include "Scene.h"
#include "EntityModel.h"
#include "Camera.h"
#include <iostream>
#include <sstream>

/// <summary>
/// Initializes a new instance of the <see cref="Scene"/> class.
/// </summary>
/// <param name="_hWnd">The hWND.</param>
/// <param name="_level">The level.</param>
Scene::Scene(HWND hWnd, std::string level)
{
	_hWnd = hWnd;
	Camera* cam = new Camera();
	LoadSceneFromFile(level);
	Log::Instance()->LogMessage("Scene - Scene created.", Log::MESSAGE_INFO);
}

/// <summary>
/// Finalizes an instance of the <see cref="Scene"/> class.
/// </summary>
Scene::~Scene()
{
	/*CreateEntityModel("Tiger.x", "zebra.jpg", 1,-20, 50, Vector3(5, 5, 5));
	CreateEntityModel("Tiger.x", "zebra3.bmp", 6,-20, 50, Vector3(5, 5, 5));
	CreateEntityModel("boxman.x", "tiger.bmp", 11, -20, 50,Vector3(0.1,0.1,0.1));*/
	/*_terrain = new Terrain("terrain.jpg", "terrainbrown.jpg");*/
	Log::Instance()->LogMessage("~Scene - Scene cleaned up!", Log::MESSAGE_INFO);
}

/// <summary>
/// Creates the entity model.
/// </summary>
Entity* Scene::CreateEntityModel(std::string _meshName, std::string _textureName, float _positionX, float _positionY, float _positionZ, Vector3 scaleVector)
{
	EntityModel* entityModel = new EntityModel(_meshName, _textureName, _positionX, _positionY, _positionZ, scaleVector);
	_entityModels.push_back(entityModel);
	Log::Instance()->LogMessage("Scene - EntityModel created", Log::MESSAGE_INFO);
	return entityModel;
}

/// <summary>
/// Setups the geometry of the entities on the scene
/// </summary>
/// <param name="_renderer">The _renderer used to draw the scene.</param>
/// <returns></returns>
HRESULT Scene::SetupGeometry(ResourceManager* resourceManager, Renderer* renderer)
{

	for each(Entity* entityModel in _entityModels)
	{
		if (dynamic_cast<EntityModel*>(entityModel))
		{
			EntityModel* e = dynamic_cast<EntityModel*>(entityModel);
			if (FAILED(e->InitGeometry(resourceManager)))
			{
				Log::Instance()->LogMessage("Scene - Geometry was failed to be set for all entitymodels.", Log::MESSAGE_ERROR);
				return E_FAIL;
			}
		}
	}
	Skybox_Cube sky;
	sky.back = "skybox3_back.tga";
	sky.top = "skybox3_top.tga";
	sky.left = "skybox3_left.tga";
	sky.front = "skybox3_front.tga";
	sky.bottom = "skybox3_bottom.tga";
	sky.right = "skybox3_right.tga";
	_skybox = new Skybox(sky);
	_skybox->InitGeometry(renderer, resourceManager);
	_terrain->LoadTexture(resourceManager);
	_terrain->Initialize(renderer, "heightdata.raw", "terrainbrown.jpg");
	ShowWindow(_hWnd, SW_MAXIMIZE);
	UpdateWindow(_hWnd);
	return S_OK;
}

/// <summary>
/// Gets the handler.
/// </summary>
/// <returns></returns>
HWND Scene::GetHandler()
{
	return _hWnd;
}

/// <summary>
/// Renders the scene with the specified _renderer.
/// </summary>
/// <param name="_renderer">The _renderer.</param>
void Scene::Render(Renderer* renderer)
{
	// Clear the backbuffer and the zbuffer
	renderer->ClearBuffer(200, 200, 200);

	// Begin drawing the scene
	if (FAILED(renderer->BeginScene())) //todo
	{
		Log::Instance()->LogMessage("Scene - BeginScene failed", Log::MESSAGE_ERROR);
	}

	_skybox->Render(renderer);
	_terrain->Render(renderer);
	_camera->SetCamera(renderer);

	for each(Entity* entity in _entityModels)
	{
		if (dynamic_cast<EntityModel*>(entity))
		{
			EntityModel* e = dynamic_cast<EntityModel*>(entity);
			e->SetupMatrices();
			e->Render(renderer);

		}
	}

	// End drawing the scene
	renderer->EndScene();

	// Present the backbuffer contents to the display
	renderer->Present(_hWnd);
}

/// <summary>
/// Gets the entity models.
/// </summary>
/// <returns></returns>
std::vector<Entity*> Scene::GetEntityModels()
{
	return _entityModels;
}

/// <summary>
/// Load the scene through a levelfile
/// </summary>
/// <param name="_level">The level.</param>
void Scene::LoadSceneFromFile(std::string level)
{
	std::ifstream file(level);
	bool successful = file.is_open();

	if (!successful)
	{
		Log::Instance()->LogMessage("Scene - Unable to read level file. (" + level + ")", Log::MESSAGE_WARNING);
	}
	else
	{
		std::string line;
		if (file.good())
		{
			bool emFound = false, posFound = false, mnFound = false, tnFound = false;
			for (std::string line; std::getline(file, line);)
			{
				if (line.find("EntityModel") != std::string::npos)
				{
					GetEntityModelFromFile(line);
					Log::Instance()->LogMessage("Scene - Created entity from levelfile. (" + line + ")", Log::MESSAGE_INFO);
				}
				else if (line.find("Terrain") != std::string::npos)
				{
					GetTerrainFromFile(line);
					Log::Instance()->LogMessage("Scene - Created terrain from levelfile. (" + line + ")", Log::MESSAGE_INFO);
				}
				else if (line.find("Skybox") != std::string::npos)
				{
					GetSkyBoxFromFile(line);
					Log::Instance()->LogMessage("Scene - Created skybox from levelfile. (" + line + ")", Log::MESSAGE_INFO);
				}
			}
		}
	}

	file.close();
}

/// <summary>
/// Get entity model from the file
/// </summary>
/// <param name="line"></param>
void Scene::GetEntityModelFromFile(std::string line)
{
	std::istringstream ss(line);
	std::string str;
	EntityModel* entityModel = NULL;
	enum EntityProperty {
		BEGIN, MESHNAME, TEXTURENAME, POSITIONX, POSITIONY, POSITIONZ, SCALEX, SCALEY, SCALEZ, END
	};
	float x = 0;
	float y = 0;
	float z = 0;
	float scaleX = 0;
	float scaleY = 0;
	float scaleZ = 0;
	std::string fileName;
	std::string textureName;
	EntityProperty entityProperty = EntityProperty::BEGIN;

	while (getline(ss, str, ','))
	{
		switch (entityProperty) {
		case BEGIN:  entityProperty = MESHNAME; break;
		case MESHNAME: fileName = str; entityProperty = TEXTURENAME; break;
		case TEXTURENAME: textureName = str; entityProperty = POSITIONX; break;
		case POSITIONX: x = std::stof(str); entityProperty = POSITIONY; break;
		case POSITIONY: y = std::stof(str); entityProperty = POSITIONZ; break;
		case POSITIONZ:	z = std::stof(str); entityProperty = SCALEX; break;
		case SCALEX:	scaleX = std::stof(str); entityProperty = SCALEY; break;
		case SCALEY:	scaleY = std::stof(str); entityProperty = SCALEZ; break;
		case SCALEZ:	scaleZ = std::stof(str); entityProperty = END;  break;

		}

	}
	CreateEntityModel(fileName, textureName, x, y, z, Vector3(scaleX, scaleY, scaleZ));

}

/// <summary>
/// Get terrain from a line from the levelfile
/// </summary>
/// <param name="line"></param>
void Scene::GetTerrainFromFile(std::string line)
{
	std::istringstream ss(line);
	std::string str;
	EntityModel* entityModel = NULL;
	enum EntityProperty {
		BEGIN, MESHNAME, TEXTURENAME, POSITIONX, POSITIONY, POSITIONZ, SCALEX, SCALEY, SCALEZ, END
	};
	float x = 0;
	float y = 0;
	float z = 0;
	float scaleX = 0;
	float scaleY = 0;
	float scaleZ = 0;
	std::string fileName;
	std::string textureName;
	EntityProperty entityProperty = EntityProperty::BEGIN;

	while (getline(ss, str, ','))
	{
		switch (entityProperty) {
		case BEGIN:  entityProperty = MESHNAME; break;
		case MESHNAME: fileName = str; entityProperty = TEXTURENAME; break;
		case TEXTURENAME: textureName = str; entityProperty = END; break;
		}

	}

	_terrain = new Terrain(fileName, textureName);

}
/// <summary>
/// Get skybox from a line from the levelfile
/// </summary>
/// <param name="line"></param>
void Scene::GetSkyBoxFromFile(std::string line)
{
	std::istringstream ss(line);
	std::string str;
	EntityModel* entityModel = NULL;
	enum EntityProperty {
		BEGIN, MESHNAME, LEFT, TOP, RIGHT, BOTTOM, BACK, FRONT, END
	};
	float x = 0;
	float y = 0;
	float z = 0;
	float scaleX = 0;
	float scaleY = 0;
	float scaleZ = 0;
	std::string fileName;
	std::string textureName;
	EntityProperty entityProperty = EntityProperty::BEGIN;
	Skybox_Cube cube;
	std::string left;
	std::string right;
	//while (getline(ss, str, ','))
	//{
	//	if (str.find("left") != std::string::npos) {
	//		left = str.substr(str.find("=") + 1);
	//	}
	//	else if (str.find("right") != std::string::npos) {
	//		right = str.substr(str.find("=") + 1);
	//	}
	//}

	//_skybox = new Skybox(cube);

}

/// <summary>
/// Get the Skybox belonging to this scene
/// </summary>
/// <returns></returns>
Skybox* Scene::GetSkyBox()
{
	return _skybox;
}

/// <summary>
/// Gets the terrain belonging to this scene
/// </summary>
/// <returns></returns>
Terrain* Scene::GetTerrain()
{
	return _terrain;
}