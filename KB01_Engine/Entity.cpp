#include "Entity.h"

#include "Renderer.h"
#include "ResourceManager.h"

Entity:: Entity() 
{
	Reset();
}

Entity::~Entity()
{

}

/// <summary>
/// Resets all the transformation matrices to their default matrix values
/// </summary>
void Entity::Reset()
{
	_positionX = 0.0f;
	_positionY = 0.0f;
	_positionZ = 0.0f;

	_rotationX = 0.0f;
	_rotationY = 0.0f;

	_speed = 0.0f;

	_matRotateX.Identity();
	_matRotateY.Identity();
	_matRotateZ.Identity();

	_matScale.Identity();
	_matTranslate.Identity();
	_matWorld.Identity();
}
