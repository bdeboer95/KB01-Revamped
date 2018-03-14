#include "DXVector3.h"

//bool DXVector3::operator!=(const D3DXVECTOR3 other) 
//{
//	return (x != other.x && y != other.y && z != other.z) ? 1 : 0;
//}

D3DXVECTOR3& DXVector3::operator=(DXVector3 other)
{
	return D3DXVECTOR3(other.x, other.y, other.z);
}

D3DXVECTOR3 DXVector3::ToDX(DXVector3 * const &other)
{
	return D3DXVECTOR3(other->x, other->y, other->z);
}