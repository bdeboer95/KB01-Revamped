#include "ResourceManagerFacade.h"
#include "Renderer.h"


/// <summary>
/// Initializes a new instance of the <see cref="ResourceManagerFacade"/> class.
/// </summary>
ResourceManagerFacade::ResourceManagerFacade()
{
	resourceManager = new ResourceManager();
//	InitResourceLoaders(renderer);
}


/// <summary>
/// Finalizes an instance of the <see cref="ResourceManagerFacade"/> class.
/// </summary>
ResourceManagerFacade::~ResourceManagerFacade()
{
	Cleanup();
}

void ResourceManagerFacade::InitResourceLoaders(Renderer* _renderer)
{
	resourceManager->InitResourceLoader(_renderer);
}

void ResourceManagerFacade::LoadNewMesh(std::string _fileName)
{
	resourceManager->LoadMesh("..\\Meshes\\", _fileName);
}

void ResourceManagerFacade::Cleanup()
{
	delete resourceManager;
}