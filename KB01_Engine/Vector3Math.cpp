#include "Vector3Math.h"
#include <math.h>


Vector3Math::Vector3Math()
{
}


Vector3Math::~Vector3Math()
{
}

Vector3* Vector3Math::Vec3Subtract(Vector3* out, const Vector3* v1, const Vector3* v2)
{
	if (!out || !v1 || !v2) return NULL;
	out->_x = v1->_x - v2->_x;
	out->_y = v1->_y - v2->_y;
	out->_z = v1->_z - v2->_z;
	return out;
}

Vector3* Vector3Math::Vec3Cross(Vector3* out, const Vector3* v1, const Vector3* v2)
{
	Vector3 v;

	if (!out || !v1 || !v2) return NULL;

	v._x = v1->_y * v2->_z - v1->_z * v2->_y;
	v._y = v1->_z * v2->_x - v1->_x * v2->_z;
	v._z = v1->_x * v2->_y - v1->_y * v2->_x;

	*out = v;
	return out;
}

Vector3* Vector3Math::Vec3Normalize(Vector3* out, const Vector3* v)
{
	float norm;

	norm = Vec3Length(v);
	if (!norm)
	{
		out->_x = 0.0f;
		out->_y = 0.0f;
		out->_z = 0.0f;
	}
	else
	{
		out->_x = v->_x / norm;
		out->_y = v->_y / norm;
		out->_z = v->_z / norm;
	}
	return out;
}

float Vector3Math::Vec3Length(const Vector3* v)
{
	if (!v) return 0.0f;
	return sqrt((v->_x) * (v->_x) + (v->_y) * (v->_y) + (v->_z) * (v->_z));
}

float Vector3Math::Vec3Dot(const Vector3* v1, const Vector3* v2)
{
	if (!v1 || !v2) return 0.0f;
	return v1->_x * v2->_x + v1->_y * v2->_y + v1->_z * v2->_z;

}
