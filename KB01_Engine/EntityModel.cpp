#include "EntityModel.h"
#include <iostream>
#include <vector>
#include "Vector3.h"
//#include <dinput.h> //does this also need to be removed?

//#define KEYDOWN(name, key) (name[key])
//#define MSTATE(name, key) (name[key])

/// <summary>
/// Initializes a new instance of the <see cref="EntityModel"/> class.
/// </summary>
EntityModel::EntityModel(std::string fileName, std::string textureName, float positionX, float positionY, float positionZ, Vector3 scaleVector)
{
	_fileName = fileName;
	_textureContainer = new TextureContainer(textureName);
	_positionX = positionX;
	_positionY = positionY;
	_positionZ = positionZ;
	_scaleVector = scaleVector;
	_speed = 0.1f;
	Log::Instance()->LogMessage("EntityModel - Created.", Log::MESSAGE_INFO);
}

/// <summary>
/// Finalizes an instance of the <see cref="EntityModel"/> class.
/// </summary>
EntityModel::~EntityModel()
{
	//TODO
	Log::Instance()->LogMessage("~EntityModel - EntityModel cleaned up!", Log::MESSAGE_INFO);
}

/// <summary>
/// Renders the entitymodel with the specified renderer.
/// </summary>
/// <param name="_renderer">The specified renderer.</param>
void EntityModel::Render(Renderer* _renderer)
{

	for (UINT i = 0; i < mesh->GetNumberOfMaterials(); i++)
	{
		_renderer->SetMaterial(mesh->GetMeshMaterials(), i);
		_renderer->SetTexture(_textureContainer->GetTexture(), i);
		_renderer->DrawSubset(mesh->GetMesh(), i);
	}

}


/// <summary>
/// Handles translation and rotation for the entitymodel
/// </summary>
/// <param name="_renderer">The renderer used to draw the entitymodels on the backbuffer</param>
void EntityModel::ChangeRotation(Renderer* _renderer)
{
	//// Set up world matrix
	//switch (rotation)
	//{

	//case 0:

	//	break;

	//case 1:
	//	//Move forward
	//	_positionZ = _positionZ + 0.1f;
	//	break;
	//case 2:
	//	//Move left
	//	_positionX = _positionX - 0.1f;
	//	break;

	//case 3:
	//	//Move backwards
	//	_positionZ = _positionZ - 0.1f;
	//	break;
	//case 4:
	//	//Move right
	//	_positionX = _positionX + 0.1f;
	//	break;
	//}
	
}

/// <summary>
/// Setups the matrices.
/// </summary>
/// <param name="_renderer">The _renderer.</param>
void EntityModel::SetupMatrices(Renderer* _renderer)
{
	Scale(&_matScale, _scaleVector);
	Translate(&_matTranslate, _positionX, _positionY, _positionZ);
	RotateY(&_matRotateY, _rotationY);
	RotateX(&_matRotateX, _rotationX);
	_matWorld = _matScale * _matTranslate*_matRotateY*_matRotateX;
	_renderer->SetTransform(_renderer->WORLD, &_matWorld);
	/*SetRotation(0);*/
	//renderer->setTransform(&matWorld)

//
//	D3DXMatrixTranslation(&trans_matrix,//Matrix
//
//		-1,           //X offset
//
//		-20,           //Y offset
//
//		100);          //Z offset

	//pd3dDevice->SetTransform(D3DTS_WORLD, &trans_matrix);
	//D3DXMATRIX _matTranslate;    // a matrix to store the translation information
	//// build a matrix to move the model 12 units along the x-axis and 4 units along the y-axis
	//// store it to _matTranslate
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
	//ChangeRotation(_renderer);
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
	mesh = _resourceManager->LoadMesh("..\\Assets\\Meshes\\", _fileName);
	_textureContainer = _resourceManager->LoadTexture("..\\Assets\\Textures\\", _textureContainer->GetFileName());
	if (!mesh)
	{
		Log::Instance()->LogMessage("EntityModel - Geometry was failed to initialize.", Log::MESSAGE_ERROR);
		return E_FAIL;
	}

	return S_OK;
}

/// <summary>
/// Notifies the specified state.
/// </summary>
/// <param name="state">The state.</param>
void EntityModel::Notify(TRANSFORMATIONEVENT transformationEvent, float x, float y)
{
	if (transformationEvent == TRANSFORMATIONEVENT::MOVE_RIGHT)
	{
		_positionX = _positionX - _speed;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::MOVE_LEFT)
	{
		_positionX = _positionX + _speed;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::MOVE_BACKWARDS)
	{
		_positionZ = _positionZ - _speed;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::MOVE_FORWARD)
	{
		_positionZ = _positionZ + _speed;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::ROTATE_LEFT)
	{
		_rotationY = _rotationY - y;
		/*rotationX = rotationX + x;*/
	}

	//}
	//if (KEYDOWN(DIK_DOWN, _state)) {
	//rotationX = rotationX - 0.010f;

	//}

	//if (KEYDOWN(DIK_UP, _state)) {
	//rotationX = rotationX + 0.010f;

	//}
	//if (KEYDOWN(DIK_LEFT, _state)) {
	//	rotationY = rotationY - 0.010f;

	//}
	//if (KEYDOWN(DIK_RIGHT, _state)) {
	//	rotationY = rotationY + 0.010f;

	//}
	//if (KEYDOWN(DIK_A, _state))
	//{


	//	



	//}

	//if (KEYDOWN(DIK_S, _state))
	//{
	//	

	//}

	//if (KEYDOWN(DIK_D, _state))
	//{
	//	positionX = positionX + speed;


	//}
	//if (MSTATE(0, _state))
	//{

	//}
	//if (rotationY >= 6.28f)
	//	rotationY = 0.0f;

	//if (rotationX >= 6.28f)
	//	rotationX = 0.0f;

	Translate(&_matTranslate, _positionX, _positionY, _positionZ);
	RotateX(&_matRotateX, _rotationX);
	RotateY(&_matRotateY, _rotationY);
	_matWorld = _matScale*_matTranslate*_matRotateX*_matRotateY;
}
