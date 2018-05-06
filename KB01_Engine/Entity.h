#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Matrix.h"

class Vector3;
class Renderer;
class Entity
{
protected:
	float				_positionX;	//position value for the x-axis
	float				_positionY;	//position value for the y-axis
	float				_positionZ;	//position value for the z-axis
	float				_rotationX;	//rotation value for the x-axis
	float				_rotationY;	//rotation value for the y-axis
	float				_rotationZ;  //rotation value for the z-axis
	float				_speed;      //multiplification factor for speed at which the entity rotates or translates itself
	Matrix				_matRotateX; //the matrix for the rotation on the x-axis
	Matrix				_matRotateY;	//the matrix for the rotation on the y-axis
	Matrix				_matRotateZ;	//the matrix for the rotation on the z-axis
	Matrix				_matWorld;	//the matrix that contains  the multiplication of all the modification matrices (scale, rotate, translate)
	Matrix				_matScale;	//the matrix for the scaling of the skybox
	Matrix				_matTranslate; //the translation matrix for the entitymodel

public:
	Entity();
	virtual ~Entity(); //Destructor
	void Reset(); //Resets the matrix of the entity to its default values
	Matrix*  LookAtLH(Matrix* out, const Vector3* eye, const Vector3* at, const Vector3* pup); //Builds a left-handed look-at matrix
	Matrix*  PerspectiveFovLH(Matrix* out, float fovy, float aspect, float zn, float zf); //Builds a left-handed perspective projection matrix based on a field of view
	Matrix* MatrixIdentity(Matrix* out); //TODO
	Matrix*  __stdcall Translate(Matrix* out, float x, float y, float z);//Used to translate an object containing a matrix with specified x, y and z values
	Matrix*  __stdcall RotateX(Matrix* out, float angle);//Used to rotate an object containing a matrix on the x-axis
	Matrix*  __stdcall RotateY(Matrix* out, float angle);//Used to rotate an object containing a matrix on the y-axis
	//Matrix*  __stdcall RotateZ(Matrix* out, float angle);//Used to rotate an object containing a matrix on the z-axis
	Matrix*  __stdcall Scale(Matrix* out, float x, float y, float);//Used to scale an object containing a matrix with an x, y and z value
	//Matrix* __stdcall Scale(Matrix* out, float x, float y, float);//Put back std call if it dont work
};
#endif
