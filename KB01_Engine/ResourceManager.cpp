#include "ResourceManager.h"

#include "Renderer.h"
#include "Log.h"

ResourceManager::ResourceManager()
{
	textures = std::vector<Texture*>();
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
	Mesh* mesh = meshLoader->LoadResource(_filePath, _fileName);
	meshes.push_back(mesh);
	Log::Instance()->LogMessage("ResourceManager - Resource '" + _fileName + "' loaded.", Log::MESSAGE_INFO);
	return mesh;

}

Texture* ResourceManager::LoadTexture(std::string _filePath, std::string _fileName)
{
	Texture* texture = textureLoader->LoadResource(_filePath, _fileName);
	textures.push_back(texture);
	//if texture contains something
	if (texture)
	{
		Log::Instance()->LogMessage("ResourceManager - Texture '" + _fileName + "' loaded.", Log::MESSAGE_INFO);
	}

	return texture;
}
/// <summary>
/// Deletes all resources.
/// </summary>
void ResourceManager::DeleteAllResources()
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

	Log::Instance()->LogMessage("ResourceManager - Deleted all resources", Log::MESSAGE_INFO);
}

void ResourceManager::Cleanup()
{
	DeleteAllResources();
	
	delete meshLoader;
	delete textureLoader;

	Log::Instance()->LogMessage("ResourceManager - ResourceManager cleaned up!", Log::MESSAGE_INFO);
}

