#ifndef __MESH_H__
#define __MESH_H__

#include "Resource.h"

#include "Texture.h"
#include "d3dx9.h"

class Mesh : public Resource
{
private:
	Texture*					texture;

public:
	Mesh(std::string _fileName);
	~Mesh();

	virtual void				Cleanup();

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

};

#endif