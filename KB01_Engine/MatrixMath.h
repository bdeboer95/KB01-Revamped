#ifndef _MATRIXMATH_H__
#define __MATRIXMATH_H__

#include "Matrix.h"

class MatrixMath
{
public:
	MatrixMath(); //Constructor
	~MatrixMath(); //Destructor
	Matrix* LookAtLH(Matrix* out, const Vector3* eye, const Vector3* at, const Vector3* pup); //Builds a left-handed look-at matrix
	Matrix* PerspectiveFovLH(Matrix* out, float fovy, float aspect, float zn, float zf); //Builds a left-handed perspective projection matrix based on a field of view
	Matrix* Translation(Matrix* out, float x, float y, float z);
	Matrix* RotationX(Matrix* out, float angle);
	Matrix* RotationY(Matrix* out, float angle);
	Matrix* RotationZ(Matrix* out, float angle);
	Matrix* Scaling(Matrix* out, float x, float y, float);

	static inline  Matrix* MatrixIdentity(Matrix* out);

};


#endif

