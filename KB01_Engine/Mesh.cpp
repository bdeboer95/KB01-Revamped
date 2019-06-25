#include "Mesh.h"

/// <summary>
/// Initializes a new instance of the <see cref="Mesh"/> class.
/// </summary>
/// <param name="fileName">Name of the file.</param>
Mesh::Mesh(std::string fileName)
{
	_fileName = fileName;
}


/// <summary>
/// Finalizes an instance of the <see cref="Mesh"/> class.
/// </summary>
Mesh::~Mesh()
{
	CleanUp();
}

void Mesh::SetNumberOfMaterials(unsigned int numberOfMaterials)
{
	_numberOfMaterials = numberOfMaterials;
}

void* Mesh::GetMeshMaterials()
{
	return _meshMaterials;
}

void Mesh::SetMeshMaterials(void* meshMaterials)
{
	_meshMaterials = meshMaterials;
}

void Mesh::SetMeshTextures(void* meshTextures)
{
	_meshTextures = meshTextures;
}

void* Mesh::GetMeshTextures()
{
	return _meshTextures;
}

unsigned int Mesh::GetNumberOfMaterials()
{
	return _numberOfMaterials;
}



void Mesh::SetMesh(void* _mesh)
{
	_mesh = _mesh;
}

void* Mesh::GetMesh()
{
	return _mesh;
}
/// <summary>
/// Deletes all pointers and/or variables that may cause memory leaks
/// </summary>
void Mesh::CleanUp()
{
	delete _meshMaterials;
	delete _meshTextures;
	//delete numberOfMaterials;
}