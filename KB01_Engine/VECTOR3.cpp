#include "Vector3.h"
#include <math.h>

Vector3::Vector3()
{
	_x = 0;
	_y = 0;
	_z = 0;
}

Vector3::Vector3(const Vector3& v)
{
	if (!v) return;

	_x = v._x;
	_y = v._y;
	_z = v._z;
}

Vector3::Vector3(const float* f)
{
	if (!f) return;

	_x = f[0];
	_y = f[1];
	_z = f[2];
}

Vector3::Vector3(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

void Vector3::Subtract(const Vector3* v1, const Vector3* v2)
{
	if (!v1 || !v2) return;

	_x = v1->_x - v2->_x;
	_y = v1->_y - v2->_y;
	_z = v1->_z - v2->_z;
}

void Vector3::Cross(const Vector3* v1, const Vector3* v2)
{
	if (!v1 || !v2) return;

	_x = v1->_y * v2->_z - v1->_z * v2->_y;
	_y = v1->_z * v2->_x - v1->_x * v2->_z;
	_z = v1->_x * v2->_y - v1->_y * v2->_x;
}

void Vector3::Normalize(const Vector3* v)
{
	if (!v) return;

	float norm = Length(v);

	if (!norm)
	{
		_x = 0.0f;
		_y = 0.0f;
		_z = 0.0f;
	}
	else
	{
		_x = v->_x / norm;
		_y = v->_y / norm;
		_z = v->_z / norm;
	}
}

float Vector3::Length(const Vector3* v)
{
	if (!v) return 0.0f;

	return sqrt((v->_x) * (v->_x) + (v->_y) * (v->_y) + (v->_z) * (v->_z));
}

float Vector3::Dot(const Vector3* v)
{
	if (!v) return 0.0f;

	return _x * v->_x + _y * v->_y + _z * v->_z;

}

