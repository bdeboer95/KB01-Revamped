#ifndef __MESH_H__
#define __MESH_H__

#include "Texture.h"
#include "Resource.h"

class Mesh : public Resource
{
private:
	Texture*					texture;
public:
								Mesh(std::string _fileName) :Resource(_fileName){};
								~Mesh();

	void*						meshTextures; // Textures for our mesh
	void*						meshMaterials = NULL; // Materials for our mesh
	UINT						numberOfMaterials;   // Number of mesh materials	
	void*						mesh = NULL; // Our mesh object in sysmem	

	void						SetMeshMaterials(void* _meshMaterials);
	void*						GetMeshMaterials();
	void						SetMeshTextures(void*_meshTextures);
	void*						GetMeshTextures();
	void						SetNumberOfMaterials(UINT _numberOfMaterials);
	UINT						GetNumberOfMaterials();
	void						SetMesh(void* _mesh);
	void*						GetMesh();
	virtual void				Cleanup();
};

#endif