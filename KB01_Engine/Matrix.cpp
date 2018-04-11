#include "Matrix.h"



inline Matrix::Matrix()
{
}

//inline Matrix::Matrix(const float *pf)
//{
//	if (!pf) return;
//	memcpy(&_11, pf, sizeof(Matrix));
//}
//
//inline Matrix::Matrix(const D3DMATRIX& mat)
//{
//	memcpy(&_11, &mat, sizeof(Matrix));
//}

inline Matrix::Matrix(float f11, float f12, float f13, float f14,
	float f21, float f22, float f23, float f24,
	float f31, float f32, float f33, float f34,
	float f41, float f42, float f43, float f44)
{
	_11 = f11; _12 = f12; _13 = f13; _14 = f14;
	_21 = f21; _22 = f22; _23 = f23; _24 = f24;
	_31 = f31; _32 = f32; _33 = f33; _34 = f34;
	_41 = f41; _42 = f42; _43 = f43; _44 = f44;
}

inline float& Matrix::operator () (unsigned int row, unsigned int col)
{
	return m[row][col];
}

inline float Matrix::operator () (unsigned int row, unsigned int col) const
{
	return m[row][col];
}

inline Matrix::operator float* ()
{
	return (float*)&_11;
}

inline Matrix::operator const float* () const
{
	return (const float*)&_11;
}

inline Matrix* Matrix::operator *= (Matrix* mat)
{
	//MatrixMultiply(this, this, &mat);
	Matrix* resultMatrix = new Matrix();
	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; column++) {
			resultMatrix->m[row][column] = 0;

			for (int n = 0; n < 4; n++) {
				resultMatrix->m[row][column] +=
					m[row][n] * mat->m[n][column];
			}
		}
	}
	return resultMatrix;
}

inline Matrix& Matrix::operator += (const Matrix& mat)
{
	_11 += mat._11; _12 += mat._12; _13 += mat._13; _14 += mat._14;
	_21 += mat._21; _22 += mat._22; _23 += mat._23; _24 += mat._24;
	_31 += mat._31; _32 += mat._32; _33 += mat._33; _34 += mat._34;
	_41 += mat._41; _42 += mat._42; _43 += mat._43; _44 += mat._44;
	return *this;
}

inline Matrix& Matrix::operator -= (const Matrix& mat)
{
	_11 -= mat._11; _12 -= mat._12; _13 -= mat._13; _14 -= mat._14;
	_21 -= mat._21; _22 -= mat._22; _23 -= mat._23; _24 -= mat._24;
	_31 -= mat._31; _32 -= mat._32; _33 -= mat._33; _34 -= mat._34;
	_41 -= mat._41; _42 -= mat._42; _43 -= mat._43; _44 -= mat._44;
	return *this;
}

inline Matrix& Matrix::operator *= (float f)
{
	_11 *= f; _12 *= f; _13 *= f; _14 *= f;
	_21 *= f; _22 *= f; _23 *= f; _24 *= f;
	_31 *= f; _32 *= f; _33 *= f; _34 *= f;
	_41 *= f; _42 *= f; _43 *= f; _44 *= f;
	return *this;

}

+inline Matrix& Matrix::operator /= (float f)
{
	float inv = 1.0f / f;
	_11 *= inv; _12 *= inv; _13 *= inv; _14 *= inv;
	_21 *= inv; _22 *= inv; _23 *= inv; _24 *= inv;
	_31 *= inv; _32 *= inv; _33 *= inv; _34 *= inv;
	_41 *= inv; _42 *= inv; _43 *= inv; _44 *= inv;
	return *this;
}

inline Matrix Matrix::operator + () const
{
	return *this;
}

inline Matrix Matrix::operator - () const
{
	return Matrix(-_11, -_12, -_13, -_14,
		-_21, -_22, -_23, -_24,
		-_31, -_32, -_33, -_34,
		-_41, -_42, -_43, -_44);
}

inline Matrix Matrix::operator * (const Matrix& mat) const
{
	Matrix buf;
	MatrixMultiply(&buf, this, &mat);
	return buf;
}

inline Matrix Matrix::operator + (const Matrix& mat) const
{
	return Matrix(_11 + mat._11, _12 + mat._12, _13 + mat._13, _14 + mat._14,
		_21 + mat._21, _22 + mat._22, _23 + mat._23, _24 + mat._24,
		_31 + mat._31, _32 + mat._32, _33 + mat._33, _34 + mat._34,
		_41 + mat._41, _42 + mat._42, _43 + mat._43, _44 + mat._44);
}

inline Matrix Matrix::operator - (const Matrix& mat) const
{
	return Matrix(_11 - mat._11, _12 - mat._12, _13 - mat._13, _14 - mat._14,
		_21 - mat._21, _22 - mat._22, _23 - mat._23, _24 - mat._24,
		_31 - mat._31, _32 - mat._32, _33 - mat._33, _34 - mat._34,
		_41 - mat._41, _42 - mat._42, _43 - mat._43, _44 - mat._44);
}

inline Matrix Matrix::operator * (float f) const
{
	return Matrix(_11 * f, _12 * f, _13 * f, _14 * f,
		_21 * f, _22 * f, _23 * f, _24 * f,
		_31 * f, _32 * f, _33 * f, _34 * f,
		_41 * f, _42 * f, _43 * f, _44 * f);
}

inline Matrix Matrix::operator / (float f) const
{
	float inv = 1.0f / f;
	return Matrix(_11 * inv, _12 * inv, _13 * inv, _14 * inv,
		_21 * inv, _22 * inv, _23 * inv, _24 * inv,
		_31 * inv, _32 * inv, _33 * inv, _34 * inv,
		_41 * inv, _42 * inv, _43 * inv, _44 * inv);
}

inline Matrix operator * (float f, const Matrix& mat)
{
	return Matrix(f * mat._11, f * mat._12, f * mat._13, f * mat._14,
		f * mat._21, f * mat._22, f * mat._23, f * mat._24,
		f * mat._31, f * mat._32, f * mat._33, f * mat._34,
		f * mat._41, f * mat._42, f * mat._43, f * mat._44);

}

inline BOOL Matrix::operator == (const Matrix& mat) const
{
	return (memcmp(this, &mat, sizeof(Matrix)) == 0);
}

inline BOOL Matrix::operator != (const Matrix& mat) const
{
	return (memcmp(this, &mat, sizeof(Matrix)) != 0);
}
