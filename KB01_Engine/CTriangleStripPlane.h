/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

Title : CGraphics.h
Author : Chad Vernon
URL : http://www.c-unit.com

Description : DirectX Graphics wrapper

Created :  08/26/2005
Modified : 12/01/2005

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CTRIANGLESTRIPPLANE_H
#define CTRIANGLESTRIPPLANE_H

#include "CustomVertex.h"

class CTriangleStripPlane
{
public:
    static void GeneratePositionNormalTextured(CustomVertex::PositionNormalTextured** ppVertices, int verticesAlongWidth, int verticesAlongLength );
    static void GeneratePositionTexturedWithHeight(CustomVertex::PositionTextured** ppVertices, int verticesAlongWidth, int verticesAlongLength, unsigned char* pHeight );
    static int GenerateIndices( int** ppIndices, int verticesAlongWidth, int verticesAlongLength );
    static int GenerateIndices( unsigned short** ppIndices, int verticesAlongWidth, int verticesAlongLength );
};

#endif