#include "MeshLoaderDx.h"
#include "Mesh.h"
#include <iostream>
#include <Windows.h>
#include "StringToWStringConverter.h"

MeshLoaderDx::MeshLoaderDx(Renderer* _renderer)
{
	renderer = _renderer;
	materialBuffer = NULL;

	Log::Instance()->LogMessage("MeshLoaderDx - MeshLoaderDx created.", Log::MESSAGE_INFO);
}


MeshLoaderDx::~MeshLoaderDx()
{
	Log::Instance()->LogMessage("~MeshLoaderDx - MeshLoaderDx cleaned up!", Log::MESSAGE_INFO);
}

//-----------------------------------------------------------------------------
// Name: LoadMeshFromFile(LPCTSTR _fileName)
// Desc:  Load the mesh from the specified file using dirextX9
//-----------------------------------------------------------------------------
Mesh* MeshLoaderDx::LoadResource(std::string _filePath, std::string _fileName)
{
	Mesh* mesh = new Mesh(_fileName);

	LPD3DXMESH direct3Dmesh;
	DWORD numberOfMaterials = 0L;

	StringToWStringConverter converter;
	std::wstring path = converter.Convert(_filePath);
	std::wstring name = converter.Convert(_fileName);
	std::wstring temp = path + name;
	LPCWSTR directory = temp.c_str();

	// Fill LPD3DXMESH
	if (FAILED(D3DXLoadMeshFromX(directory, D3DXMESH_SYSTEMMEM,
		static_cast<LPDIRECT3DDEVICE9>(renderer->GetDevice()), 
		NULL,
		&materialBuffer, 
		NULL, 
		&numberOfMaterials,
		&direct3Dmesh)))
	{
		Log::Instance()->LogMessage("MeshLoaderDx - Failed to load Mesh using the direct3Ddevice.Could not find the file." + _fileName, Log::MESSAGE_WARNING);
		return NULL;
	}


	// We need to extract the material properties and texture names from the 
	// pD3DXMtrlBuffer
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();
	LPDIRECT3DTEXTURE9*	meshTextures = new LPDIRECT3DTEXTURE9[numberOfMaterials];
	D3DMATERIAL9* meshMaterials = new D3DMATERIAL9[numberOfMaterials];

	for (UINT i = 0; i < numberOfMaterials; i++)
	{
		// Copy the material
		meshMaterials[i] = d3dxMaterials[i].MatD3D;

		// Set the ambient color for the material (D3DX does not do this)
		meshMaterials[i].Ambient = meshMaterials[i].Diffuse;
		meshTextures[i] = NULL;

		mesh->SetMeshTextures(meshTextures);
		mesh->SetMeshMaterials(meshMaterials);
		mesh->SetNumberOfMaterials(numberOfMaterials);
		mesh->SetMesh(direct3Dmesh);
		//Done with the Materialbuffer
		materialBuffer->Release();
		return mesh;
	}
}

void MeshLoaderDx::Cleanup()
{

}

