#include "EntityModel.h"

/// <summary>
/// Initializes a new instance of the <see cref="EntityModel"/> class.
/// </summary>
EntityModel::EntityModel(std::string fileName, std::string textureName, float positionX, float positionY, float positionZ)
{
	_positionX = positionX;
	_positionY = positionY;
	_positionZ = positionZ;

	_speed = 0.1f;

	_fileName = fileName;
	_texture = new Texture(textureName);

	SetupMatrices();
}

/// <summary>
/// Finalizes an instance of the <see cref="EntityModel"/> class.
/// </summary>
EntityModel::~EntityModel()
{
	//TODO
	Log::Instance()->LogMessage("~EntityModel - EntityModel cleaned up!", Log::MESSAGE_INFO);
}

void EntityModel::Render(Renderer* renderer)
{
	for (unsigned int i = 0; i < _mesh->GetNumberOfMaterials(); i++)
	{
		renderer->SetMaterial(_mesh->GetMeshMaterials(), i);
		renderer->SetTexture(_texture->GetTextures(), i);
		renderer->DrawSubset(_mesh->GetMesh(), i);
	}

	renderer->SetTransform(Renderer::WORLD, &_matWorld);
}

/// <summary>
/// Sets the rotation.
/// </summary>
/// <param name="_rotation">The _rotation.</param>
void EntityModel::SetRotation(int rotation)
{
	_rotation = rotation;
}

/// <summary>
/// Gets the rotation.
/// </summary>
/// <returns></returns>
int EntityModel::GetRotation()
{
	return _rotation;
}

void EntityModel::SetupMatrices()
{
	_matTranslate.Translate(_positionX, _positionY, _positionZ);

	_matRotateX.RotateX(_rotationX);
	_matRotateY.RotateY(_rotationY);

	_matScale.Scale(1, 1, 1);

	_matWorld = _matScale * _matTranslate * _matRotateY * _matRotateX;
}

/// <summary>
/// Initializes the tiger.
/// </summary>
/// <param name="_renderer">The _renderer.</param>
/// <returns></returns>HRESULT EntityModel::InitGeometry(ResourceManager* _resourceManager)
HRESULT EntityModel::InitGeometry(Renderer* renderer, ResourceManager* resourceManager)
{
	// Load the mesh from the specified file
	_mesh = resourceManager->LoadMesh("..\\Assets\\Meshes\\", _fileName);
	_texture = resourceManager->LoadTexture("..\\Assets\\Textures\\", _texture->GetFileName());

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
		_positionX = _positionX + _speed;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::MOVE_LEFT)
	{
		_positionX = _positionX - _speed;
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
		_rotationY = _rotationY + y;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::ROTATE_DOWN)
	{

	}

	SetupMatrices();
}
