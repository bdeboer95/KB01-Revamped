#ifndef __VECTOR3_H__
#define __VECTOR3_H__

class Vector3
{
private:
	float					_x;									//the x-axis of the vector
	float					_y;									//the y-axis of the vector
	float					_z;									//the z-axis of the vector

public:
							Vector3 ();
							Vector3 (const Vector3& v);
							Vector3 (const float* f);
							Vector3 (float x, float y, float z);
	float					GetX();
	float					GetY();
	float					GetZ();
	void					SetX(float x);
	void					SetY(float y);
	void					SetZ(float z);
	// casting
	operator float* ();
	operator const float* () const;

	// assignment operators
	Vector3& operator+= (const Vector3&);
	Vector3& operator-= (const Vector3&);
	Vector3& operator*= (float);
	Vector3& operator/= (float);

	// unary operators
	Vector3 operator+ () const;
	Vector3 operator- () const;

	// binary operators
	Vector3 operator+ (const Vector3&) const;
	Vector3 operator- (const Vector3&) const;
	Vector3 operator* (float) const;
	Vector3 operator/ (float) const;

	friend Vector3 operator* (float, const Vector3&);

	bool operator== (const Vector3&) const;
	bool operator!= (const Vector3&) const;

	static  Vector3* Vec3Subtract(Vector3* out, const Vector3* v1, const Vector3* v2);
	static  Vector3* Vec3Cross(Vector3* out, const Vector3* v1, const Vector3* v2);
	static  Vector3* Vec3Normalize(Vector3* out, const Vector3* v);
	static  float Vec3Length(const Vector3* v);
	static  float Vec3Dot(const Vector3* v1, const Vector3* v2);

};
#endif 
