#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include "MeshLoaderDx.h"
#include "TextureLoaderDx.h"


class ResourceManager
{
private:
	MeshLoaderDx*					_meshLoader;
	std::vector<Mesh*>				_meshes;
	TextureLoaderDx*				_textureLoader;												//
	std::vector<TextureContainer*>	_textures;													//A list that contains all the textures that have been loaded during the lifetime of the application

	void							Cleanup();													//Delete all pointers and/or variables that can cause memory leaks

public:
									ResourceManager();											//Constructor
									~ResourceManager();											//Destructor
	bool							InitResourceLoader(Renderer* renderer);					//Create and initialize the loaders for respectively meshes and textures
	Mesh*							LoadMesh(std::string filePath, std::string fileName);		//Load a mesh from a filename
	TextureContainer*				LoadTexture(std::string filePath, std::string fileName);	//Load a texture from a texturename
};

#endif