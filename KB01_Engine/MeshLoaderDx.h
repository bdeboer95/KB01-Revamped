#ifndef __FILELOADERMESHDX_H__
#define __FILELOADERMESHDX_H__

#include "ResourceLoader.h"

#include "Mesh.h"

class MeshLoaderDx: public ResourceLoader
{
private:
	std::vector<Mesh>		meshes;
	LPD3DXBUFFER			materialBuffer; //Our material buffer
	
public:
	MeshLoaderDx(Renderer* _renderer);
	virtual	~MeshLoaderDx();

	virtual Mesh*			LoadResource(std::string _filePath, std::string _fileName);
	virtual void			Cleanup();
						
};
#endif
