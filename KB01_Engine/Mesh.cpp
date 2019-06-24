#include "Mesh.h"

Mesh::Mesh(std::string _fileName)
{
	_fileName = _fileName;
}

/// <summary>
/// Destructor
/// </summary>
Mesh::~Mesh()
{

}

void Mesh::SetNumberOfMaterials(unsigned int _numberOfMaterials)
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

unsigned int Mesh::GetNumberOfMaterials()
{
	return numberOfMaterials;
}



void Mesh::SetMesh(void* _mesh)
{
	mesh = _mesh;
}

void* Mesh::GetMesh()
{
	return mesh;
}
/// <summary>
/// Deletes all pointers and/or variables that may cause memory leaks
/// </summary>
void Mesh::CleanUp()
{
	delete meshMaterials;
	delete meshTextures;
	//delete numberOfMaterials;
}