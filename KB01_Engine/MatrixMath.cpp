#include "MatrixMath.h"
#include "Vector3Math.h"
#include <math.h>

MatrixMath::MatrixMath()
{
}

MatrixMath::~MatrixMath()
{

}

Matrix* MatrixMath::LookAtLH(Matrix* out, const Vector3* eye, const Vector3* at, const Vector3* pup)
{
	Vector3 right, rightn, up, upn, vec, vec2;
	Vector3Math* vector3Math = new Vector3Math();

	vector3Math->Vec3Subtract(&vec2, at, eye);
	vector3Math->Vec3Normalize(&vec, &vec2);
	vector3Math->Vec3Cross(&right, pup, &vec);

	vector3Math->Vec3Cross(&up, &vec, &right);
	vector3Math->Vec3Normalize(&rightn, &right);
	vector3Math->Vec3Normalize(&upn, &up);

	out->m[0][0] = rightn._x;
	out->m[1][0] = rightn._y;
	out->m[2][0] = rightn._z;
	out->m[3][0] = -vector3Math->Vec3Dot(&rightn, eye);
	out->m[0][1] = upn._x;
	out->m[1][1] = upn._y;
	out->m[2][1] = upn._z;
	out->m[3][1] = -vector3Math->Vec3Dot(&upn, eye);
	out->m[0][2] = vec._x;
	out->m[1][2] = vec._y;
	out->m[2][2] = vec._z;
	out->m[3][2] = -vector3Math->Vec3Dot(&vec, eye);
	out->m[0][3] = 0.0f;
	out->m[1][3] = 0.0f;
	out->m[2][3] = 0.0f;
	out->m[3][3] = 1.0f;

	return out;

}

Matrix* MatrixMath::PerspectiveFovLH(Matrix* out, float fovy, float aspect, float zn, float zf)
{
	MatrixIdentity(out);
	out->m[0][0] = 1.0f / (aspect * tan(fovy / 2.0f));
	out->m[1][1] = 1.0f / tan(fovy / 2.0f);
	out->m[2][2] = zf / (zf - zn);
	out->m[2][3] = 1.0f;
	out->m[3][2] = (zf * zn) / (zn - zf);
	out->m[3][3] = 0.0f;
	return out;
}

Matrix* MatrixMath::Translation(Matrix* out, float x, float y, float z)
{
	MatrixIdentity(out);

	out->m[3][0] = x;
	out->m[3][1] = y;
	out->m[3][2] = z;

	return out;
}

Matrix* MatrixMath::RotationX(Matrix* out, float angle)
{
	MatrixIdentity(out);

	out->m[1][1] = cos(angle);
	out->m[2][2] = cos(angle);
	out->m[1][2] = sin(angle);
	out->m[2][1] = -sin(angle);

	return out;
}

Matrix* MatrixMath::RotationY(Matrix* out, float angle)
{
	MatrixIdentity(out);

	out->m[0][0] = cos(angle);
	out->m[2][2] = cos(angle);
	out->m[0][2] = -sin(angle);
	out->m[2][0] = sin(angle);

	return out;
}

Matrix* MatrixMath::RotationZ(Matrix* out, float angle)
{
	MatrixIdentity(out);

	out->m[0][0] = cos(angle);
	out->m[1][1] = cos(angle);
	out->m[0][1] = sin(angle);
	out->m[1][0] = -sin(angle);

	return out;
}

Matrix* MatrixMath::Scaling(Matrix* out, float x, float y, float z)
{
	MatrixIdentity(out);

	out->m[0][0] = x;
	out->m[1][1] = y;
	out->m[2][2] = z;

	return out;
}

inline  Matrix* MatrixMath::MatrixIdentity(Matrix* out)
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
Matrix* __stdcall MatrixMath::Scale(Matrix *out, float x, float y, float z)
{
	MatrixIdentity(out);
	out->m[0][0] = x;
	out->m[1][1] = y;
	out->m[2][2] = z;
	return out;
}
Matrix* __stdcall MatrixMath::Translate(Matrix *out, float x, float y, float z)
{
	MatrixIdentity(out);
	out->m[3][0] = x;
	out->m[3][1] = y;
	out->m[3][2] = z;
	return out;
}
Matrix* __stdcall MatrixMath::RotateX(Matrix *out, float angle)
{
	MatrixIdentity(out);
	out->m[1][1] = cos(angle);
	out->m[2][2] = cos(angle);
	out->m[1][2] = sin(angle);
	out->m[2][1] = -sin(angle);
	return out;
}

Matrix* __stdcall MatrixMath::RotateY(Matrix *out, float angle)
{
	MatrixIdentity(out);
	out->m[0][0] = cos(angle);
	out->m[2][2] = cos(angle);
	out->m[0][2] = -sin(angle);
	out->m[2][0] = sin(angle);
	return out;
}
