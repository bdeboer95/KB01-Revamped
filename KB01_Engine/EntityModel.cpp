#include "EntityModel.h"
#include <iostream>
#include <vector>
#include <dinput.h>

#define KEYDOWN(name, key) (name[key])
#define MSTATE(name, key) (name[key])

/// <summary>
/// Initializes a new instance of the <see cref="EntityModel"/> class.
/// </summary>
EntityModel::EntityModel(std::string _fileName, std::string _textureName,float _positionX, float _positionY, float _positionZ)
{
	fileName = _fileName;
	texture = new Texture(_textureName);
	Log::Instance()->LogMessage("EntityModel - Created.", Log::MESSAGE_INFO);
	positionX =_positionX;
	positionY =_positionY;
	positionZ = _positionZ;
}

/// <summary>
/// Finalizes an instance of the <see cref="EntityModel"/> class.
/// </summary>
EntityModel::~EntityModel()
{
	//TODO
	Log::Instance()->LogMessage("~EntityModel - EntityModel cleaned up!", Log::MESSAGE_INFO);
}

void EntityModel::Render(Renderer* _renderer)
{

	for (UINT i = 0; i < mesh->GetNumberOfMaterials(); i++)
	{
		_renderer->SetMaterial(mesh->GetMeshMaterials(), i);
		_renderer->SetTexture(texture->GetTextures(), i);
		_renderer->DrawSubset(mesh->GetMesh(), i);
	}

}


/// <summary>
/// Changes the rotation.
/// </summary>
/// <param name="_renderer">The _renderer.</param>
/// <param name="_rotation">The _rotation.</param>
void EntityModel::ChangeRotation(Renderer* _renderer)
{
	// Set up world matrix
	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matTranslate;
	D3DXMATRIX matRotateX;
	D3DXMATRIX matRotateY;
	D3DXMATRIX matRotateZ;
	LPDIRECT3DDEVICE9 pd3dDevice = static_cast<LPDIRECT3DDEVICE9>(_renderer->GetDevice());
	
	switch (rotation)
	{
		
	case 0:
		D3DXMatrixTranslation(&matTranslate, positionX, positionY, positionZ);
		D3DXMatrixRotationX(&matRotateX, rotationX);
		break;
		//Move forward
	case 1:
		positionZ = positionZ + 0.1f;
		//positionX = positionY + 0.1f;
		D3DXMatrixRotationX(&matRotateX, rotationX);
		break;
		//Move left
	case 2:
		//rotationX = -1.0f;
		positionX = positionX - 0.1f;
		D3DXMatrixRotationX(&matRotateX, rotationX);
		D3DXMatrixRotationY(&matRotateX, rotationY);
		//D3DXMatrixRotationY(&matRotateY, 0.0f);
		//D3DXMatrixRotationZ(&matRotateZ, 0.0f);
		break;
		//Move backwards
	case 3:
		positionZ = positionZ - 0.1f;
		D3DXMatrixRotationX(&matRotateX, rotationX);
		break;
		//Move right
	case 4:
		//rotationX = 1.0f;
		positionX = positionX + 0.1f;
		D3DXMatrixRotationX(&matRotateX, rotationX);
		break;
	}
	D3DXMatrixTranslation(&matTranslate, positionX, positionY, positionZ);
	matWorld = matTranslate*matRotateX;
	pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	SetRotation(0);
}

/// <summary>
/// Setups the matrices.
/// </summary>
/// <param name="_renderer">The _renderer.</param>
void EntityModel::SetupMatrices(Renderer* _renderer)
{
//	LPDIRECT3DDEVICE9 pd3dDevice = static_cast<LPDIRECT3DDEVICE9>(_renderer->GetDevice());
//	D3DXMATRIX trans_matrix;
//
//	D3DXMatrixTranslation(&trans_matrix,//Matrix
//
//		-1,           //X offset
//
//		-20,           //Y offset
//
//		100);          //Z offset

	//pd3dDevice->SetTransform(D3DTS_WORLD, &trans_matrix);
	//D3DXMATRIX matTranslate;    // a matrix to store the translation information
	//// build a matrix to move the model 12 units along the x-axis and 4 units along the y-axis
	//// store it to matTranslate
	//D3DXMATRIX world_matrix;
	//D3DXMATRIX translation_matrix;
	//D3DXMATRIX rotation_matrix;

	////3 units to the right and 10 units down the Z-axis

	//D3DXMatrixTranslation(&translation_matrix,
	//	3,   //X

	//	0,   //Y

	//	10);  //Z


	//D3DXMatrixRotationX(&rotation_matrix, D3DX_PI / 2);   //Rotate 90 degrees around the X-axis


	//D3DXMatrixMultiply(&world_matrix, &translation_matrix, &rotation_matrix);

	//pd3dDevice->SetTransform(D3DTS_WORLD, &world_matrix);
	//sceneManager = new SceneManager();

	// Set up world matrix
	//D3DXMATRIXA16 matWorld;
	//D3DXMatrixRotationZ(&matWorld, timeGetTime() / 1000.0f);
	//	pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	// Set up world matrix
	ChangeRotation(_renderer);
	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we set the
	// eye five units back along the z-axis and up three units, look at the 
	// origin, and define "up" to be in the y-direction.
	//D3DXVECTOR3 vEyePt(0.0f, 3.0f, -5.0f);
	//D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	//D3DXMATRIXA16 matView;
	//D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	//pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	// For the projection matrix, we set up a perspective transform (which
	// transforms geometry from 3D view space to 2D viewport space, with
	// a perspective divide making objects smaller in the distance). To build
	// a perpsective transform, we need the field of view (1/4 pi is common),
	// the aspect ratio, and the near and far clipping planes (which define at
	// what distances geometry should be no longer be rendered).
	/*D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);*/
}

/// <summary>
/// Initializes the tiger.
/// </summary>
/// <param name="_renderer">The _renderer.</param>
/// <returns></returns>HRESULT EntityModel::InitGeometry(ResourceManager* _resourceManager)
HRESULT EntityModel::InitGeometry(ResourceManager* _resourceManager)
{
	// Load the mesh from the specified file
	mesh = _resourceManager->LoadMesh("..\\Meshes\\", fileName);
	texture = _resourceManager->LoadTexture("..\\Textures\\", texture->GetFileName());
	if (!mesh)
	{
		Log::Instance()->LogMessage("EntityModel - Geometry was failed to initialize.", Log::MESSAGE_ERROR);
		return E_FAIL;
	}

	return S_OK;
}

/// <summary>
/// Sets the rotation.
/// </summary>
/// <param name="_rotation">The _rotation.</param>
void EntityModel::SetRotation(int _rotation)
{
	rotation = _rotation;
}

/// <summary>
/// Gets the rotation.
/// </summary>
/// <returns></returns>
int EntityModel::GetRotation()
{
	return rotation;
}

/// <summary>
/// Notifies the specified state.
/// </summary>
/// <param name="state">The state.</param>
void EntityModel::Notify(byte _state[])
{
	if (KEYDOWN(DIK_W, _state))
	{
		SetRotation(3);

	}

	if (KEYDOWN(DIK_A, _state))
	{
		SetRotation(4);
		
	}

	if (KEYDOWN(DIK_S, _state))
	{
		SetRotation(1);
		
	}

	if (KEYDOWN(DIK_D, _state))
	{
		SetRotation(2);
		
	}
	if (MSTATE(0, _state))
	{
		std::cout << "LINKS";
	}
}
