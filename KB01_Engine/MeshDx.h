#ifndef __MESHDX_H__
#define __MESHDX_H__

#include "Mesh.h"

#include "d3dx9.h"

class MeshDx : public Mesh
{
public:
	MeshDx(std::string _fileName);
	~MeshDx();

	virtual void				SetMeshMaterials(void* _meshMaterials);
	virtual void*				GetMeshMaterials();

	virtual void				SetMeshTextures(void*_meshTextures);
	virtual void*				GetMeshTextures();

	virtual void				SetNumberOfMaterials(unsigned int _numberOfMaterials);
	virtual unsigned int		GetNumberOfMaterials();

	virtual void				SetMesh(void* _mesh);
	virtual void*				GetMesh();
	virtual std::string			GetFileName();
	virtual void				Cleanup();

	virtual long				LockVertexBuffer(unsigned long flags, void** data);
	virtual long				UnlockVertexBuffer();
	virtual long				LockIndexBuffer(unsigned long flags, void** data);
	virtual long				UnlockIndexBuffer();
	virtual long				LockAttributeBuffer(unsigned long flags, unsigned long** data);
	virtual long				UnlockAttributeBuffer();

};

#endif