#include "MatrixMath.h"
#include "Vector3.h"


MatrixMath::MatrixMath()
{
}


MatrixMath::~MatrixMath()
{

}


inline Matrix* MatrixMath::MatrixLookAtLH(Matrix* out, const Vector3* eye, const Vector3* at, const Vector3* pup)
{
	Vector3 right, rightn, up, upn, vec, vec2;

	Vector3::Vec3Subtract(&vec2, at, eye);
	Vector3::Vec3Normalize(&vec, &vec2);
	Vector3::Vec3Cross(&right, pup, &vec);

	Vector3::Vec3Cross(&up, &vec, &right);
	Vector3::Vec3Normalize(&rightn, &right);
	Vector3::Vec3Normalize(&upn, &up);

	out->m[0][0] = rightn._x;
	out->m[1][0] = rightn._y;
	out->m[2][0] = rightn._z;
	out->m[3][0] = -Vector3::Vec3Dot(&rightn, eye);
	out->m[0][1] = upn._x;
	out->m[1][1] = upn._y;
	out->m[2][1] = upn._z;
	out->m[3][1] = -Vector3::Vec3Dot(&upn, eye);
	out->m[0][2] = vec._x;
	out->m[1][2] = vec._y;
	out->m[2][2] = vec._z;
	out->m[3][2] = -Vector3::Vec3Dot(&vec, eye);
	out->m[0][3] = 0.0f;
	out->m[1][3] = 0.0f;
	out->m[2][3] = 0.0f;
	out->m[3][3] = 1.0f;

	return out;

}

Matrix* MatrixMath::MatrixPerspectiveFovLH(Matrix* out, float fovy, float aspect, float zn, float zf)
{
	return nullptr;
}
