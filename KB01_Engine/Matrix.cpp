#include "Matrix.h"
#include "Vector3.h"
#include <string.h>
#include <math.h>

//  Matrix::Matrix()
//{
//}

Matrix::Matrix(const float *pf)
{
	if (!pf) return;
	memcpy(&_11, pf, sizeof(Matrix));
}

//  Matrix::Matrix(const D3DMATRIX& mat)
//{
//	memcpy(&_11, &mat, sizeof(Matrix));
//}

Matrix::Matrix(float f11, float f12, float f13, float f14,
	float f21, float f22, float f23, float f24,
	float f31, float f32, float f33, float f34,
	float f41, float f42, float f43, float f44)
{
	_11 = f11; _12 = f12; _13 = f13; _14 = f14;
	_21 = f21; _22 = f22; _23 = f23; _24 = f24;
	_31 = f31; _32 = f32; _33 = f33; _34 = f34;
	_41 = f41; _42 = f42; _43 = f43; _44 = f44;
}

float& Matrix::operator() (unsigned int row, unsigned int col)
{
	return m[row][col];
}

float Matrix::operator() (unsigned int row, unsigned int col) const
{
	return m[row][col];
}

Matrix::operator float* ()
{
	return (float*)&_11;
}

/// <summary>
/// Cast a matrix to a const float pointer
/// </summary>
Matrix::operator const float* () const
{
	return (const float*)&_11;
}

/// <summary>
/// Multiply the current matrix with another matrix and replace it's values
/// </summary>
/// <param name="mat">The matrix to multiply with</param>
Matrix& Matrix::operator*= (const Matrix& mat) //documenteren  operators aan elkaar vast aub
{
	//MatrixMultiply(this, this, &mat);
	Matrix* resultMatrix = new Matrix();
	for (int row = 0; row < 4; row++) { //endline accolades niet
		for (int column = 0; column < 4; column++) {
			resultMatrix->m[row][column] = 0;

			for (int n = 0; n < 4; n++) {
				resultMatrix->m[row][column] +=
					m[row][n] * mat.m[n][column];
			}
		}
	}
	return *resultMatrix; // TODO test this out
}

/// <summary>
/// Add the matrix to another matrix and replace it's values
/// </summary>
/// <param name="mat">The matrix to add with</param>
Matrix& Matrix::operator+= (const Matrix& mat)
{
	_11 += mat._11; _12 += mat._12; _13 += mat._13; _14 += mat._14;
	_21 += mat._21; _22 += mat._22; _23 += mat._23; _24 += mat._24;
	_31 += mat._31; _32 += mat._32; _33 += mat._33; _34 += mat._34;
	_41 += mat._41; _42 += mat._42; _43 += mat._43; _44 += mat._44;
	return *this;
}

Matrix& Matrix::operator-= (const Matrix& mat)
{
	_11 -= mat._11; _12 -= mat._12; _13 -= mat._13; _14 -= mat._14;
	_21 -= mat._21; _22 -= mat._22; _23 -= mat._23; _24 -= mat._24;
	_31 -= mat._31; _32 -= mat._32; _33 -= mat._33; _34 -= mat._34;
	_41 -= mat._41; _42 -= mat._42; _43 -= mat._43; _44 -= mat._44;
	return *this;
}

Matrix& Matrix::operator*= (float f)
{
	_11 *= f; _12 *= f; _13 *= f; _14 *= f;
	_21 *= f; _22 *= f; _23 *= f; _24 *= f;
	_31 *= f; _32 *= f; _33 *= f; _34 *= f;
	_41 *= f; _42 *= f; _43 *= f; _44 *= f;
	return *this;

}

Matrix& Matrix::operator/= (float f)
{
	float inv = 1.0f / f;
	_11 *= inv; _12 *= inv; _13 *= inv; _14 *= inv;
	_21 *= inv; _22 *= inv; _23 *= inv; _24 *= inv;
	_31 *= inv; _32 *= inv; _33 *= inv; _34 *= inv;
	_41 *= inv; _42 *= inv; _43 *= inv; _44 *= inv;
	return *this;
}

Matrix Matrix::operator+ () const
{
	return *this;
}

Matrix Matrix::operator- () const
{
	return Matrix(-_11, -_12, -_13, -_14,
		-_21, -_22, -_23, -_24,
		-_31, -_32, -_33, -_34,
		-_41, -_42, -_43, -_44);
}

Matrix Matrix::operator* (const Matrix& mat) const
{
	Matrix* buf = new Matrix();
	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; column++) {
			buf->m[row][column] = 0;

			for (int n = 0; n < 4; n++) {
				buf->m[row][column] +=
					m[row][n] * mat.m[n][column];
			}
		}
	}
	//MatrixMultiply(&buf, this, &mat);
	return *buf;
}

