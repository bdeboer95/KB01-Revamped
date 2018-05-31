#ifndef _MATRIX_H__
#define __MATRIX_H__

//TODO fix this class with comments and logic
//TODO make test classes
class Vector3;
class Matrix
{
public:
	Matrix() {}; //Constructor
	Matrix(const float *); //Overloaded constructor
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;
		};
		float m[4][4]; //this contains the values _11 through _44 
	};
	/*	Matrix(const D3DMATRIX&);*/
		//Matrix(const D3DXfloat16 *);
	Matrix(float _11, float _12, float _13, float _14,
		float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34,
		float _41, float _42, float _43, float _44); //overloaded constructor with all the matrix values individually


	// access grants
	float& operator() (unsigned int  Row, unsigned int  Col);
	float  operator() (unsigned int  Row, unsigned int  Col) const;

	// casting operators
	operator float* (); //cast the current matrix to a float value
	operator const float* () const; //cas the current matrix to a const float value

	// assignment operators
	Matrix& operator*= (const Matrix&);	//multiply current matrix values by another matrix's values and replace current values
	Matrix& operator+= (const Matrix&); //add a new matrix to the current matrix and replace current values
	Matrix& operator-= (const Matrix&);	//subsract another matrix from the current matrix and replace current values
	Matrix& operator*= (float);		//multiply current matrix with a float value and replace current values		 		
	Matrix& operator/= (float);		//divide the current matrix with a float value and replace current values

	// unary operators
	Matrix operator+ () const;		//add matrices together
	Matrix operator- () const;		//substract matrices from each other

	// binary operators
	Matrix operator* (const Matrix&) const;	//multiply matrices with another matrix
	Matrix operator+ (const Matrix&) const; //add matrices to each other
	Matrix operator- (const Matrix&) const; //substract matrices from each other
	Matrix operator* (float) const; //multiply matrices with float values
	Matrix operator/ (float) const; //divide matrices by a vloat value

	friend Matrix operator* (float, const Matrix&); //TODO

	bool operator== (const Matrix&) const; //compare a matrix to another matrix and check if they are the same
	bool operator!= (const Matrix&) const; //compare a matrix to aother matrix and check if they are not the same

	/*static inline Matrix* MatrixLookAtLH(Matrix* out, const Vector3* eye, const Vector3* at, const Vector3* pup);
	static inline Matrix* MatrixPerspectiveFovLH (Matrix* out, float fovy, float aspect, float zn, float zf);*/

};
#endif

