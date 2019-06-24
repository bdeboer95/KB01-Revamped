#include "Entity.h"
#include <math.h>
#include "Renderer.h"
#include "Vector3.h"


/// <summary>
/// Initializes a new instance of the <see cref="Entity"/> class.
/// </summary>
Entity::Entity() {
	Reset();
}


/// <summary>
/// Finalizes an instance of the <see cref="Entity"/> class.
/// </summary>
Entity::~Entity() {
	delete _matTranslate;
	delete _matRotateX;
	delete _matRotateY;
	delete _matRotateZ;
	delete _matScale;
	delete _matWorld;
	//todo
}

/// <summary>
/// Resets all the transformation matrices to their default matrix values
/// </summary>
void Entity::Reset()
{
	ResetMatrix(&_matTranslate);
	ResetMatrix(&_matRotateX);
	ResetMatrix(&_matRotateY);
	ResetMatrix(&_matRotateZ);
	ResetMatrix(&_matScale);
	ResetMatrix(&_matWorld);
	_rotationX = 0.0f;
	_rotationY = 0.0f;
	_rotationZ = 0.0f;

}

/// <summary>
/// Looks at lh.
/// </summary>
/// <param name="out">The out.</param>
/// <param name="eye">The eye.</param>
/// <param name="at">At.</param>
/// <param name="pup">The pup.</param>
/// <returns></returns>
Matrix* Entity::LookAtLH(Matrix* out, const Vector3* eye, const Vector3* at, const Vector3* pup)
{
	Vector3 right, rightn, up, upn, vec, vec2;

	Vector3::Vec3Subtract(&vec2, at, eye);
	Vector3::Vec3Normalize(&vec, &vec2);
	Vector3::Vec3Cross(&right, pup, &vec);

	Vector3::Vec3Cross(&up, &vec, &right);
	Vector3::Vec3Normalize(&rightn, &right);
	Vector3::Vec3Normalize(&upn, &up);

	out->m[0][0] = rightn.GetX();
	out->m[1][0] = rightn.GetY();
	out->m[2][0] = rightn.GetZ();
	out->m[3][0] = Vector3::Vec3Dot(&rightn, eye);
	out->m[0][1] = upn.GetX();
	out->m[1][1] = upn.GetY();
	out->m[2][1] = upn.GetZ();
	out->m[3][1] = Vector3::Vec3Dot(&upn, eye);
	out->m[0][2] = vec.GetX();
	out->m[1][2] = vec.GetY();
	out->m[2][2] = vec.GetZ();
	out->m[3][2] = Vector3::Vec3Dot(&vec, eye);
	out->m[0][3] = 0.0f;
	out->m[1][3] = 0.0f;
	out->m[2][3] = 0.0f;
	out->m[3][3] = 1.0f;

	return out;

}

/// <summary>
/// Perspectives the fov lh.
/// </summary>
/// <param name="out">The out.</param>
/// <param name="fovy">The fovy.</param>
/// <param name="aspect">The aspect.</param>
/// <param name="zn">The zn.</param>
/// <param name="zf">The zf.</param>
/// <returns></returns>
Matrix* Entity::PerspectiveFovLH(Matrix* out, float fovy, float aspect, float zn, float zf)
{
	ResetMatrix(out);
	out->m[0][0] = 1.0f / (aspect * tan(fovy / 2.0f));
	out->m[1][1] = 1.0f / tan(fovy / 2.0f);
	out->m[2][2] = zf / (zf - zn);
	out->m[2][3] = 1.0f;
	out->m[3][2] = (zf * zn) / (zn - zf);
	out->m[3][3] = 0.0f;
	return out;
}

/// <summary>
/// Resets the matrix to the default matrix values
/// The last 4 would be 1, while the rest is 0
/// </summary>
/// <param name="out"> The matrix that needs to be reset </param>
/// <returns>the matrix that was resetted</returns>
Matrix* Entity::ResetMatrix(Matrix* out)
{
	if (!out) return NULL;
	out->m[0][1] = 0.0f;
	out->m[0][2] = 0.0f;
	out->m[0][3] = 0.0f;
	out->m[1][0] = 0.0f;
	out->m[1][2] = 0.0f;
	out->m[1][3] = 0.0f;
	out->m[2][0] = 0.0f;
	out->m[2][1] = 0.0f;
	out->m[2][3] = 0.0f;
	out->m[3][0] = 0.0f;
	out->m[3][1] = 0.0f;
	out->m[3][2] = 0.0f;
	out->m[0][0] = 1.0f;
	out->m[1][1] = 1.0f;
	out->m[2][2] = 1.0f;
	out->m[3][3] = 1.0f;
	return out;
}

/// <summary>
/// Scales the specified matrix with separate x, y and z values
/// </summary>
/// <param name="out">The out.</param>
/// <param name="x">The x.</param>
/// <param name="y">The y.</param>
/// <param name="z">The z.</param>
/// <returns></returns>
Matrix*  Entity::Scale(Matrix* out, float x, float y, float z)
{
	ResetMatrix(out);
	out->m[0][0] = x; //set the x-scale in the array
	out->m[1][1] = y; //set the y-scale in the matrix array
	out->m[2][2] = z; //set the z-scale in the matrix array
	return out;
}

/// <summary>
/// Scales the specified matrix with a scale vector
/// </summary>
/// <param name="out">The out.</param>
/// <param name="scaleVector">The scale vector.</param>
/// <returns></returns>
Matrix* Entity::Scale(Matrix* out, Vector3 scaleVector)
{
	ResetMatrix(out);
	out->m[0][0] = scaleVector.GetX(); //set the x-scale in the array
	out->m[1][1] = scaleVector.GetY(); //set the y-scale in the matrix array
	out->m[2][2] = scaleVector.GetZ(); //set the z-scale in the matrix array
	return out;
}

/// <summary>
/// Translates the specified out.
/// </summary>
/// <param name="out">The out.</param>
/// <param name="x">The x.</param>
/// <param name="y">The y.</param>
/// <param name="z">The z.</param>
/// <returns></returns>
Matrix*  Entity::Translate(Matrix *out, float x, float y, float z)
{
	ResetMatrix(out);
	out->m[3][0] = x;
	out->m[3][1] = y;
	out->m[3][2] = z;
	return out;
}

/// <summary>
/// Rotates the x.
/// </summary>
/// <param name="out">The out.</param>
/// <param name="angle">The angle.</param>
/// <returns></returns>
Matrix*  Entity::RotateX(Matrix *out, float angle)
{
	ResetMatrix(out);
	out->m[1][1] = cos(angle);
	out->m[2][2] = cos(angle);
	out->m[1][2] = sin(angle);
	out->m[2][1] = -sin(angle);
	return out;
}

/// <summary>
/// Rotates the y.
/// </summary>
/// <param name="out">The out.</param>
/// <param name="angle">The angle.</param>
/// <returns></returns>
Matrix*  Entity::RotateY(Matrix *out, float angle)
{
	ResetMatrix(out);
	out->m[0][0] = cos(angle);
	out->m[2][2] = cos(angle);
	out->m[0][2] = -sin(angle);
	out->m[2][0] = sin(angle);
	return out;
}
