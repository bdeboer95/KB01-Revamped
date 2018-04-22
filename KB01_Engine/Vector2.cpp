#include "Vector2.h"

//inline  Vector2::Vector2()
//{
//}

inline  Vector2::Vector2(const float *pf)
{
	if (!pf) return;
	x = pf[0];
	y = pf[1];
}

inline  Vector2::Vector2(float fx, float fy)
{
	x = fx;
	y = fy;
}

inline  Vector2::operator float* ()
{
	return (float*)&x;
}

inline  Vector2::operator const float* () const
{
	return (const float*)&x;
}

inline  Vector2&  Vector2::operator += (const  Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}
inline  Vector2&  Vector2::operator -= (const  Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}
//x and y coordinates will be both multiplied by a factor f
inline  Vector2&  Vector2::operator *= (float f)
{
	x *= f;
	y *= f;
	return *this;
}
//x and y coordinates will be both divided by a factor f
inline  Vector2&  Vector2::operator /= (float f)
{
	x /= f;
	y /= f;
	return *this;
}

inline  Vector2  Vector2::operator + () const
{
	return *this;
}
inline  Vector2  Vector2::operator - () const
 {
return  Vector2(-x, -y);
	}

inline  Vector2  Vector2::operator + (const  Vector2& v) const
 {
	return  Vector2(x + v.x, y + v.y);
	}

inline  Vector2  Vector2::operator - (const  Vector2& v) const
 {
	return  Vector2(x - v.x, y - v.y);
	}

inline  Vector2  Vector2::operator * (float f) const
 {
	return  Vector2(x * f, y * f);
	}

inline  Vector2  Vector2::operator / (float f) const
 {
	return  Vector2(x / f, y / f);
	}

inline  Vector2 operator * (float f, const  Vector2& v)
 {
	return  Vector2(f * v.x, f * v.y);
	}

inline bool  Vector2::operator == (const  Vector2& v) const
 {
	return x == v.x && y == v.y;
	}

inline bool  Vector2::operator != (const  Vector2& v) const
 {
	return x != v.x || y != v.y;
	}
