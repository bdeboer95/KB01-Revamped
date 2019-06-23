/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

Title : CTriangleStripPlane.cpp
Author : Chad Vernon
URL : http://www.c-unit.com

Description : Generates vertices and indices to create an indexed triangle strip plane

Created :  12/04/2005
Modified : 12/04/2005

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN		    
#define DIRECTINPUT_VERSION 0x0800

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
#include <d3dx9.h>
#include <dinput.h>

#include <ctime>
#include <fstream>
#include "resource.h"

// Useful macros
#define SAFE_RELEASE(x) if( x ) { (x)->Release(); (x) = NULL; }
#define SAFE_DELETE(x) if( x ) { delete(x); (x) = NULL; }
#define SAFE_DELETE_ARRAY(x) if( x ) { delete [] (x); (x) = NULL; }
#define SHOWERROR(s,f,l) char buf[1024]; sprintf( buf, "File: %s\nLine: %d\n%s",f,l,s); MessageBox( 0, buf, "Error", 0 );
#include "CTriangleStripPlane.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Generates vertices with a position, normal, and texture coordinates to create an indexed 
triangle strip plane.
Parameters: 
[in/out] ppVertices - Pointer to an array to be filled up.
[in] verticesAlongWidth - Number of vertices along the width
[in] verticesAlongLength - Number of vertices along the length
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CTriangleStripPlane::GeneratePositionNormalTextured( cuCustomVertex::PositionNormalTextured** ppVertices, int verticesAlongWidth, int verticesAlongLength )
{
    SAFE_DELETE_ARRAY( *ppVertices );
    *ppVertices = new cuCustomVertex::PositionNormalTextured[verticesAlongLength * verticesAlongWidth];
    for ( int z = 0; z < verticesAlongLength; z++ )
    {
        for ( int x = 0; x < verticesAlongWidth; x++ )
        {
            float halfWidth = ((float)verticesAlongWidth - 1.0f) / 2.0f;
            float halfLength = ((float)verticesAlongLength - 1.0f) / 2.0f;
            (*ppVertices)[z * verticesAlongLength + x] = cuCustomVertex::PositionNormalTextured(
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
void CTriangleStripPlane::GeneratePositionTexturedWithHeight( cuCustomVertex::PositionTextured** ppVertices, int verticesAlongWidth, int verticesAlongLength, UCHAR* pHeight )
{
    SAFE_DELETE_ARRAY( *ppVertices );
    *ppVertices = new cuCustomVertex::PositionTextured[verticesAlongLength * verticesAlongWidth];
    for ( int z = 0; z < verticesAlongLength; z++ )
    {
        for ( int x = 0; x < verticesAlongWidth; x++ )
        {
            float halfWidth = ((float)verticesAlongWidth - 1.0f) / 2.0f;
            float halfLength = ((float)verticesAlongLength - 1.0f) / 2.0f;
            (*ppVertices)[z * verticesAlongLength + x] = cuCustomVertex::PositionTextured(
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
int CTriangleStripPlane::GenerateIndices( int** ppIndices, int verticesAlongWidth, int verticesAlongLength )
{
    int numIndices = (verticesAlongWidth * 2) * (verticesAlongLength - 1) + (verticesAlongLength - 2);

    SAFE_DELETE_ARRAY( *ppIndices );
    *ppIndices = new int[numIndices];

    int index = 0;
    for ( int z = 0; z < verticesAlongLength - 1; z++ )
    {
        // Even rows move left to right, odd rows move right to left.
        if ( z % 2 == 0 )
        {
            // Even row
            int x;
            for ( x = 0; x < verticesAlongWidth; x++ )
            {
                (*ppIndices)[index++] = x + (z * verticesAlongWidth);
                (*ppIndices)[index++] = x + (z * verticesAlongWidth) + verticesAlongWidth;
            }
            // Insert degenerate vertex if this isn't the last row
            if ( z != verticesAlongLength - 2)
            {
                (*ppIndices)[index++] = --x + (z * verticesAlongWidth);
            }
        } 
        else
        {
            // Odd row
            int x;
            for ( x = verticesAlongWidth - 1; x >= 0; x-- )
            {
                (*ppIndices)[index++] = x + (z * verticesAlongWidth);
                (*ppIndices)[index++] = x + (z * verticesAlongWidth) + verticesAlongWidth;
            }
            // Insert degenerate vertex if this isn't the last row
            if ( z != verticesAlongLength - 2)
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
int CTriangleStripPlane::GenerateIndices( USHORT** ppIndices, int verticesAlongWidth, int verticesAlongLength )
{
    int numIndices = (verticesAlongWidth * 2) * (verticesAlongLength - 1) + (verticesAlongLength - 2);

    SAFE_DELETE_ARRAY( *ppIndices );
    *ppIndices = new USHORT[numIndices];

    int index = 0;
    for ( int z = 0; z < verticesAlongLength - 1; z++ )
    {
        // Even rows move left to right, odd rows move right to left.
        if ( z % 2 == 0 )
        {
            // Even row
            int x;
            for ( x = 0; x < verticesAlongWidth; x++ )
            {
                (*ppIndices)[index++] = (USHORT)(x + (z * verticesAlongWidth));
                (*ppIndices)[index++] = (USHORT)(x + (z * verticesAlongWidth) + verticesAlongWidth);
            }
            // Insert degenerate vertex if this isn't the last row
            if ( z != verticesAlongLength - 2)
            {
                (*ppIndices)[index++] = (USHORT)(--x + (z * verticesAlongWidth));
            }
        } 
        else
        {
            // Odd row
            int x;
            for ( x = verticesAlongWidth - 1; x >= 0; x-- )
            {
                (*ppIndices)[index++] = (USHORT)(x + (z * verticesAlongWidth));
                (*ppIndices)[index++] = (USHORT)(x + (z * verticesAlongWidth) + verticesAlongWidth);
            }
            // Insert degenerate vertex if this isn't the last row
            if ( z != verticesAlongLength - 2)
            {
                (*ppIndices)[index++] = (USHORT)(++x + (z * verticesAlongWidth));
            }
        }
    } 
    return numIndices;
}