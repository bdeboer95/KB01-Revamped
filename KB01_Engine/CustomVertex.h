#ifndef CUSTOMVERTEX_H
#define CUSTOMVERTEX_H

class CustomVertex
{
public:
/// <summary>
/// Position
/// </summary>
	typedef struct Position
	{
	public:
		Position() : X(0), Y(0), Z(0) {}
		Position(float x, float y, float z)
			: X(x), Y(y), Z(z) {}
		float X, Y, Z;
	} Position;

/// <summary>
/// Position and color
/// </summary>
	typedef struct PositionColor
	{
	public:
		PositionColor() : X(0), Y(0), Z(0), Color(0) {}
		PositionColor(float x, float y, float z, unsigned long color)
			: X(x), Y(y), Z(z), Color(color) {}
		float X, Y, Z;
		unsigned long Color;
	} PositionColor;

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	Summary: Position and color
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	typedef struct PositionTextured
	{
	public:
		PositionTextured() : X(0), Y(0), Z(0), Tu(0), Tv(0) {}
		PositionTextured(float x, float y, float z, float tu, float tv)
			: X(x), Y(y), Z(z), Tu(tu), Tv(tv) {}
		float X, Y, Z;
		float Tu, Tv;
	} PositionTextured;

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	Summary: Position, color, texture coordinates
	* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	typedef struct PositionColorTextured
	{
	public:
		PositionColorTextured() : X(0), Y(0), Z(0), Color(0), Tu(0), Tv(0) {}
		PositionColorTextured(float x, float y, float z, unsigned long color, float tu, float tv)
			: X(x), Y(y), Z(z), Color(color), Tu(tu), Tv(tv) {}
		float X, Y, Z;
		unsigned long Color;
		float Tu, Tv;
	} PositionColorTextured;

	/// <summary>
	/// Position, color, texture coordinates
	/// </summary>
	typedef struct PositionNormalTextured
	{
	public:
		PositionNormalTextured() : X(0), Y(0), Z(0), Nx(0), Ny(0), Nz(0), Tu(0), Tv(0) {}
		PositionNormalTextured(float x, float y, float z, float nx, float ny, float nz, float tu, float tv)
			: X(x), Y(y), Z(z), Nx(nx), Ny(ny), Nz(nz), Tu(tu), Tv(tv) {}
		float X, Y, Z;
		float Nx, Ny, Nz;
		float Tu, Tv;
	} PositionNormalTextured;

};

#endif