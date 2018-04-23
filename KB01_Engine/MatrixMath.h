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
	static inline  Matrix* MatrixIdentity(Matrix* out);
	static Matrix* __stdcall Scale(Matrix * out, float x, float y, float z); //Used to scale an object containing a matrix with an x, y and z value

	static Matrix* __stdcall Translate(Matrix * out, float x, float y, float z);  //Used to translate an object containing a matrix with specified x, y and z values
	static Matrix* __stdcall RotateX(Matrix *out, float angle); //Used to rotate an object containing a matrix on the x-axis
	static Matrix* __stdcall RotateY(Matrix *out, float angle); //Used to rotate an object containing a matrix on the y-axis

};


#endif

