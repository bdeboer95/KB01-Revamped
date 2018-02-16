//-----------------------------------------------------------------------------
// File: ResourceManager.cpp
//
// Desc: 
//-----------------------------------------------------------------------------
#include "ResourceManager.h"
#include "FileLoaderMeshDx.h"
#include "TextureLoaderDx.h"
#include <iostream>

/// <summary>
/// Initializes a new instance of the <see cref="ResourceManager"/> class.
/// </summary>
ResourceManager::ResourceManager()
{
	resources = std::vector<Resource*>();
	Log::Instance()->LogMessage("ResourceManager - Created.", Log::MESSAGE_INFO);
}

/// <summary>
/// Finalizes an instance of the <see cref="ResourceManager"/> class.
/// </summary>
ResourceManager::~ResourceManager()
{
	Cleanup();
	Log::Instance()->LogMessage("~ResourceManager - ResourceManager cleaned up!", Log::MESSAGE_INFO);
}

bool ResourceManager::InitResourceLoader(void* _device)
{
	if (_device)
	{
		meshLoader = new FileLoaderMeshDx();
		textureLoader = new TextureLoaderDx();
		meshLoader->SetDevice(_device);
		textureLoader->SetDevice(_device);
	}
	return true;
}
//-----------------------------------------------------------------------------
// Name: LoadResource(std::string _fileName)
// Desc: Loads a resource using the filename provided in the parameters
//-----------------------------------------------------------------------------
Mesh* ResourceManager::LoadMesh(std::string _fileName)
{
	Mesh* mesh = meshLoader->LoadMeshFromFile(_fileName);
	resources.push_back(mesh);
	Log::Instance()->LogMessage("ResourceManager - Resource '" + _fileName + "' loaded.", Log::MESSAGE_INFO);
	return mesh;

}

Texture* ResourceManager::LoadTexture(std::string _filePath,std::string _fileName)
{
	Texture* texture = textureLoader->LoadTexture(_filePath,_fileName);
	resources.push_back(texture);
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
	while (!resources.empty())
	{
		delete resources.back();
		resources.pop_back();
	}
	Log::Instance()->LogMessage("ResourceManager - Deleted all resources", Log::MESSAGE_INFO);
}

void ResourceManager::Cleanup()
{
	DeleteAllResources();
	//TODO : DELETE resourceLoaders
	Log::Instance()->LogMessage("ResourceManager - ResourceManager cleaned up!", Log::MESSAGE_INFO);
}

