#include "Entity.h"
#include "Vector3Math.h"
#include <math.h>
#include "Renderer.h"

Entity::Entity() {
	Reset();
}

/// <summary>
/// Resets the matrices to their default matrix values
/// </summary>
void Entity::Reset()
{
	MatrixIdentity(&_matTranslate);
	MatrixIdentity(&_matRotate);
	MatrixIdentity(&_matScale);
	MatrixIdentity(&_matTransform);
	_matRotateX = _matRotateY = _matRotateZ = 0.0f;

}

Matrix* Entity::LookAtLH(Matrix* out, const Vector3* eye, const Vector3* at, const Vector3* pup)
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

Matrix* Entity::PerspectiveFovLH(Matrix* out, float fovy, float aspect, float zn, float zf)
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

Matrix* Entity::Translation(Matrix* out, float x, float y, float z)
{
	MatrixIdentity(out);

	out->m[3][0] = x;
	out->m[3][1] = y;
	out->m[3][2] = z;

	return out;
}

Matrix* Entity::RotationX(Matrix* out, float angle)
{
	MatrixIdentity(out);

	out->m[1][1] = cos(angle);
	out->m[2][2] = cos(angle);
	out->m[1][2] = sin(angle);
	out->m[2][1] = -sin(angle);

	return out;
}

Matrix* Entity::RotationY(Matrix* out, float angle)
{
	MatrixIdentity(out);

	out->m[0][0] = cos(angle);
	out->m[2][2] = cos(angle);
	out->m[0][2] = -sin(angle);
	out->m[2][0] = sin(angle);

	return out;
}

Matrix* Entity::RotationZ(Matrix* out, float angle)
{
	MatrixIdentity(out);

	out->m[0][0] = cos(angle);
	out->m[1][1] = cos(angle);
	out->m[0][1] = sin(angle);
	out->m[1][0] = -sin(angle);

	return out;
}

Matrix* Entity::Scaling(Matrix* out, float x, float y, float z)
{
	MatrixIdentity(out);

	out->m[0][0] = x;
	out->m[1][1] = y;
	out->m[2][2] = z;

	return out;
}

Matrix* Entity::MatrixIdentity(Matrix* out)
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
Matrix* __stdcall Entity::Scale(Matrix *out, float x, float y, float z)
{
	MatrixIdentity(out);
	out->m[0][0] = x;
	out->m[1][1] = y;
	out->m[2][2] = z;
	return out;
}
Matrix* __stdcall Entity::Translate(Matrix *out, float x, float y, float z)
{
	MatrixIdentity(out);
	out->m[3][0] = x;
	out->m[3][1] = y;
	out->m[3][2] = z;
	return out;
}
Matrix* __stdcall Entity::RotateX(Matrix *out, float angle)
{
	MatrixIdentity(out);
	out->m[1][1] = cos(angle);
	out->m[2][2] = cos(angle);
	out->m[1][2] = sin(angle);
	out->m[2][1] = -sin(angle);
	return out;
}

Matrix* __stdcall Entity::RotateY(Matrix *out, float angle)
{
	MatrixIdentity(out);
	out->m[0][0] = cos(angle);
	out->m[2][2] = cos(angle);
	out->m[0][2] = -sin(angle);
	out->m[2][0] = sin(angle);
	return out;
}
///* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//Summary: Absolute translation
//Parameters:
//[in] x - X position
//[in] y - Y position
//[in] z - Z position
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//void CWorldTransform::TranslateAbs(float x, float y, float z)
//{
//	m_translate._41 = x;
//	m_translate._42 = y;
//	m_translate._43 = z;
//}
//
///* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//Summary: Relative translation
//Parameters:
//[in] x - X amount
//[in] y - Y amount
//[in] z - Z amount
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//void CWorldTransform::TranslateRel(float x, float y, float z)
//{
//	m_translate._41 += x;
//	m_translate._42 += y;
//	m_translate._43 += z;
//}
//
///* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//Summary: Absolute rotation
//Parameters:
//[in] x - X radians
//[in] y - Y radians
//[in] z - Z radians
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//void CWorldTransform::RotateAbs(float x, float y, float z)
//{
//	m_rotationX = x;
//	m_rotationY = y;
//	m_rotationZ = z;
//	D3DXMatrixRotationYawPitchRoll(&m_rotate, y, x, z);
//}
//
///* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//Summary: Relative rotation
//Parameters:
//[in] x - X radians
//[in] y - Y radians
//[in] z - Z radians
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//void CWorldTransform::RotateRel(float x, float y, float z)
//{
//	m_rotationX += x;
//	m_rotationY += y;
//	m_rotationZ += z;
//	D3DXMatrixRotationYawPitchRoll(&m_rotate, m_rotationY, m_rotationX, m_rotationZ);
//}
//
///* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//Summary: Absolute scale.
//Parameters:
//[in] x - X size
//[in] y - Y size
//[in] z - Z size
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//void CWorldTransform::ScaleAbs(float x, float y, float z)
//{
//	m_scale._11 = x;
//	m_scale._22 = y;
//	m_scale._33 = z;
//}
//
///* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//Summary: Relative scale.
//Parameters:
//[in] x - X size
//[in] y - Y size
//[in] z - Z size
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//void CWorldTransform::ScaleRel(float x, float y, float z)
//{
//	m_scale._11 += x;
//	m_scale._22 += y;
//	m_scale._33 += z;
//}
//
///* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//Summary: Get the transformation matrix
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//D3DXMATRIX* CWorldTransform::GetTransform()
//{
//
//	m_transform = m_scale * m_rotate * m_translate;
//	return &m_transform;
//}