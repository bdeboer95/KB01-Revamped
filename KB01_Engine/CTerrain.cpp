/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

Title : CTerrain.cpp
Author : Chad Vernon
URL : http://www.c-unit.com

Description : Terrain class

Created :  08/11/2005
Modified : 12/05/2005

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "stdafx.h"
#include "CTerrain.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
Summary: Default constructor.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
CTerrain::CTerrain()
{
    m_pHeight = NULL;
    m_pTexture = NULL;
    m_numVertices = m_numIndices = 0;
	positionX = -100;
	positionY = -300;
	positionZ = 50;
	speed = 0.1f;
	/*Matrix modifyMatrix= new Matrix()
	matTranslate +=*/
	D3DXMatrixTranslation((D3DXMATRIX*)&matTranslate, positionX, positionY, positionZ);
	D3DXMatrixScaling((D3DXMATRIX*)&matScale, // Pointer to recieve computed matrix
		10, // x=axis scale
		2, // y-axis scale
		2 // z-axis scale
	);
	matWorld = matScale * matTranslate ;

}
void CTerrain::Notify(TRANSFORMATIONEVENT transformationEvent, float x, float y) {

	if (transformationEvent == TRANSFORMATIONEVENT::MOVE_RIGHT)
	{
		positionX = positionX - speed;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::MOVE_LEFT)
	{
		positionX = positionX + speed;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::MOVE_BACKWARDS)
	{
		positionZ = positionZ - speed;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::MOVE_FORWARD)
	{
		positionZ = positionZ + speed;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::ROTATE_LEFT)
	{
		rotationY = rotationY - y;
		//rotationX = rotationX + x;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::ROTATE_DOWN)
	{

	}
	D3DXMatrixTranslation((D3DXMATRIX*)&matTranslate, positionX, positionY, positionZ);
	D3DXMatrixRotationX((D3DXMATRIX*)&matRotateX, rotationX);
	D3DXMatrixRotationY((D3DXMATRIX*)&matRotateY, rotationY);
	matWorld = matScale * matTranslate  * matRotateX* matRotateY;
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
Summary: Create a new Terrain object.
Parameters:
[in] pDevice - D3D Device
[in] rawFile - Name of the height map file
[in] terrainTexture - Texture file name
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
BOOL CTerrain::Initialize( LPDIRECT3DDEVICE9 pDevice, char *rawFile, char *terrainTexture )
{
    Release();
    
    // Load height map
    char path[MAX_PATH] = {0};
   
    std::ifstream heightStream;
	//Open the file with the height data with this specific name
	heightStream.open(L"..\\Assets\\Heightmaps\\heightMap.raw", std::ios::binary);
	if (heightStream.fail())
	{
		return false;
	}
    //{
    //   // SHOWERROR( "Could not open height file.", __FILE__, __LINE__ );
    //    return FALSE;
    //}

    // Get number of vertices
    heightStream.seekg( 0, std::ios::end );
    m_numVertices = heightStream.tellg();
    heightStream.seekg( 0, std::ios::beg );

    // Allocate memory and read the data
    m_pHeight = new UCHAR[m_numVertices];
    heightStream.read( (char *)m_pHeight, m_numVertices );
    heightStream.close();

    // Generate vertices
    UINT width = (int)sqrt( (float)m_numVertices );
    cuCustomVertex::PositionTextured* pVertices = NULL; 
    CTriangleStripPlane::GeneratePositionTexturedWithHeight( &pVertices, width, width, m_pHeight );
    m_vb.CreateBuffer( pDevice, m_numVertices, D3DFVF_XYZ | D3DFVF_TEX1, sizeof( cuCustomVertex::PositionTextured ) );
    m_vb.SetData( m_numVertices, pVertices, 0 );

    // Generate indices
    int* pIndices = NULL;
    m_numIndices = CTriangleStripPlane::GenerateIndices( &pIndices, width, width );
    m_ib.CreateBuffer( pDevice, m_numIndices, D3DFMT_INDEX32 );
    m_ib.SetData( m_numIndices, pIndices, 0 );
    m_vb.SetIndexBuffer( &m_ib );
    
    CUtility::GetMediaFile( "terrain.jpg", "..\\Assets\\Textures\\Terrain\\");
	wchar_t wtext[20];
	mbstowcs(wtext, path, strlen(path) + 1);//Plus null
	LPWSTR ptr = wtext;
    if ( FAILED( D3DXCreateTextureFromFile( pDevice, L"..\\Assets\\Textures\\Terrain\\terrain.jpg", &m_pTexture ) ) )
    {
       // SHOWERROR( "Unable to load terrain textures.", __FILE__, __LINE__ );
        return FALSE;

    }
    return TRUE;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
Summary: Renders the terrain.
Parameters:
[in] pDevice - D3D Device
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CTerrain::Render( LPDIRECT3DDEVICE9 pDevice )
{
    pDevice->SetTransform( D3DTS_WORLD, &matWorld);
    pDevice->SetTexture( 0, m_pTexture );
    m_vb.Render( pDevice, m_numIndices - 2, D3DPT_TRIANGLESTRIP );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
Summary: Release resources
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CTerrain::Release()
{
    SAFE_DELETE_ARRAY( m_pHeight );
    SAFE_RELEASE( m_pTexture );
    m_vb.Release();
    m_ib.Release();
}