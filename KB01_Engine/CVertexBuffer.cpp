/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

Title : CVertexBuffer.cpp
Author : Chad Vernon
URL : http://www.c-unit.com

Description : Vertex buffer wrapper

Created :  08/11/2005
Modified : 12/01/2005

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "stdafx.h"
#include "CVertexBuffer.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Default Constructor
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
CVertexBuffer::CVertexBuffer()
{
    m_pVB         = NULL; 
    m_pIB         = NULL; 
    m_numVertices = 0; 
    m_FVF         = 0; 
    m_vertexSize  = 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Creates the vertex buffer.
Parameters:
[in] pDevice - Pointer to IDirect3DDevice9
[in] numVertices - Max number of vertices allowed in the buffer
[in] FVF - Flexible Vertex Format
[in] vertexSize - Size of the vertex structure
[in] dynamic - TRUE for dynamic buffer, FALSE for static buffer
Returns: TRUE on success, FALSE on failure
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
BOOL CVertexBuffer::CreateBuffer(Renderer* renderer, UINT numVertices, DWORD FVF, UINT vertexSize, BOOL dynamic )
{
    Release();
    m_numVertices = numVertices;
    m_FVF = FVF;
    m_vertexSize = vertexSize;

    // Dynamic buffers can't be in D3DPOOL_MANAGED
    D3DPOOL pool = dynamic ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED;
    DWORD usage = dynamic ? D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC : D3DUSAGE_WRITEONLY;
    if ( FAILED(renderer->CreateVertexBuffer( m_numVertices * m_vertexSize, usage, m_FVF, pool, &m_pVB, NULL ) ) )
    {
        //SHOWERROR( "CreateVertexBuffer failed.", __FILE__, __LINE__ );
        return FALSE;
    }

    return TRUE;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Cleans up resources
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CVertexBuffer::Release()
{
    SAFE_RELEASE( m_pVB );
    m_numVertices = 0;
    m_FVF = 0;
    m_vertexSize = 0;
    // IndexBuffer is released in CIndexBuffer
    m_pIB = NULL;

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Fill up the vertex buffer
Parameters:
[in] numVertices - Number of vertices being put in the buffer.
[in] pVertices - Pointer to the vertex data
[in] flags - Lock flags
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
BOOL CVertexBuffer::SetData( UINT numVertices, void *pVertices, DWORD flags )
{
    if ( m_pVB == NULL )
    {
        return FALSE;
    }

    char *pData;
    // Lock the vertex buffer
    if ( FAILED( m_pVB->Lock( 0, 0, (void**)&pData, flags ) ) )
    {
        //SHOWERROR( "IDirect3DVertexBuffer9::Lock failed.", __FILE__, __LINE__ );
        return FALSE;
    }

    // Copy vertices to vertex buffer
    memcpy( pData, pVertices, numVertices * m_vertexSize );
    
    // Unlock vertex buffer
    if ( FAILED( m_pVB->Unlock() ) )
    {
        //SHOWERROR( "IDirect3DVertexBuffer9::Unlock failed.", __FILE__, __LINE__ );
        return FALSE;
    }

    return TRUE;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Assigns an index buffer to the vertex buffer.
Parameters:
[in] pIB - Pointer to CIndexBuffer
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CVertexBuffer::SetIndexBuffer( CIndexBuffer* pIB )
{
    m_pIB = pIB;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Purpose: Render the buffer
Parameters:
[in] pDevice - Pointer to IDirect3DDevice9
[in] numPrimitives - Number of primitives being rendered
[in] primitiveType - D3DPRIMITIVETYPE
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CVertexBuffer::Render(Renderer* renderer, UINT numPrimitives, unsigned int primitiveType )
{
	LPDIRECT3DDEVICE9 pDevice;

    if ( renderer == NULL )
    {
        return;
    }

    renderer->SetStreamSource( 0, m_pVB, 0, m_vertexSize );
    renderer->SetFVF( m_FVF );

    if ( m_pIB )
    {
        renderer->SetIndexBuffer( m_pIB->GetBuffer() );
        renderer->DrawIndexedPrimitive( primitiveType, 0, 0, m_numVertices, 0, numPrimitives );
    }
    else
    {
        renderer->SetIndexBuffer( NULL );
        renderer->DrawPrimitive( primitiveType, 0, numPrimitives );
    }
}