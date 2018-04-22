#ifndef _MATRIXMATH_H__
#define __MATRIXMATH_H__

#include "Matrix.h"

class MatrixMath
{
public:
	MatrixMath(); //Constructor
	~MatrixMath(); //Destructor
	Matrix* MatrixLookAtLH(Matrix* out, const Vector3* eye, const Vector3* at, const Vector3* pup); //Builds a left-handed look-at matrix
	Matrix* MatrixPerspectiveFovLH(Matrix* out, float fovy, float aspect, float zn, float zf); //Builds a left-handed perspective projection matrix based on a field of view
	static inline  Matrix* MatrixIdentity(Matrix* out); //The identity matrix is used as the starting point for matrices that will modify vertex values to create rotations, translations, and any other transformations that can be represented by a 4x4 matrix.

};


#endif

