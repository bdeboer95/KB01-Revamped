#include "Terrain.h"
#include "Log.h"
#include "MatrixMath.h"
#include "Renderer.h"

Terrain::Terrain()
{
    _height = NULL;
    _texture = NULL;

    _numVertices = _numIndices = 0;

	_positionX = -100;
	_positionY = -400;
	_positionZ = 500;
	_speed = 0.1f;

	MatrixMath* matrix = new MatrixMath();

	matrix->Translation(&_matTranslate, _positionX, _positionY, _positionZ);
	matrix->Scaling(&_matScale, 10, 2, 10);
	_matWorld = _matScale * *_matTranslate;
}

Terrain::~Terrain()
{
	Release();
}

void Terrain::Notify(TRANSFORMATIONEVENT transformationEvent, float x, float y) {

	if (transformationEvent == TRANSFORMATIONEVENT::MOVE_RIGHT)
	{
		_positionX = _positionX - _speed;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::MOVE_LEFT)
	{
		_positionX = _positionX + _speed;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::MOVE_BACKWARDS)
	{
		_positionZ = _positionZ - _speed;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::MOVE_FORWARD)
	{
		_positionZ = _positionZ + _speed;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::ROTATE_LEFT)
	{
		_rotationY = _rotationY - y;
		//rotationX = rotationX + x;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::ROTATE_DOWN)
	{

	}

	MatrixMath* matrix = new MatrixMath();

	matrix->Translation(&_matTranslate, _positionX, _positionY, _positionZ);
	matrix->RotationX(&_matRotateX, _rotationX);
	matrix->RotationY(&_matRotateY, _rotationY);

	_matWorld = _matScale * _matTranslate  * _matRotateX * _matRotateY; 
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
Summary: Create a new Terrain object.
Parameters:
[in] pDevice - D3D Device
[in] rawFile - Name of the height map file
[in] terrainTexture - Texture file name
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool Terrain::Initialize(Renderer* renderer, char* rawFile, char* terrainTexture )
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
    _numVertices = heightStream.tellg();  //read the file and returns the position of this last character
    heightStream.seekg( 0, std::ios::beg ); //returns the position to the beginning of the file

    // Allocate memory and read the data
    _height = new unsigned char[_numVertices];
    heightStream.read( (char *)_height, _numVertices );
    heightStream.close();

    // Generate vertices
    unsigned int width = (int)sqrt( (float)_numVertices );
    cuCustomVertex::PositionTextured* pVertices = NULL;  
    CTriangleStripPlane::GeneratePositionTexturedWithHeight( &pVertices, width, width, _height );
    _vertexBuffer = renderer->CreateBuffer( renderer, _numVertices, D3DFVF_XYZ | D3DFVF_TEX1, sizeof( cuCustomVertex::PositionTextured ) ); //move this to the renderer TODO define somewhere
	_vertexBuffer.SetData(_numVertices, pVertices, 0 );//move this to the renderer TODO

    // Generate indices
    int* pIndices = NULL;
    _numIndices = CTriangleStripPlane::GenerateIndices( &pIndices, width, width ); //generate how many indices are needed for the trianglestrip
    _indexBuffer = renderer->CreateBuffer( renderer, _numIndices, D3DFMT_INDEX32 ); //put this is in an enum : TODO //move this to the renderer TODO
	_indexBuffer.SetData(_numIndices, pIndices, 0 );//move this to the renderer TODO
	_vertexBuffer.SetIndexBuffer(&_indexBuffer);//move this to the renderer TODO
    
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
void Terrain::Render(Renderer* renderer )
{
	renderer->SetTransform(renderer->WORLD, &matWorld);
	renderer->SetTexture( 0, m_pTexture); // to renderer todo
	_vertexBuffer.Render(renderer, m_numIndices - 2, renderer->TRIANGLESTRIP ); // renderer->GetVertexBuffer.Render( renderer->GetDevice, m_numIndices - 2, D3DPT_TRIANGLESTRIP ); change for this
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
Summary: Release resources
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void Terrain::Release()
{
    SAFE_DELETE_ARRAY( m_pHeight );
    SAFE_RELEASE( m_pTexture );
	_vertexBuffer.Release();
	_indexBuffer.Release();
}