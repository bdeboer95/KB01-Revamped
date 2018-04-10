#include "Scene.h"
#include "EntityModel.h"
#include "Camera.h"
#include <iostream>
#include <sstream>

/// <summary>
/// Initializes a new instance of the <see cref="Scene"/> class.
/// </summary>
/// <param name="_levelIndex">Index of the _level.</param>
Scene::Scene(int _levelIndex, HWND _hWnd, std::string _level)
{
	levelIndex = _levelIndex;
	hWnd = _hWnd;
	Camera* cam = new Camera();
	entityModels.push_back(cam);
	SceneLoader(_level);
	//CreateEntityModel("Tiger.x", "luipard.jpg",0, 0, 5);
	CreateEntityModel("Tiger.x", "zebra.jpg", 1, 0, 5);
	CreateEntityModel("Tiger.x", "zebra3.bmp", 2, 0, 5);
	CreateEntityModel("Tiger.x", "zebra3.bmp", 3, 0, 5);
	terrain = new Terrain();
	Log::Instance()->LogMessage("Scene - Scene created.", Log::MESSAGE_INFO);
}

/// <summary>
/// Finalizes an instance of the <see cref="Scene"/> class.
/// </summary>
Scene::~Scene()
{
	Log::Instance()->LogMessage("~Scene - Scene cleaned up!", Log::MESSAGE_INFO);
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
	Skybox_Cube sky;
	sky.back = "skybox3_back.tga";
	sky.top = "skybox3_top.tga";
	sky.left = "skybox3_left.tga";
	sky.front = "skybox3_front.tga";
	sky.bottom = "skybox3_bottom.tga";
	sky.right = "skybox3_right.tga";
	skybox = new Skybox(sky);
	skybox->InitGeometry(_renderer, _resourceManager);
	terrain->Initialize(_renderer, _resourceManager->LoadTexture("..\\Assets\\Textures\\Terrain\\", "terrainbrown.jpg"));
	ShowWindow(hWnd, SW_MAXIMIZE);
	UpdateWindow(hWnd);
	return S_OK;
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

	skybox->Render(_renderer);
	//terrain->Render(_renderer);
	for each(Entity* entity in entityModels)
	{
		if (dynamic_cast<EntityModel*>(entity))
		{
			EntityModel* e = dynamic_cast<EntityModel*>(entity);
			e->SetupMatrices(_renderer);
			e->Render(_renderer);

		}
		if (dynamic_cast<Camera*>(entity))
		{
			Camera* camera = dynamic_cast<Camera*>(entity);

			camera->SetCamera(_renderer);
		}

	}



	// End drawing the scene
	pd3dDevice->EndScene();

	// Present the backbuffer contents to the display
	_renderer->Present(hWnd);
}

std::vector<Entity*> Scene::GetEntityModels()
{
	return entityModels;
}

void Scene::SceneLoader(std::string _level)
{
	std::ifstream file(_level);
	bool successful = file.is_open();

	if (!successful)
	{
		Log::Instance()->LogMessage("Scene - Unable to read level file. (" + _level + ")", Log::MESSAGE_WARNING);
	}
	else
	{
		std::string line;
		if (file.good())
		{
			bool emFound = false, posFound = false, mnFound = false, tnFound = false;
			for (std::string line; std::getline(file, line);)
			{
				if (line.substr(0, 11) == "EntityModel" && !emFound)
				{
					emFound = true;
					GetEntityModelFromFile(line);
				}
				else if (!emFound)
				{
					Log::Instance()->LogMessage("Scene - EntityModel was not found in level file.", Log::MESSAGE_WARNING);
				}

				if (line.substr(0, 8) == "Position" && !posFound)
				{
					posFound = true;
					GetPositionFromFile(line);
				}
				else if (!posFound)
				{
					Log::Instance()->LogMessage("Scene - Position was not found in level file.", Log::MESSAGE_WARNING);
				}

				if (line.substr(0, 8) == "MeshName" && !mnFound)
				{
					mnFound = true;
					GetMeshNameFromFile(line);
				}
				else if (!mnFound)
				{
					Log::Instance()->LogMessage("Scene - MeshName was not found in level file.", Log::MESSAGE_WARNING);
				}

				if (line.substr(0, 11) == "TextureName" && !tnFound)
				{
					tnFound = true;
					GetTextureNameFromFile(line);
				}
				else if (!tnFound)
				{
					Log::Instance()->LogMessage("Scene - TextureName was not found in level file.", Log::MESSAGE_WARNING);
				}

			}
		}
	}

	file.close();
}

void Scene::GetEntityModelFromFile(std::string line)
{
	std::istringstream ss(line.substr(12));
	std::string str;

	while (getline(ss, str, ','))
	{
		if (str == "E1")
		{
			terrain = new Terrain();
		}

		if (str == "E2")
		{
			//skybox = new Skybox();
		}

		if (str == "E3")
		{
			CreateEntityModel(meshNames[2] + ".x", textureNames[2] + ".jpg", positioning[6], positioning[7], positioning[8]);
		}
	}
}

void Scene::GetPositionFromFile(std::string line)
{
	std::istringstream ss(line.substr(9));
	std::string str;
	std::string::size_type sz;

	while (getline(ss, str, ','))
	{
		std::string temp = str.substr(3);
		std::istringstream subss(temp);
		if (str.substr(0, 2) == "P1")
		{
			while (getline(subss, temp, '-'))
			{
				positioning.push_back(std::stof(temp));
			}
		}

		if (str.substr(0, 2) == "P2")
		{
			while (getline(subss, temp, '-'))
			{
				positioning.push_back(std::stof(temp));
			}
		}

		if (str.substr(0, 2) == "P3")
		{
			while (getline(subss, temp, '-'))
			{
				positioning.push_back(std::stof(temp));
			}
		}
	}

}

void Scene::GetMeshNameFromFile(std::string line)
{
	std::istringstream ss(line.substr(9));
	std::string str;

	while (getline(ss, str, ','))
	{
		if (str.substr(0, 2) == "M1")
		{
			meshNames.push_back(str.substr(3));
		}

		if (str.substr(0, 2) == "M2")
		{
			meshNames.push_back(str.substr(3));
		}

		if (str.substr(0, 2) == "M3")
		{
			meshNames.push_back(str.substr(3));
		}
	}

}

void Scene::GetTextureNameFromFile(std::string line)
{
	std::istringstream ss(line.substr(12));
	std::string str;

	while (getline(ss, str, ','))
	{
		if (str.substr(0, 2) == "T1")
		{
			textureNames.push_back(str.substr(3));
		}

		if (str.substr(0, 2) == "T2")
		{
			textureNames.push_back(str.substr(3));
		}

		if (str.substr(0, 2) == "T3")
		{
			textureNames.push_back(str.substr(3));
		}
	}
	
}
Skybox* Scene::GetSkyBox()
{
	return skybox;
}