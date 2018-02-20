#ifndef __VECTOR3_H__
#define __VECTOR3_H__

struct Vector3
{
	FLOAT x; 
	FLOAT y; 
	FLOAT z;

	Vector3() : x(0), y(0), z(0) { }
	Vector3(FLOAT _x, FLOAT _y, FLOAT _z) : x(_x), y(_y), z(_z) { }

	operator D3DXVECTOR3() { return &D3DXVECTOR3(x, y, z); }
};

#endif