#include "Vector3.h"


Vector3::Vector3()
{
	_x = 0;
	_y = 0;
	_z = 0;
}

Vector3::Vector3(const Vector3& v)
{
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

