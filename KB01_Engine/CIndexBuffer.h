/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

Title : CVertexBuffer.h
Author : Chad Vernon
URL : http://www.c-unit.com

Description : Index buffer wrapper

Created :  08/11/2005
Modified : 12/01/2005

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef CINDEXBUFFER_H
#define CINDEXBUFFER_H

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

class CIndexBuffer
{
public:
    CIndexBuffer();
    ~CIndexBuffer() { Release(); }

    BOOL CreateBuffer( LPDIRECT3DDEVICE9 pDevice, UINT numIndices, D3DFORMAT format, BOOL dynamic = FALSE );
    void Release();
    BOOL SetData( UINT numIndices, void *pIndices, DWORD flags = D3DLOCK_DISCARD );
    LPDIRECT3DINDEXBUFFER9 GetBuffer() { return m_pIB; }
    UINT GetNumIndices() { return m_numIndices; }
    
private:
    LPDIRECT3DINDEXBUFFER9  m_pIB;
    UINT                    m_numIndices;
};

#endif