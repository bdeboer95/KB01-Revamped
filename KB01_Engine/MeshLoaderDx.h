#ifndef __FILELOADERMESHDX_H__
#define __FILELOADERMESHDX_H__

#include "ResourceLoader.h"
#include "Mesh.h"
#include <d3dx9.h>

/// <summary>
/// Loads resources through the directX library
/// </summary>
class MeshLoaderDx: public ResourceLoader
{
private:
	std::vector<Mesh>		_meshes;													//The meshes used 
	LPD3DXBUFFER			_materialBuffer;											//Our material buffer
	
public:
							MeshLoaderDx(Renderer* _renderer);							//Constructor
	virtual					~MeshLoaderDx();											//Destructor
	virtual Mesh*			LoadResource(std::string _filePath, std::string _fileName); //Load a resource that will be used for the entities from a file name and a file path
	virtual void			CleanUp();													//Deletes all pointers and variables that can cause memory leaks					
};
#endif
