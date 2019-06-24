#include "Vector3.h"
#include <math.h>
/// <summary>
/// Constructor that initializes the Vector with all values set to 0
/// </summary>
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
/// <summary>
/// Initializes an instance of Vector3 by individually declaring the the x, y and z-axis 
/// </summary>
/// <param name="x">the x-axis of the vector</param>
/// <param name="y">the y-axis of the vector</param>
/// <param name="z">the z-axis of the vector</param>
Vector3::Vector3(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

/// <summary>
/// Get the value for the y-axis of the vector
/// </summary>
/// <returns> a float containign the y-axis of the vector</returns>
float Vector3::GetY()
{
	return _y;
}

/// <summary>
/// Get the value for the x-axis of the vector
/// </summary>
/// <returns>a float containing the x-axis of the vectoe</returns>
float Vector3::GetX()
{
	return _x;
}

/// <summary>
/// Get the value for the z-axis of the vector
/// </summary>
/// <returns>a float containing the z-axis of the vector</returns>
float Vector3::GetZ()
{
	return _z;
}

/// <summary>
/// Sets the value for the x-axis of the vector
/// </summary>
/// <returns>a float containing the x-axis of the vectoe</returns>
void Vector3::SetX(float x)
{
	_x=x;
}

/// <summary>
/// Sets the value for the z-axis of the vector
/// </summary>
/// <returns>a float containing the z-axis of the vector</returns>
void Vector3::SetZ(float z)
{
	_z = z;

}
/// <summary>
/// Sets the value for the y-axis of the vector
/// </summary>
/// <returns>a float containing the z-axis of the vector</returns>
void Vector3::SetY(float y)
{
	_y = y;

}

Vector3* Vector3::Vec3Subtract(Vector3* out, const Vector3* v1, const Vector3* v2)
{
	if (!out || !v1 || !v2) return nullptr;
	out->SetX(v1->_x - v2->_x);
	out->SetY(v1->_y - v2->_y);
	out->SetZ(v1->_z - v2->_z);
	return out;
}

Vector3* Vector3::Vec3Cross(Vector3* out, const Vector3* v1, const Vector3* v2)
{
	Vector3 v;

	if (!out || !v1 || !v2) return nullptr;

	v._x = v1->_y * v2->_z - v1->_z * v2->_y;
	v._y = v1->_z * v2->_x - v1->_x * v2->_z;
	v._z = v1->_x * v2->_y - v1->_y * v2->_x;

	*out = v;
	return out;
}

Vector3* Vector3::Vec3Normalize(Vector3* out, const Vector3* v)
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
float Vector3::Vec3Length(const Vector3* v)
{
	if (!v) return 0.0f;
	return sqrt((v->_x) * (v->_x) + (v->_y) * (v->_y) + (v->_z) * (v->_z));
}

float Vector3::Vec3Dot(const Vector3* v1, const Vector3* v2)
{
	if (!v1 || !v2) return 0.0f;
	return v1->_x * v2->_x + v1->_y * v2->_y + v1->_z * v2->_z;

}
