/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

Title : CVertexBuffer.h
Author : Chad Vernon
URL : http://www.c-unit.com

Description : Vertex buffer wrapper

Created :  08/11/2005
Modified : 12/01/2005

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma warning(disable:4996)
#ifndef CVERTEXBUFFER_H
#define CVERTEXBUFFER_H
// Useful macros
#define SAFE_RELEASE(x) if( x ) { (x)->Release(); (x) = NULL; }
#define SAFE_DELETE(x) if( x ) { delete(x); (x) = NULL; }
#define SAFE_DELETE_ARRAY(x) if( x ) { delete [] (x); (x) = NULL; }
#define SHOWERROR(s,f,l) char buf[1024]; sprintf( buf, "File: %s\nLine: %d\n%s",f,l,s); MessageBox( 0, buf, "Error", 0 );
#include "stdafx.h"
#include "CIndexBuffer.h"
#include "Renderer.h"

class CVertexBuffer
{
public:
    CVertexBuffer();
    ~CVertexBuffer() { Release(); }

    BOOL CreateBuffer(Renderer* renderer, UINT numVertices, DWORD FVF, UINT vertexSize, 
        BOOL dynamic = FALSE );
    void Release();
    BOOL SetData( UINT numVertices, void *pVertices, DWORD flags = D3DLOCK_DISCARD );
    void SetIndexBuffer( CIndexBuffer* pIB );
    void Render(Renderer* renderer, UINT numPrimitives, unsigned int primitiveType );

private:
    LPDIRECT3DVERTEXBUFFER9 m_pVB;
    CIndexBuffer*           m_pIB;
    UINT                    m_numVertices;
    UINT                    m_vertexSize;
    DWORD                   m_FVF;
};

#endif