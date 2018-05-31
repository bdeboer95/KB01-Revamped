#include "Scene.h"
#include "EntityModel.h"
#include "Camera.h"
#include <vector>

/// <summary>
/// Initializes a new instance of the <see cref="Scene"/> class.
/// </summary>
/// <param name="_levelIndex">Index of the _level.</param>
Scene::Scene(int levelIndex, HWND hWnd, std::string level)
{
	_levelIndex = levelIndex;
	_hWnd = hWnd;

	_camera = new Camera();
	_terrain = new Terrain();

	ReadLevelFile("../Assets/Levels/Level2.xml");

	Log::Instance()->LogMessage("Scene - Scene Instantiated.", Log::MESSAGE_INFO);
}

/// <summary>
/// Finalizes an instance of the <see cref="Scene"/> class.
/// </summary>
Scene::~Scene()
{
	Log::Instance()->LogMessage("~Scene - Scene cleaned up!", Log::MESSAGE_INFO);
}

void Scene::ReadLevelFile(std::string fileName)
{
	XmlReader* reader = new XmlReader(fileName);

	std::vector<std::string> attributes = reader->LoadContents();

	for each (std::string setting in attributes)
	{
		if (setting.find("Entity") != std::string::npos)
		{
			std::string mesh	= XmlReader::GetValue(setting, "mesh");
			std::string texture = XmlReader::GetValue(setting, "texture");
			float x				= std::stof(XmlReader::GetValue(setting, "px"));
			float y				= std::stof(XmlReader::GetValue(setting, "py"));
			float z				= std::stof(XmlReader::GetValue(setting, "pz"));

			CreateEntityModel(mesh, texture, x, y, z);

			Log::Instance()->LogMessage("~Scene - Created: " + XmlReader::GetValue(setting, "name"), Log::MESSAGE_INFO);
		}
		else if (setting.find("Skybox") != std::string::npos)
		{
			Skybox_Cube sky;

			sky.back	= XmlReader::GetValue(setting, "back");
			sky.top		= XmlReader::GetValue(setting, "top");
			sky.left	= XmlReader::GetValue(setting, "left");
			sky.front	= XmlReader::GetValue(setting, "front");
			sky.bottom	= XmlReader::GetValue(setting, "bottom");
			sky.right	= XmlReader::GetValue(setting, "right");

			_skybox = new Skybox(sky);

			Log::Instance()->LogMessage("~Scene - Created: " + XmlReader::GetValue(setting, "name"), Log::MESSAGE_INFO);
		}
		else if (setting.find("Terrain") != std::string::npos)
		{
			Log::Instance()->LogMessage("~Scene - TODO: implement loading: " + XmlReader::GetValue(setting, "name"), Log::MESSAGE_WARNING);
		}
	}
}

/// <summary>
/// Creates the view port based on the amount of scenes that will be splitted on the window.
/// </summary>
/// <param name="_rect">The _rect.</param>
void Scene::CreateViewPort(RECT rect)
{
	_viewPort.X = rect.left;
	_viewPort.Y = rect.top;
	_viewPort.Width = rect.right;
	_viewPort.Height = rect.bottom;
	_splitted = true;
}

/// <summary>
/// Deletes the view port.
/// </summary>
void Scene::DeleteViewPort()
{
	_splitted = false;
}

/// <summary>
/// Gets the index of the level.
/// </summary>
/// <returns></returns>
int Scene::GetLevelIndex()
{
	return _levelIndex;
}

/// <summary>
/// Creates the entity model.
/// </summary>
Entity* Scene::CreateEntityModel(std::string meshName, std::string textureName, float positionX, float positionY, float positionZ)
{
	EntityModel* entityModel = new EntityModel(meshName, textureName, positionX, positionY, positionZ);
	_entityModels.push_back(entityModel);
	Log::Instance()->LogMessage("Scene - EntityModel created", Log::MESSAGE_INFO);
	return entityModel;
}

/// <summary>
/// Setups the geometry.
/// </summary>
/// <param name="_renderer">The _renderer.</param>
/// <returns></returns>
HRESULT Scene::SetupGeometry(ResourceManager* resourceManager, Renderer* renderer)
{

	for each(Entity* entityModel in _entityModels)
	{
		if (static_cast<EntityModel*>(entityModel))
		{
			EntityModel* e = static_cast<EntityModel*>(entityModel);
			if (FAILED(e->InitGeometry(resourceManager)))
			{
				Log::Instance()->LogMessage("Scene - Geometry was failed to be set for all entitymodels.", Log::MESSAGE_ERROR);
				return E_FAIL;
			}
		}
	}

	_skybox->InitGeometry(renderer, resourceManager);
	_terrain->Initialize(renderer, "heightdata.raw", "terrainbrown.jpg");
	ShowWindow(_hWnd, SW_MAXIMIZE);
	UpdateWindow(_hWnd);
	return S_OK;
}

/// <summary>
/// Renders the specified _renderer.
/// </summary>
/// <param name="_renderer">The _renderer.</param>
void Scene::Render(Renderer* renderer)
{
	// Check if the scene will be splitscreen or not
	if (_splitted)
	{
		renderer->SetViewPort(&_viewPort);
	}

	// Clear the backbuffer and the zbuffer
	renderer->ClearBuffer(200, 200, 200);

	// Begin drawing the scene
	if (FAILED(renderer->BeginScene()))
	{
		Log::Instance()->LogMessage("Scene - BeginScene failed", Log::MESSAGE_ERROR);
	}

	_skybox->Render(renderer);
	//_terrain->Render(renderer);
	_camera->SetCamera(renderer);

	for each(Entity* entity in _entityModels)
	{
		if (static_cast<EntityModel*>(entity))
		{
			EntityModel* e = static_cast<EntityModel*>(entity);
			e->Render(renderer);
		}
	}

	// End drawing the scene
	renderer->EndScene();

	// Present the backbuffer contents to the display
	renderer->Present(_hWnd);
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
/// Gets a vector pointer to entity models.
/// </summary>
/// <returns></returns>
std::vector<Entity*> Scene::GetEntityModels()
{
	return _entityModels;
}

/// <summary>
/// Gets a pointer to a skybox.
/// </summary>
/// <returns></returns>
Skybox* Scene::GetSkyBox()
{
	return _skybox;
}

Terrain* Scene::GetTerrain()
{
	return _terrain;
}