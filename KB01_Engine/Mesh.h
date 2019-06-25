#ifndef __MESH_H__
#define __MESH_H__

#include "Resource.h"
#include "TextureContainer.h"

class Mesh : public Resource
{
private:
	TextureContainer*			_textureContainer;										// The container holding the texture for the mesh
	void*						_meshTextures;											// Textures for our mesh
	void*						_meshMaterials;											// Materials for our mesh
	unsigned int				_numberOfMaterials;										// Number of mesh materials	
	void*						_mesh;													// Our mesh object in sysmem

public:
								Mesh(std::string fileName);							// Constructor
								~Mesh();												// Deconstructor
	void						SetMeshMaterials(void* meshMaterials);
	void*						GetMeshMaterials();
	void						SetMeshTextures(void*meshTextures);
	void*						GetMeshTextures();
	void						SetNumberOfMaterials(unsigned int numberOfMaterials);
	unsigned int				GetNumberOfMaterials();
	void						SetMesh(void* mesh);
	void*						GetMesh();
	virtual void				CleanUp();												//Delete all pointers and variables that can cause memory leaks
};

#endif