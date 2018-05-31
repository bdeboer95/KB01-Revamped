#include "Terrain.h"
#include "Log.h"
#include "Renderer.h"
#include "CTriangleStripPlane.h"
#include "CUtility.h"
#include "CustomVertex.h"

Terrain::Terrain(char* rawFile, char* terrainTexture)
{
	_height = NULL;
	_texture = NULL;
	_numVertices = _numIndices = 0;

	_positionX = -100;
	_positionY = -400;
	_positionZ = 500;

	_rotationY = 0;
	_rotationX = 0;

	_speed = 0.1f;

	SetupMatrices();
}

Terrain::~Terrain()
{

}

/// <summary>
/// Renders the terrain.
/// </summary>
/// <param name="renderer">The renderer used to draw the terrain on the backbuffer.</param>
void Terrain::Render(Renderer* renderer)
{
	renderer->SetTransform(renderer->WORLD, &_matWorld);
	renderer->SetTexture(_texture, 0);																	  
	renderer->SetStreamSource(0, 0, _vertexSize);
	renderer->SetFVF();
	renderer->SetIndices();
	renderer->DrawIndexedPrimitive(Renderer::TRIANGLESTRIP, 0, 0, _numVertices, 0, _numIndices - 2);
}

void Terrain::SetupMatrices()
{
	_matTranslate.Translate(_positionX, _positionY, _positionZ);

	_matRotateX.RotateX(_rotationX);
	_matRotateY.RotateY(_rotationY);

	_matScale.Scale(10, 2, 10);

	_matWorld = _matScale * _matTranslate * _matRotateY * _matRotateX;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Create a new Terrain object.
Parameters:
[in] pDevice - D3D Device
[in] rawFile - Name of the height map file
[in] terrainTexture - Texture file name
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool Terrain::InitGeometry(Renderer* renderer, ResourceManager* resourceManager)
{

	renderer->Release();
	// Load height map
	char path[MAX_PATH] = { 0 };

	std::ifstream heightStream;
	//Open the file with the height data with this specific name and path --> this needs to go to the resource manager TODO
	heightStream.open(L"..\\Assets\\Heightmaps\\heightMap.raw", std::ios::binary);
	if (heightStream.fail())
	{
		Log::Instance()->LogMessage("Terrain - Heightmap file could not be found.", Log::MESSAGE_WARNING);

		return false;
	}
	// Get number of vertices
	heightStream.seekg(0, std::ios::end); //use seekg to move the position of the next character to be extracted to the last character
	_numVertices = heightStream.tellg();  //read the file and returns the position of this last character
	heightStream.seekg(0, std::ios::beg); //returns the position to the beginning of the file

										  // Allocate memory and read the data
	_height = new unsigned char[_numVertices];
	heightStream.read((char *)_height, _numVertices);
	heightStream.close();

	// Generate vertices
	unsigned int width = (int)sqrt((float)_numVertices);
	cuCustomVertex::PositionTextured* pVertices = NULL;
	CTriangleStripPlane::GeneratePositionTexturedWithHeight(&pVertices, width, width, _height);
	_vertexSize = sizeof(cuCustomVertex::PositionTextured);
	renderer->CreateVertexBuffer(_numVertices, sizeof(cuCustomVertex::PositionTextured), D3DFVF_XYZ | D3DFVF_TEX1, NULL); //move this to the renderer TODO define somewhere
	renderer->FillVertexBuffer(_numVertices, pVertices, 0);

	// Generate indices
	int* pIndices = NULL;
	_numIndices = CTriangleStripPlane::GenerateIndices(&pIndices, width, width); //generate how many indices are needed for the trianglestrip
	renderer->CreateIndexBuffer(_numIndices, D3DFMT_INDEX32, NULL); //put this is in an enum : 
	renderer->FillIndexBuffer(_numIndices, pIndices, 0);//move this to the renderer TODO
														//_vertexBuffer.SetIndexBuffer(&_indexBuffer);//move this to the renderer TODO

	CUtility::GetMediaFile("terrain.jpg", "..\\Assets\\Textures\\Terrain\\");

	if (FAILED(renderer->CreateTextureFromFile(L"..\\assets\\textures\\terrain\\terrainorange.jpg", &_texture)))
	{
		Log::Instance()->LogMessage("Terrain - unable to load terrain textures.", Log::MESSAGE_WARNING);
		return false;
	}

	return true;
}

void Terrain::Notify(TRANSFORMATIONEVENT transformationEvent, float x, float y) {

	if (transformationEvent == TRANSFORMATIONEVENT::MOVE_RIGHT)
	{
		//_positionX = _positionX + _speed;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::MOVE_LEFT)
	{
		//_positionX = _positionX - _speed;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::MOVE_BACKWARDS)
	{
		//_positionZ = _positionZ - _speed;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::MOVE_FORWARD)
	{
		//_positionZ = _positionZ + _speed;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::ROTATE_LEFT)
	{
		_rotationY = _rotationY + y;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::ROTATE_DOWN)
	{

	}

	SetupMatrices();
}


