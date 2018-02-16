#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__


#include "FileLoaderMeshDx.h"
#include "TextureLoaderDx.h"
#include <vector>
#include "Mesh.h"
#include "Log.h"


class ResourceManager
{

private:
	FileLoaderMeshDx* meshLoader;
	TextureLoaderDx* textureLoader;
	void DeleteAllResources();

	std::vector<Resource*> resources;
	void Cleanup();

public:
	ResourceManager();
	~ResourceManager();

	bool InitResourceLoader(void* _device);
	Mesh* LoadMesh(std::string _fileName); //ResourceManager loads all the meshes and textures
	Texture* LoadTexture(std::string _filePath, std::string _fileName);
	
};

#endif