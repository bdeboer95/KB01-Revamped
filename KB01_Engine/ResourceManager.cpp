#include "ResourceManager.h"
#include "Renderer.h"
#include "Log.h"
#include <algorithm>


ResourceManager::ResourceManager()
{
	_textures = std::vector<TextureContainer*>();
	_meshes = std::vector<Mesh*>();

	Log::Instance()->LogMessage("ResourceManager - Created.", Log::MESSAGE_INFO);
}

ResourceManager::~ResourceManager()
{
	Cleanup();

	Log::Instance()->LogMessage("~ResourceManager - ResourceManager cleaned up!", Log::MESSAGE_INFO);
}

bool ResourceManager::InitResourceLoader(Renderer* renderer)
{
	if (renderer)
	{
		_meshLoader = new MeshLoaderDx(renderer);
		_textureLoader = new TextureLoaderDx(renderer);
	}
	return true;
}

//-----------------------------------------------------------------------------
// Name: LoadResource(std::string _fileName)
// Desc: Loads a resource using the filename provided in the parameters
//-----------------------------------------------------------------------------
Mesh* ResourceManager::LoadMesh(std::string filePath, std::string fileName)
{
	Mesh* mesh = NULL;

	std::vector<Mesh*>::iterator it = std::find_if(_meshes.begin(), _meshes.end(), [fileName](Mesh* temp) { return temp->GetFileName() == fileName; });

	// if mesh does exist, give it the existing pointer
	if (it != _meshes.end())
	{
		mesh = static_cast<Mesh*>(*it);

		Log::Instance()->LogMessage("ResourceManager - Mesh '" + fileName + "' already loaded.'", Log::MESSAGE_INFO);
	}
	// if mesh doesn't exist, load it
	else 
	{
		mesh = _meshLoader->LoadResource(filePath, fileName);
		_meshes.push_back(mesh);

		Log::Instance()->LogMessage("ResourceManager - Mesh '" + fileName + "' loaded.", Log::MESSAGE_INFO);
	}
	
	return mesh;
}

/// <summary>
/// Load the texture and store it in a texture container
/// </summary>
/// <param name="_filePath">the directory in which the file resides </param>
/// <param name="_fileName">the name of the file that contains the texture</param>
/// <returns></returns>
TextureContainer* ResourceManager::LoadTexture(std::string filePath, std::string fileName)
{
	TextureContainer* texture = NULL;
	
	std::vector<TextureContainer*>::iterator it = std::find_if(_textures.begin(), _textures.end(), [fileName](TextureContainer* temp) { return temp->GetFileName() == fileName; });

	// if texture does exist, give it the existing pointer
	if (it != _textures.end())
	{
		texture = static_cast<TextureContainer*>(*it);

		Log::Instance()->LogMessage("ResourceManager - Texture '" + fileName + "' already loaded'", Log::MESSAGE_INFO);
	}
	// if texture doesn't exist, load it
	else
	{
		texture = _textureLoader->LoadResource(filePath, fileName);
		_textures.push_back(texture);

		Log::Instance()->LogMessage("ResourceManager - Texture '" +fileName + "' loaded.", Log::MESSAGE_INFO);
	}

	return texture;
}

/// <summary>
/// Delete all pointers and/or variables that can cause memory leaks
/// </summary>
void ResourceManager::Cleanup()
{

	while (!_textures.empty())
	{
		delete _textures.back();
		_textures.pop_back();
	}

	while (!_meshes.empty())
	{
		delete _meshes.back();
		_meshes.pop_back();
	}
	
	delete _meshLoader;
	delete _textureLoader;

	Log::Instance()->LogMessage("ResourceManager - ResourceManager cleaned up!", Log::MESSAGE_INFO);
}



