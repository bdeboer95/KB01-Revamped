/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

Title : CVertexBuffer.cpp
Author : Chad Vernon
URL : http://www.c-unit.com

Description : Vertex buffer wrapper

Created :  08/11/2005
Modified : 12/01/2005

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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
#include "CIndexBuffer.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Default Constructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
CIndexBuffer::CIndexBuffer()
{
    m_pIB        = NULL; 
    m_numIndices = 0; 
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Free up resources
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CIndexBuffer::Release()
{
    SAFE_RELEASE( m_pIB );
    m_numIndices = 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Creates an index buffer.
Parameters:
[in] pDevice - Device to create the buffer with
[in] numIndices - Number of indices to put in the index buffer
[in] format - D3DFMT_INDEX32 for 32-bit indices, D3DFMT_INDEX16 for 16-bit indices
[in] dynamic - TRUE for dynamic buffer, FALSE for static buffer
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
BOOL CIndexBuffer::CreateBuffer( LPDIRECT3DDEVICE9 pDevice, UINT numIndices, D3DFORMAT format, BOOL dynamic )
{
    Release();
    m_numIndices = numIndices;

    // Dynamic buffers can't be in D3DPOOL_MANAGED
    D3DPOOL pool = dynamic ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED;
    UINT size = (format == D3DFMT_INDEX32) ? sizeof( UINT ) : sizeof( USHORT );
    DWORD usage = dynamic ? D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC : D3DUSAGE_WRITEONLY;

    if( FAILED( pDevice->CreateIndexBuffer( m_numIndices * size, usage, format, pool, &m_pIB, NULL ) ) )
    {
        //SHOWERROR( "CreateIndexBuffer failed.", __FILE__, __LINE__ );
        return FALSE;
    }
    return TRUE;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Fill up the index buffer
Parameters:
[in] numIndices - Number of indices being put in the buffer.
[in] pIndices - Pointer to the vertex data
[in] dwFlags - Lock flags
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
BOOL CIndexBuffer::SetData( UINT numIndices, void *pIndices, DWORD flags )
{
    if ( m_pIB == NULL )
    {
        return FALSE;
    }

    char *pData;

    D3DINDEXBUFFER_DESC desc;
    m_pIB->GetDesc( &desc );
    UINT size = (desc.Format == D3DFMT_INDEX32) ? sizeof( UINT ) : sizeof( USHORT );

    // Lock the index buffer
    if ( FAILED( m_pIB->Lock( 0, 0, (void**)&pData, flags ) ) )
    {
        return FALSE;
    }

    memcpy( pData, pIndices, numIndices * size );

    // Unlock index buffer
    if ( FAILED( m_pIB->Unlock() ) )
    {
        return FALSE;
    }

    return TRUE;
}