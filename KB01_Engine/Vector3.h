#ifndef __VECTOR3_H__
#define __VECTOR3_H__

class Vector3
{
public:
	Vector3() {};
	Vector3(const float *);
	/*Vector3(const D3DVECTOR&);*/
	//Vector3(const D3DXfloat16 *);
	Vector3(float x, float y, float z);

	// casting
	operator float* ();
	operator const float* () const;

	// assignment operators
	Vector3& operator += (const Vector3&);
	Vector3& operator -= (const Vector3&);
	Vector3& operator *= (float);
	Vector3& operator /= (float);

	// unary operators
	Vector3 operator + () const;
	Vector3 operator - () const;

	// binary operators
	Vector3 operator + (const Vector3&) const;
	Vector3 operator - (const Vector3&) const;
	Vector3 operator * (float) const;
	Vector3 operator / (float) const;

	friend Vector3 operator * (float, const Vector3&);

	bool operator == (const Vector3&) const;
	bool operator != (const Vector3&) const;

};
#endif 
