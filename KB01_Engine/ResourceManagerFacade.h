#ifndef __RESOURCEMANAGERFACADE_H__
#define __RESOURCEMANAGERFACADE_H__

#include "ResourceManager.h"

class ResourceManagerFacade
{
private:
	ResourceManager* resourceManager;
//	Renderer* renderer;

	void InitResourceLoaders(Renderer* _renderer);
public:
	ResourceManagerFacade();
	~ResourceManagerFacade();
	void LoadNewMesh(std::string _fileName);
	void Cleanup();

};

#endif