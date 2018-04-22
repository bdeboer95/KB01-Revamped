#ifndef __VECTOR2_H__
#define __VECTOR2_H__

class Vector2
{
public:
	 Vector2() {};
	 Vector2(const float *);
	/* Vector2(const D3DXfloat16 *);*/
	 Vector2(float x, float y);

	// casting
	operator float* ();
	operator const float* () const;

	// assignment operators
	 Vector2& operator += (const  Vector2&);
	 Vector2& operator -= (const  Vector2&);
	 Vector2& operator *= (float);
	 Vector2& operator /= (float);

	// unary operators
	 Vector2 operator + () const;
	 Vector2 operator - () const;

	// binary operators
	 Vector2 operator + (const  Vector2&) const;
	 Vector2 operator - (const  Vector2&) const;
	 Vector2 operator * (float) const;
	 Vector2 operator / (float) const;

	friend  Vector2 operator * (float, const  Vector2&);

	bool operator == (const  Vector2&) const;
	bool operator != (const  Vector2&) const;


public:
	float x, y;
};

#endif