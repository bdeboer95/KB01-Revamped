#include "Mesh.h"

Mesh::Mesh(std::string _fileName)
{
	fileName = _fileName;
}

Mesh::~Mesh()
{

}

void Mesh::SetNumberOfMaterials(UINT _numberOfMaterials)
{
	numberOfMaterials = _numberOfMaterials;
}

void* Mesh::GetMeshMaterials()
{
	return meshMaterials;
}

void Mesh::SetMeshMaterials(void* _meshMaterials)
{
	meshMaterials = _meshMaterials;
}

void Mesh::SetMeshTextures(void* _meshTextures)
{
	meshTextures = _meshTextures;
}

void* Mesh::GetMeshTextures()
{
	return meshTextures;
}

UINT Mesh::GetNumberOfMaterials()
{
	return numberOfMaterials;
}

void Mesh::Cleanup()
{
	delete meshMaterials;
	delete meshTextures;
	//delete numberOfMaterials;
}

void Mesh::SetMesh(void* _mesh)
{
	mesh = _mesh;
}

void* Mesh::GetMesh()
{
	return mesh;
}