#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include "MeshLoaderDx.h"
#include "TextureLoaderDx.h"

class ResourceManager 
{
private:
	MeshLoaderDx* meshLoader;
	std::vector<Mesh*> meshes;

	TextureLoaderDx* textureLoader;
	std::vector<Texture*> textures;

	Renderer renderer;

	void DeleteAllResources();
	void Cleanup();

public:
	ResourceManager();
	~ResourceManager();

	bool InitResourceLoader(Renderer* _renderer);

	Mesh* LoadMesh(std::string _filePath, std::string _fileName);
	Texture* LoadTexture(std::string _filePath, std::string _fileName);
	
};

#endif