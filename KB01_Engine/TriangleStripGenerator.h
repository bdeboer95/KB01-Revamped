#ifndef TRIANGLESTRIPGENERATOR_H
#define TRIANGLESTRIPGENERATOR_H

#include "CustomVertex.h"
class TriangleStripGenerator
{
public:
	static void GeneratePositionNormalTextured(CustomVertex::PositionNormalTextured** ppVertices, int verticesAlongWidth, int verticesAlongLength);
	static void GeneratePositionTexturedWithHeight(CustomVertex::PositionTextured** ppVertices, int verticesAlongWidth, int verticesAlongLength, unsigned char* pHeight);
	static int GenerateIndices(int** ppIndices, int verticesAlongWidth, int verticesAlongLength);
	static int GenerateIndices(unsigned short** ppIndices, int verticesAlongWidth, int verticesAlongLength);
};

#endif
