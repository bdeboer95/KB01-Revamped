#ifndef __MESH_H__
#define __MESH_H__

#include "Resource.h"

class Mesh : public Resource
{
public:
	virtual	~Mesh() = 0;

	virtual void				SetMeshMaterials(void* _meshMaterials) = 0;
	virtual void*				GetMeshMaterials() = 0;

	virtual void				SetMeshTextures(void*_meshTextures) = 0;
	virtual void*				GetMeshTextures() = 0;

	virtual void				SetNumberOfMaterials(unsigned int _numberOfMaterials) = 0;
	virtual unsigned int		GetNumberOfMaterials() = 0;

	virtual void				SetMesh(void* _mesh) = 0;
	virtual void*				GetMesh() = 0;
	virtual std::string			GetFileName() = 0;
	virtual void				Cleanup() = 0;

	virtual long				LockVertexBuffer(unsigned long flags, void** data) = 0;
	virtual long				UnlockVertexBuffer() = 0;
	virtual long				LockIndexBuffer(unsigned long flags, void** data) = 0;
	virtual long				UnlockIndexBuffer() = 0;
	virtual long				LockAttributeBuffer(unsigned long flags, unsigned long** data) = 0;
	virtual long				UnlockAttributeBuffer() = 0;

protected:
	void*						_texture;
	void*						_mesh;

	void*						_meshTextures;			// Textures for our mesh
	void*						_meshMaterials;			// Materials for our mesh
	unsigned int				_numberOfMaterials;		// Number of mesh materials	

	unsigned long				_attributeBuffer;
	long						_attributeBufferLockCount;
};

#endif