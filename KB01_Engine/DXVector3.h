#ifndef __DXVECTOR3_H__
#define __DXVECTOR3_H__

#include "d3dx9.h"

struct DXVector3
{
public:
	FLOAT x;
	FLOAT y;
	FLOAT z;

	DXVector3() : x(0), y(0), z(0) { }
	DXVector3(FLOAT _x, FLOAT _y, FLOAT _z) : x(_x), y(_y), z(_z) { }

	//bool operator!=(D3DXVECTOR3 const other);
	D3DXVECTOR3& operator=(DXVector3 other);
	static D3DXVECTOR3 ToDX(DXVector3 * const &other);
};

#endif