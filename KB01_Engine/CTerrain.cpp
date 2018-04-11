/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

Title : CTerrain.cpp
Author : Chad Vernon
URL : http://www.c-unit.com

Description : Terrain class

Created :  08/11/2005
Modified : 12/05/2005

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "CTerrain.h"
#include "Log.h"
#include "Renderer.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
Summary: Default constructor.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
CTerrain::CTerrain()
{
    m_pHeight = NULL;
    m_pTexture = NULL;
    m_numVertices = m_numIndices = 0;
	positionX = -100;
	positionY = -400;
	positionZ = 500;
	speed = 0.1f;
	/*Matrix modifyMatrix= new Matrix()
	matTranslate +=*/
	D3DXMatrixTranslation((D3DXMATRIX*)&matTranslate, positionX, positionY, positionZ);
	D3DXMatrixScaling((D3DXMATRIX*)&matScale, // Pointer to recieve computed matrix
		10, // x=axis scale
		2, // y-axis scalee
		10 // z-axis scale
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
	D3DXMatrixTranslation((D3DXMATRIX*)&matTranslate, positionX, positionY, positionZ); //move this to the matrix class todo
	D3DXMatrixRotationX((D3DXMATRIX*)&matRotateX, rotationX); //move this to the matrix class todo
	D3DXMatrixRotationY((D3DXMATRIX*)&matRotateY, rotationY); //move this to the matrix class todo
	matWorld = matScale * matTranslate  * matRotateX* matRotateY; //move this to the matrix class todo
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
	//Open the file with the height data with this specific name and path --> this needs to go to the resource manager TODO
	heightStream.open(L"..\\Assets\\Heightmaps\\heightMap.raw", std::ios::binary);
	if (heightStream.fail())
	{
		Log::Instance()->LogMessage("Terrain - Heightmap file could not be found.", Log::MESSAGE_WARNING);

		return false;
	}
    // Get number of vertices
    heightStream.seekg( 0, std::ios::end ); //use seekg to move the position of the next character to be extracted to the last character
    m_numVertices = heightStream.tellg();  //read the file and returns the position of this last character
    heightStream.seekg( 0, std::ios::beg ); //returns the position to the beginning of the file

    // Allocate memory and read the data
    m_pHeight = new unsigned char[m_numVertices];
    heightStream.read( (char *)m_pHeight, m_numVertices );
    heightStream.close();

    // Generate vertices
    unsigned int width = (int)sqrt( (float)m_numVertices );
    cuCustomVertex::PositionTextured* pVertices = NULL;  
    CTriangleStripPlane::GeneratePositionTexturedWithHeight( &pVertices, width, width, m_pHeight );
    m_vb.CreateBuffer( pDevice, m_numVertices, D3DFVF_XYZ | D3DFVF_TEX1, sizeof( cuCustomVertex::PositionTextured ) ); //move this to the renderer TODO define somewhere
    m_vb.SetData( m_numVertices, pVertices, 0 );//move this to the renderer TODO

    // Generate indices
    int* pIndices = NULL;
    m_numIndices = CTriangleStripPlane::GenerateIndices( &pIndices, width, width ); //generate how many indices are needed for the trianglestrip
    m_ib.CreateBuffer( pDevice, m_numIndices, D3DFMT_INDEX32 ); //put this is in an enum : TODO //move this to the renderer TODO
    m_ib.SetData( m_numIndices, pIndices, 0 );//move this to the renderer TODO
    m_vb.SetIndexBuffer( &m_ib );//move this to the renderer TODO
    
	CUtility::GetMediaFile("terrain.jpg", "..\\Assets\\Textures\\Terrain\\");
    if ( FAILED( D3DXCreateTextureFromFile( pDevice, L"..\\Assets\\Textures\\Terrain\\terrainorange.jpg", &m_pTexture ) ) ) // to the resourcemanager or fileloader
    {
		Log::Instance()->LogMessage("Terrain - Unable to load terrain textures.", Log::MESSAGE_WARNING);
        return FALSE;

    }
    return TRUE;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
Summary: Renders the terrain.
Parameters:
[in] pDevice - D3D Device
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CTerrain::Render(Renderer* renderer )
{
	renderer->SetTransform(D3DTS_WORLD, &matWorld);
	static_cast<LPDIRECT3DDEVICE9>(renderer->GetDevice())->SetTexture( 0, m_pTexture); // to renderer todo
    m_vb.Render( static_cast<LPDIRECT3DDEVICE9>(renderer->GetDevice()), m_numIndices - 2, D3DPT_TRIANGLESTRIP ); // renderer->GetVertexBuffer.Render( renderer->GetDevice, m_numIndices - 2, D3DPT_TRIANGLESTRIP ); change for this
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