#include "MeshDx.h"

MeshDx::MeshDx(std::string fileName)
{
	_fileName = fileName;
}

MeshDx::~MeshDx()
{

}

void MeshDx::SetNumberOfMaterials(unsigned int numberOfMaterials)
{
	_numberOfMaterials = numberOfMaterials;
}

void* MeshDx::GetMeshMaterials()
{
	return _meshMaterials;
}

void MeshDx::SetMeshMaterials(void* meshMaterials)
{
	_meshMaterials = meshMaterials;
}

void MeshDx::SetMeshTextures(void* meshTextures)
{
	_meshTextures = meshTextures;
}

void* MeshDx::GetMeshTextures()
{
	return _meshTextures;
}

unsigned int MeshDx::GetNumberOfMaterials()
{
	return _numberOfMaterials;
}

void MeshDx::Cleanup()
{
	delete _mesh;
	delete _texture;
	delete _meshMaterials;
	delete _meshTextures;
}

void MeshDx::SetMesh(void* mesh)
{
	_mesh = mesh;
}

void* MeshDx::GetMesh()
{
	return _mesh;
}

std::string MeshDx::GetFileName()
{
	return _fileName;
}

long MeshDx::LockVertexBuffer(unsigned long flags, void** data)
{
	return static_cast<LPD3DXMESH>(_mesh)->LockVertexBuffer(flags, data);
}

long MeshDx::UnlockVertexBuffer()
{
	return static_cast<LPD3DXMESH>(_mesh)->UnlockVertexBuffer();
}

long MeshDx::LockIndexBuffer(unsigned long flags, void** data)
{
	return static_cast<LPD3DXMESH>(_mesh)->LockIndexBuffer(flags, data);
}

long MeshDx::UnlockIndexBuffer()
{
	return static_cast<LPD3DXMESH>(_mesh)->UnlockIndexBuffer();
}

long MeshDx::LockAttributeBuffer(unsigned long flags, unsigned long** data)
{
	return static_cast<LPD3DXMESH>(_mesh)->LockAttributeBuffer(flags, data);
}

long MeshDx::UnlockAttributeBuffer()
{
	return static_cast<LPD3DXMESH>(_mesh)->UnlockAttributeBuffer();
}
