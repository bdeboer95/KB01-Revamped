#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Matrix.h"

class Renderer;
class ResourceManager;
class Vector3;
class Texture;
class Mesh;

class Entity
{
protected:
	Mesh*				_mesh;
	Texture*			_texture;

	char*				_meshLocation; //the filename of the entitymodel's mesh
	char*				_textureLocation;

	float				_positionX;		//position value for the x-axis
	float				_positionY;		//position value for the y-axis
	float				_positionZ;		//position value for the z-axis

	float				_rotationX;		//rotation value for the x-axis
	float				_rotationY;		//rotation value for the y-axis

	float				_speed;			//multiplification factor for speed at which the entity rotates or translates itself

	Matrix				_matRotateX;	//the matrix for the rotation on the x-axis
	Matrix				_matRotateY;	//the matrix for the rotation on the y-axis
	Matrix				_matRotateZ;	//the matrix for the rotation on the z-axis

	Matrix				_matScale;		//the matrix for the scaling of the skybox
	Matrix				_matTranslate;	//the translation matrix for the entitymodel
	Matrix				_matWorld;		//the matrix that contains  the multiplication of all the modification matrices (scale, rotate, translate)

	virtual void		Reset();		//Resets the matrix of the entity to its default values
	virtual void		Render(Renderer* renderer) = 0;
	virtual void		SetupMatrices() = 0;
	virtual bool		InitGeometry(Renderer* renderer, ResourceManager* resourceManager) = 0;

public:
	Entity();
	virtual ~Entity(); 

};

#endif
