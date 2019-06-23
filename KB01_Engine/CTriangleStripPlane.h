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

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// DirectX Header Files
#include <d3d9.h>
#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\d3dx9.h"
#include <dinput.h>

#include <ctime>
#include <fstream>
#include "resource.h"

// Useful macros
#define SAFE_RELEASE(x) if( x ) { (x)->Release(); (x) = NULL; }
#define SAFE_DELETE(x) if( x ) { delete(x); (x) = NULL; }
#define SAFE_DELETE_ARRAY(x) if( x ) { delete [] (x); (x) = NULL; }
#define SHOWERROR(s,f,l) char buf[1024]; sprintf( buf, "File: %s\nLine: %d\n%s",f,l,s); MessageBox( 0, buf, "Error", 0 );
#include "CustomVertex.h"

class CTriangleStripPlane
{
public:
    static void GeneratePositionNormalTextured( cuCustomVertex::PositionNormalTextured** ppVertices, int verticesAlongWidth, int verticesAlongLength );
    static void GeneratePositionTexturedWithHeight( cuCustomVertex::PositionTextured** ppVertices, int verticesAlongWidth, int verticesAlongLength, UCHAR* pHeight );
    static int GenerateIndices( int** ppIndices, int verticesAlongWidth, int verticesAlongLength );
    static int GenerateIndices( USHORT** ppIndices, int verticesAlongWidth, int verticesAlongLength );
};

#endif