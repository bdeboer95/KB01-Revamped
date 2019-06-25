#include "EntityModel.h"
#include <iostream>
#include <vector>
#include "Vector3.h"

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
	Log::Instance()->LogMessage("~EntityModel - EntityModel cleaned up!", Log::MESSAGE_INFO);
}

/// <summary>
/// Renders the entitymodel with the specified renderer.
/// </summary>
/// <param name="_renderer">The specified renderer.</param>
void EntityModel::Render(Renderer* _renderer)
{
	for (unsigned int i = 0; i < _mesh->GetNumberOfMaterials(); i++)
	{
		_renderer->SetMaterial(_mesh->GetMeshMaterials(), i);
		_renderer->SetTexture(_textureContainer->GetTexture(), i);
		_renderer->DrawSubset(_mesh->GetMesh(), i);
	}
	_renderer->SetTransform(_renderer->WORLD, &_matWorld);

}


/// <summary>
/// Set up the matrices.
/// </summary>
/// <param name="_renderer">The _renderer.</param>
void EntityModel::SetupMatrices()
{
	Scale(&_matScale, _scaleVector);
	Translate(&_matTranslate, _positionX, _positionY, _positionZ);
	RotateY(&_matRotateY, _rotationY);
	RotateX(&_matRotateX, _rotationX);
	_matWorld = _matScale * _matTranslate*_matRotateY*_matRotateX;
	
}

/// <summary>
/// Initializes the mesh and texture for this entitymodel
/// </summary>
/// <param name="_renderer">The _renderer.</param>
/// <returns></returns>HRESULT EntityModel::InitGeometry(ResourceManager* _resourceManager)
HRESULT EntityModel::InitGeometry(ResourceManager* _resourceManager)
{
	// Load the mesh from the specified file
	_mesh = _resourceManager->LoadMesh("..\\Assets\\Meshes\\", _fileName);
	_textureContainer = _resourceManager->LoadTexture("..\\Assets\\Textures\\", _textureContainer->GetFileName());
	if (!_mesh)
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

	Translate(&_matTranslate, _positionX, _positionY, _positionZ);
	RotateX(&_matRotateX, _rotationX);
	RotateY(&_matRotateY, _rotationY);
	_matWorld = _matScale*_matTranslate*_matRotateX*_matRotateY;
}
