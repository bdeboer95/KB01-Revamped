#ifndef _VECTOR3MATH_H__
#define __VECTOR3MATH_H__
#include "Vector3.h"
class Vector3Math
{
public:
	Vector3Math();
	~Vector3Math();
	  Vector3* Vec3Subtract(Vector3* out, const Vector3* v1, const Vector3* v2);
	  Vector3* Vec3Cross(Vector3* out, const Vector3* v1, const Vector3* v2);
	  Vector3* Vec3Normalize(Vector3* out, const Vector3* v);
	  float Vec3Length(const Vector3* v);
	  float Vec3Dot(const Vector3* v1, const Vector3* v2);

};

#endif
