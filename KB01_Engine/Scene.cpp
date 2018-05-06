#include "Scene.h"
#include "EntityModel.h"
#include "Camera.h"
#include <vector>

/// <summary>
/// Initializes a new instance of the <see cref="Scene"/> class.
/// </summary>
/// <param name="_levelIndex">Index of the _level.</param>
Scene::Scene(int _levelIndex, HWND _hWnd, std::string _level)
{
	levelIndex = _levelIndex;
	hWnd = _hWnd;
	Camera* cam = new Camera();
	_terrain = new CTerrain();

	ReadLevelFile("../Assets/Levels/levelFile.xml");

	Log::Instance()->LogMessage("Scene - Scene Instantiated.", Log::MESSAGE_INFO);
}

/// <summary>
/// Finalizes an instance of the <see cref="Scene"/> class.
/// </summary>
Scene::~Scene()
{
	Log::Instance()->LogMessage("~Scene - Scene cleaned up!", Log::MESSAGE_INFO);
}

void Scene::ReadLevelFile(const char* fileName)
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
			float y				= std::stof(XmlReader::GetValue(setting, "pz"));
			float z				= std::stof(XmlReader::GetValue(setting, "py"));

			CreateEntityModel(mesh, texture, x, y, z);
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
		}
		else if (setting.find("Terrain") != std::string::npos)
		{
			Log::Instance()->LogMessage("~Scene - TODO: implement loading: " + XmlReader::GetValue(setting, "name"), Log::MESSAGE_WARNING);
		}

		Log::Instance()->LogMessage("~Scene - Created: " + XmlReader::GetValue(setting, "name"), Log::MESSAGE_INFO);
	}
}

/// <summary>
/// Creates the view port based on the amount of scenes that will be splitted on the window.
/// </summary>
/// <param name="_rect">The _rect.</param>
void Scene::CreateViewPort(RECT _rect)
{
	viewPort.X = _rect.left;
	viewPort.Y = _rect.top;
	viewPort.Width = _rect.right;
	viewPort.Height = _rect.bottom;
	splitted = true;
}

/// <summary>
/// Deletes the view port.
/// </summary>
void Scene::DeleteViewPort()
{
	splitted = false;
}

/// <summary>
/// Gets the index of the level.
/// </summary>
/// <returns></returns>
int Scene::GetLevelIndex()
{
	return levelIndex;
}

/// <summary>
/// Creates the entity model.
/// </summary>
Entity* Scene::CreateEntityModel(std::string _meshName, std::string _textureName, float _positionX, float _positionY, float _positionZ)
{
	EntityModel* entityModel = new EntityModel(_meshName, _textureName, _positionX, _positionY, _positionZ);
	entityModels.push_back(entityModel);
	Log::Instance()->LogMessage("Scene - EntityModel created", Log::MESSAGE_INFO);
	return entityModel;
}

/// <summary>
/// Setups the geometry.
/// </summary>
/// <param name="_renderer">The _renderer.</param>
/// <returns></returns>
HRESULT Scene::SetupGeometry(ResourceManager* _resourceManager, Renderer* _renderer)
{

	for each(Entity* entityModel in entityModels)
	{
		if (dynamic_cast<EntityModel*>(entityModel))
		{
			EntityModel* e = dynamic_cast<EntityModel*>(entityModel);
			if (FAILED(e->InitGeometry(_resourceManager)))
			{
				Log::Instance()->LogMessage("Scene - Geometry was failed to be set for all entitymodels.", Log::MESSAGE_ERROR);
				return E_FAIL;
			}
		}
	}

	_skybox->InitGeometry(_renderer, _resourceManager);
	_terrain->Initialize(static_cast<LPDIRECT3DDEVICE9>(_renderer->GetDevice()), "heightdata.raw", "terrainbrown.jpg");
	ShowWindow(hWnd, SW_MAXIMIZE);
	UpdateWindow(hWnd);
	return S_OK;
}

/// <summary>
/// Renders the specified _renderer.
/// </summary>
/// <param name="_renderer">The _renderer.</param>
void Scene::Render(Renderer* _renderer)
{
	LPDIRECT3DDEVICE9 pd3dDevice = static_cast<LPDIRECT3DDEVICE9>(_renderer->GetDevice());

	// Check if the scene will be splitscreen or not
	if (splitted)
	{
		_renderer->SetViewPort(&viewPort);
	}

	// Clear the backbuffer and the zbuffer
	_renderer->ClearBuffer(200, 200, 200);

	// Begin drawing the scene
	if (FAILED(pd3dDevice->BeginScene()))
	{
		Log::Instance()->LogMessage("Scene - BeginScene failed", Log::MESSAGE_ERROR);
	}

	_skybox->Render(_renderer);
	_terrain->Render(_renderer);
	_camera->SetCamera(_renderer);

	for each(Entity* entity in entityModels)
	{
		if (dynamic_cast<EntityModel*>(entity))
		{
			EntityModel* e = dynamic_cast<EntityModel*>(entity);
			e->SetupMatrices(_renderer);
			e->Render(_renderer);

		}
	}

	// End drawing the scene
	pd3dDevice->EndScene();

	// Present the backbuffer contents to the display
	_renderer->Present(hWnd);
}

/// <summary>
/// Gets the handler.
/// </summary>
/// <returns></returns>
HWND Scene::GetHandler()
{
	return hWnd;
}

/// <summary>
/// Gets a vector pointer to entity models.
/// </summary>
/// <returns></returns>
std::vector<Entity*> Scene::GetEntityModels()
{
	return entityModels;
}

/// <summary>
/// Gets a pointer to a skybox.
/// </summary>
/// <returns></returns>
Skybox* Scene::GetSkyBox()
{
	return _skybox;
}

/// <summary>
/// Gets a pointer to a terrain.
/// </summary>
/// <returns></returns>
CTerrain* Scene::GetTerrain()
{
	return _terrain;
}