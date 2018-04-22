#ifndef __VECTOR3_H__
#define __VECTOR3_H__

class Vector3
{
public:
	float _x, _y, _z;

	Vector3 ();
	Vector3 (const Vector3& v);
	Vector3 (const float* f);
	Vector3 (float x, float y, float z);

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

	static inline Vector3* Vec3Subtract(Vector3* out, const Vector3* v1, const Vector3* v2);
	static inline Vector3* Vec3Cross(Vector3* out, const Vector3* v1, const Vector3* v2);
	static inline Vector3* Vec3Normalize(Vector3* out, const Vector3* v);
	static inline float Vec3Length(const Vector3* v);
	static inline float Vec3Dot(const Vector3* v1, const Vector3* v2);

};
#endif 
