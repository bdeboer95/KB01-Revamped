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

void ResourceManagerFacade::InitResourceLoaders(void* _device)
{
	resourceManager->InitResourceLoader(_device);
}

void ResourceManagerFacade::LoadNewMesh(std::string _fileName)
{
	resourceManager->LoadMesh(_fileName);
}

void ResourceManagerFacade::Cleanup()
{
	delete resourceManager;
}