Matrix Matrix::operator+ (const Matrix& mat) const
{
	return Matrix(_11 + mat._11, _12 + mat._12, _13 + mat._13, _14 + mat._14,
		_21 + mat._21, _22 + mat._22, _23 + mat._23, _24 + mat._24,
		_31 + mat._31, _32 + mat._32, _33 + mat._33, _34 + mat._34,
		_41 + mat._41, _42 + mat._42, _43 + mat._43, _44 + mat._44);
}

Matrix Matrix::operator- (const Matrix& mat) const
{
	return Matrix(_11 - mat._11, _12 - mat._12, _13 - mat._13, _14 - mat._14,
		_21 - mat._21, _22 - mat._22, _23 - mat._23, _24 - mat._24,
		_31 - mat._31, _32 - mat._32, _33 - mat._33, _34 - mat._34,
		_41 - mat._41, _42 - mat._42, _43 - mat._43, _44 - mat._44);
}

Matrix Matrix::operator* (float f) const
{
	return Matrix(_11 * f, _12 * f, _13 * f, _14 * f,
		_21 * f, _22 * f, _23 * f, _24 * f,
		_31 * f, _32 * f, _33 * f, _34 * f,
		_41 * f, _42 * f, _43 * f, _44 * f);
}

Matrix Matrix::operator/ (float f) const
{
	float inv = 1.0f / f;
	return Matrix(_11 * inv, _12 * inv, _13 * inv, _14 * inv,
		_21 * inv, _22 * inv, _23 * inv, _24 * inv,
		_31 * inv, _32 * inv, _33 * inv, _34 * inv,
		_41 * inv, _42 * inv, _43 * inv, _44 * inv);
}

Matrix operator* (float f, const Matrix& mat)
{
	return Matrix(f * mat._11, f * mat._12, f * mat._13, f * mat._14,
		f * mat._21, f * mat._22, f * mat._23, f * mat._24,
		f * mat._31, f * mat._32, f * mat._33, f * mat._34,
		f * mat._41, f * mat._42, f * mat._43, f * mat._44);

}

bool Matrix::operator== (const Matrix& mat) const
{
	return (memcmp(this, &mat, sizeof(Matrix)) == 0);
}

bool Matrix::operator!= (const Matrix& mat) const
{
	return (memcmp(this, &mat, sizeof(Matrix)) != 0);
}

void Matrix::LookAtLH(const Vector3* eye, const Vector3* at, const Vector3* pup)
{
	Vector3 right, rightn, up, upn, vec, vec2;

	vec2.Subtract(at, eye);
	vec.Normalize(&vec2);
	right.Cross(pup, &vec);

	up.Cross(&vec, &right);
	rightn.Normalize(&right);
	upn.Normalize(&up);

	m[0][0] = rightn._x;
	m[1][0] = rightn._y;
	m[2][0] = rightn._z;
	m[3][0] = -rightn.Dot(eye);
	m[0][1] = upn._x;
	m[1][1] = upn._y;
	m[2][1] = upn._z;
	m[3][1] = -upn.Dot(eye);
	m[0][2] = vec._x;
	m[1][2] = vec._y;
	m[2][2] = vec._z;
	m[3][2] = -vec.Dot(eye);
	m[0][3] = 0.0f;
	m[1][3] = 0.0f;
	m[2][3] = 0.0f;
	m[3][3] = 1.0f;
}

void Matrix::PerspectiveFovLH(float fovy, float aspect, float zn, float zf)
{
	Identity();
	m[0][0] = 1.0f / (aspect * tan(fovy / 2.0f));
	m[1][1] = 1.0f / tan(fovy / 2.0f);
	m[2][2] = zf / (zf - zn);
	m[2][3] = 1.0f;
	m[3][2] = (zf * zn) / (zn - zf);
	m[3][3] = 0.0f;
}

void Matrix::Identity()
{
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;
	m[1][0] = 0.0f;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;
	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][3] = 0.0f;
	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[0][0] = 1.0f;
	m[1][1] = 1.0f;
	m[2][2] = 1.0f;
	m[3][3] = 1.0f;
}

void Matrix::Scale(float x, float y, float z)
{
	Identity();
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
}

void Matrix::Translate(float x, float y, float z)
{
	Identity();
	m[3][0] = x;
	m[3][1] = y;
	m[3][2] = z;
}

void Matrix::RotateX(float angle)
{
	Identity();
	m[1][1] = cos(angle);
	m[2][2] = cos(angle);
	m[1][2] = sin(angle);
	m[2][1] = -sin(angle);
}

void Matrix::RotateY(float angle)
{
	Identity();
	m[0][0] = cos(angle);
	m[2][2] = cos(angle);
	m[0][2] = -sin(angle);
	m[2][0] = sin(angle);
}

