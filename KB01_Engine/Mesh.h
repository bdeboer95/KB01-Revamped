#ifndef __MESH_H__
#define __MESH_H__

#include "Resource.h"
#include "TextureContainer.h"

class Mesh : public Resource
{
private:
	TextureContainer*			_textureContainer;										// The container holding the texture for the mesh
	void*						meshTextures;											// Textures for our mesh
	void*						meshMaterials = NULL;									// Materials for our mesh
	unsigned int				numberOfMaterials;										// Number of mesh materials	
	void*						mesh = NULL;											// Our mesh object in sysmem

public:
								Mesh(std::string _fileName);							// Constructor
								~Mesh();												// Deconstructor
	void						SetMeshMaterials(void* _meshMaterials);
	void*						GetMeshMaterials();
	void						SetMeshTextures(void*_meshTextures);
	void*						GetMeshTextures();
	void						SetNumberOfMaterials(unsigned int _numberOfMaterials);
	unsigned int				GetNumberOfMaterials();
	void						SetMesh(void* _mesh);
	void*						GetMesh();
	virtual void				CleanUp();												//Delete all pointers and variables that can cause memory leaks
};

#endif