#ifndef __FILELOADERMESHDX_H__
#define __FILELOADERMESHDX_H__

#include "ResourceLoader.h"
#include "Mesh.h"

class FileLoaderMeshDx: public ResourceLoader
{
	LPD3DXBUFFER			materialBuffer; //Our material buffer
	
public:
							FileLoaderMeshDx();
	virtual					~FileLoaderMeshDx();
	Mesh*					LoadMeshFromFile(std::string _fileName);
						
};
#endif
