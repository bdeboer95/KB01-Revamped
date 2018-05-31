#ifndef __FILELOADERMESHDX_H__
#define __FILELOADERMESHDX_H__

#include "ResourceLoader.h"

#include "MeshDx.h"

class MeshLoaderDx: public ResourceLoader
{
private:
	std::vector<MeshDx>		meshes;
	LPD3DXBUFFER			materialBuffer; //Our material buffer
	
public:
	MeshLoaderDx(Renderer* _renderer);
	virtual	~MeshLoaderDx();

	virtual MeshDx*			LoadResource(std::string _filePath, std::string _fileName);
	virtual void			Cleanup();
						
};
#endif
