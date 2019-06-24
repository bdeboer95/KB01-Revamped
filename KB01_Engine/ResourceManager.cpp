#include "ResourceManager.h"
#include "Renderer.h"
#include "Log.h"
#include <algorithm>


ResourceManager::ResourceManager()
{
	textures = std::vector<TextureContainer*>();
	meshes = std::vector<Mesh*>();

	Log::Instance()->LogMessage("ResourceManager - Created.", Log::MESSAGE_INFO);
}

ResourceManager::~ResourceManager()
{
	Cleanup();

	Log::Instance()->LogMessage("~ResourceManager - ResourceManager cleaned up!", Log::MESSAGE_INFO);
}

bool ResourceManager::InitResourceLoader(Renderer* _renderer)
{
	if (_renderer)
	{
		meshLoader = new MeshLoaderDx(_renderer);
		textureLoader = new TextureLoaderDx(_renderer);
	}
	return true;
}

//-----------------------------------------------------------------------------
// Name: LoadResource(std::string _fileName)
// Desc: Loads a resource using the filename provided in the parameters
//-----------------------------------------------------------------------------
Mesh* ResourceManager::LoadMesh(std::string _filePath, std::string _fileName)
{
	Mesh* mesh = NULL;

	std::vector<Mesh*>::iterator it = std::find_if(meshes.begin(), meshes.end(), [_fileName](Mesh* temp) { return temp->GetFileName() == _fileName; });

	// if mesh does exist, give it the existing pointer
	if (it != meshes.end())
	{
		mesh = static_cast<Mesh*>(*it);

		Log::Instance()->LogMessage("ResourceManager - Mesh '" + _fileName + "' already loaded.'", Log::MESSAGE_INFO);
	}
	// if mesh doesn't exist, load it
	else 
	{
		mesh = meshLoader->LoadResource(_filePath, _fileName);
		meshes.push_back(mesh);

		Log::Instance()->LogMessage("ResourceManager - Mesh '" + _fileName + "' loaded.", Log::MESSAGE_INFO);
	}
	
	return mesh;
}

/// <summary>
/// Load the texture and store it in a texture container
/// </summary>
/// <param name="_filePath">the directory in which the file resides </param>
/// <param name="_fileName">the name of the file that contains the texture</param>
/// <returns></returns>
TextureContainer* ResourceManager::LoadTexture(std::string _filePath, std::string _fileName)
{
	TextureContainer* texture = NULL;
	
	std::vector<TextureContainer*>::iterator it = std::find_if(textures.begin(), textures.end(), [_fileName](TextureContainer* temp) { return temp->GetFileName() == _fileName; });

	// if texture does exist, give it the existing pointer
	if (it != textures.end())
	{
		texture = static_cast<TextureContainer*>(*it);

		Log::Instance()->LogMessage("ResourceManager - Texture '" + _fileName + "' already loaded'", Log::MESSAGE_INFO);
	}
	// if texture doesn't exist, load it
	else
	{
		texture = textureLoader->LoadResource(_filePath, _fileName);
		textures.push_back(texture);

		Log::Instance()->LogMessage("ResourceManager - Texture '" + _fileName + "' loaded.", Log::MESSAGE_INFO);
	}

	return texture;
}

/// <summary>
/// Delete all pointers and/or variables that can cause memory leaks
/// </summary>
void ResourceManager::Cleanup()
{

	while (!textures.empty())
	{
		delete textures.back();
		textures.pop_back();
	}

	while (!meshes.empty())
	{
		delete meshes.back();
		meshes.pop_back();
	}
	
	delete meshLoader;
	delete textureLoader;

	Log::Instance()->LogMessage("ResourceManager - ResourceManager cleaned up!", Log::MESSAGE_INFO);
}

