#include "FileLoaderMeshDx.h"
#include "Mesh.h"
#include <iostream>
#include "StringToWStringConverter.h"

FileLoaderMeshDx::FileLoaderMeshDx()
{
	direct3D = NULL; // Used to create the D3DDevice
	direct3DDevice = NULL; // Our rendering device
	materialBuffer = NULL;

	Log::Instance()->LogMessage("FileLoaderMeshDx - FileLoaderMeshDx created.", Log::MESSAGE_INFO);
}


FileLoaderMeshDx::~FileLoaderMeshDx()
{
	Log::Instance()->LogMessage("~FileLoaderMeshDx - FileLoaderMeshDx cleaned up!", Log::MESSAGE_INFO);
}

//-----------------------------------------------------------------------------
// Name: LoadMeshFromFile(LPCTSTR _fileName)
// Desc:  Load the mesh from the specified file using dirextX9
//-----------------------------------------------------------------------------
Mesh* FileLoaderMeshDx::LoadMeshFromFile(std::string _fileName)
{
	Mesh* mesh = new Mesh(_fileName);
	StringToWStringConverter converter;
	//number of materials is the amount of materials that is needed for the meshtextures
	DWORD numberOfMaterials = 0L;
	LPD3DXMESH direct3Dmesh;
	std::wstring temp = converter.Convert(_fileName);
	LPCWSTR d = L"..\\Assets\\Meshes\\";
	std::wstring df = std::wstring(d) + temp;
	LPCWSTR dfc = df.c_str();
	
		// If model is not in current folder, try parent folder
		if (FAILED(D3DXLoadMeshFromX(dfc, D3DXMESH_SYSTEMMEM,
			direct3DDevice, NULL,
			&materialBuffer, NULL, &numberOfMaterials,
			&direct3Dmesh)))
		{
			std::string message = "MeshLoaderDx - Failed to load Mesh using the direct3Ddevice.Could not find the file." + _fileName;
			Log::Instance()->LogMessage(message, Log::MESSAGE_WARNING);

			return 0;
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

