#include "TriangleStripGenerator.h"
#include "CustomVertex.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Generates vertices with a position, normal, and texture coordinates to create an indexed
triangle strip plane.
Parameters:
[in/out] ppVertices - Pointer to an array to be filled up.
[in] verticesAlongWidth - Number of vertices along the width
[in] verticesAlongLength - Number of vertices along the length
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void TriangleStripGenerator::GeneratePositionNormalTextured(CustomVertex::PositionNormalTextured** ppVertices, int verticesAlongWidth, int verticesAlongLength)
{
	//safe delete the array, prior to initialization
	if (*ppVertices) {
		delete[](*ppVertices);
		*ppVertices = nullptr;
	}

	*ppVertices = new CustomVertex::PositionNormalTextured[verticesAlongLength * verticesAlongWidth];
	for (int z = 0; z < verticesAlongLength; z++)
	{
		for (int x = 0; x < verticesAlongWidth; x++)
		{
			float halfWidth = ((float)verticesAlongWidth - 1.0f) / 2.0f;
			float halfLength = ((float)verticesAlongLength - 1.0f) / 2.0f;
			(*ppVertices)[z * verticesAlongLength + x] = CustomVertex::PositionNormalTextured(
				(float)x - halfWidth, 0.0f, (float)z - halfLength,
				0.0f, 1.0f, 0.0f,
				(float)x / (verticesAlongWidth - 1), (float)z / (verticesAlongLength - 1)
			);
		}
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Generates vertices with a position, normal, and texture coordinates to create an indexed
triangle strip plane.
Parameters:
[in/out] ppVertices - Pointer to an array to be filled up.
[in] verticesAlongWidth - Number of vertices along the width
[in] verticesAlongLength - Number of vertices along the length
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void TriangleStripGenerator::GeneratePositionTexturedWithHeight(CustomVertex::PositionTextured** ppVertices, int verticesAlongWidth, int verticesAlongLength, unsigned char* pHeight)
{
	//safe delete the array
	if (*ppVertices) {
		delete[](*ppVertices);
		*ppVertices = nullptr;
	}
	*ppVertices = new CustomVertex::PositionTextured[verticesAlongLength * verticesAlongWidth];
	for (int z = 0; z < verticesAlongLength; z++)
	{
		for (int x = 0; x < verticesAlongWidth; x++)
		{
			float halfWidth = ((float)verticesAlongWidth - 1.0f) / 2.0f;
			float halfLength = ((float)verticesAlongLength - 1.0f) / 2.0f;
			(*ppVertices)[z * verticesAlongLength + x] = CustomVertex::PositionTextured(
				(float)x - halfWidth,
				(float)pHeight[z * verticesAlongLength + x],
				(float)z - halfLength,
				(float)x / (verticesAlongWidth - 1), (float)z / (verticesAlongLength - 1)
			);
		}
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Generates 32-bit indices for an indexed triangle strip plane.
Parameters:
[in/out] ppIndices - Array to be filled up.
[in] verticesAlongWidth - Number of vertices along the width
[in] verticesAlongLength - Number of vertices along the length
Returns: The number of indices
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int TriangleStripGenerator::GenerateIndices(int** ppIndices, int verticesAlongWidth, int verticesAlongLength)
{
	int numIndices = (verticesAlongWidth * 2) * (verticesAlongLength - 1) + (verticesAlongLength - 2);

	//safe delete the array
	if (*ppIndices) {
		delete[](*ppIndices);
		*ppIndices = nullptr;
	}

	*ppIndices = new int[numIndices];

	int index = 0;
	for (int z = 0; z < verticesAlongLength - 1; z++)
	{
		// Even rows move left to right, odd rows move right to left.
		if (z % 2 == 0)
		{
			// Even row
			int x;
			for (x = 0; x < verticesAlongWidth; x++)
			{
				(*ppIndices)[index++] = x + (z * verticesAlongWidth);
				(*ppIndices)[index++] = x + (z * verticesAlongWidth) + verticesAlongWidth;
			}
			// Insert degenerate vertex if this isn't the last row
			if (z != verticesAlongLength - 2)
			{
				(*ppIndices)[index++] = --x + (z * verticesAlongWidth);
			}
		}
		else
		{
			// Odd row
			int x;
			for (x = verticesAlongWidth - 1; x >= 0; x--)
			{
				(*ppIndices)[index++] = x + (z * verticesAlongWidth);
				(*ppIndices)[index++] = x + (z * verticesAlongWidth) + verticesAlongWidth;
			}
			// Insert degenerate vertex if this isn't the last row
			if (z != verticesAlongLength - 2)
			{
				(*ppIndices)[index++] = ++x + (z * verticesAlongWidth);
			}
		}
	}
	return numIndices;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Generates 16-bit indices for an indexed triangle strip plane.
Parameters:
[in/out] pIndices - Array to be filled up.
[in] verticesAlongWidth - Number of vertices along the width
[in] verticesAlongLength - Number of vertices along the length
Returns: The number of indices
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int TriangleStripGenerator::GenerateIndices(unsigned short** ppIndices, int verticesAlongWidth, int verticesAlongLength)
{
	int numIndices = (verticesAlongWidth * 2) * (verticesAlongLength - 1) + (verticesAlongLength - 2);

	//safe delete the array
	if (*ppIndices) {
		delete[](*ppIndices);
		*ppIndices = nullptr;
	}
	*ppIndices = new unsigned short[numIndices];

	int index = 0;
	for (int z = 0; z < verticesAlongLength - 1; z++)
	{
		// Even rows move left to right, odd rows move right to left.
		if (z % 2 == 0)
		{
			// Even row
			int x;
			for (x = 0; x < verticesAlongWidth; x++)
			{
				(*ppIndices)[index++] = (unsigned short)(x + (z * verticesAlongWidth));
				(*ppIndices)[index++] = (unsigned short)(x + (z * verticesAlongWidth) + verticesAlongWidth);
			}
			// Insert degenerate vertex if this isn't the last row
			if (z != verticesAlongLength - 2)
			{
				(*ppIndices)[index++] = (unsigned short)(--x + (z * verticesAlongWidth));
			}
		}
		else
		{
			// Odd row
			int x;
			for (x = verticesAlongWidth - 1; x >= 0; x--)
			{
				(*ppIndices)[index++] = (unsigned short)(x + (z * verticesAlongWidth));
				(*ppIndices)[index++] = (unsigned short)(x + (z * verticesAlongWidth) + verticesAlongWidth);
			}
			// Insert degenerate vertex if this isn't the last row
			if (z != verticesAlongLength - 2)
			{
				(*ppIndices)[index++] = (unsigned short)(++x + (z * verticesAlongWidth));
			}
		}
	}
	return numIndices;
}