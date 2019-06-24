#include "Terrain.h"
#include "Log.h"
#include "Renderer.h"
#include "ResourceManager.h"

/// <summary>
/// Initializes a new terrain object
/// </summary>
/// <param name="heightmapName">the name of the file that contains the heightmap</param>
Terrain::Terrain(std::string heightmapName)
{
	_height = NULL;
	_numVertices = _numIndices = 0;
	_positionX = 0;
	_positionY = -600;
	_positionZ = 500;
	_rotationY = 0;
	_rotationX = 0;
	_speed = 2.0f;
	Translate(&_matTranslate, _positionX, _positionY, _positionZ);
	Scale(&_matScale, 10, 1, 10);
	RotateY(&_matRotateY, _rotationY);
	RotateX(&_matRotateX, _rotationX);
	_matWorld = _matScale * _matTranslate*_matRotateY*_matRotateX;
}

/// <summary>
/// Finalizes the terrain object and cleans all variables up
/// </summary>
Terrain::~Terrain()
{
	CleanUp();
}


/// <summary>
///  This function gets called every time an input device has been used
/// </summary>
/// <param name="transformationEvent"> the type of event that has been called</param>
/// <param name="x">the change in the x-axis</param>
/// <param name="y">the change in the y-axis</param>
void Terrain::Notify(TRANSFORMATIONEVENT transformationEvent, float x, float y) 
{

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
	}
	if (transformationEvent == TRANSFORMATIONEVENT::ROTATE_DOWN)
	{

		_rotationX = _rotationX - 1;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::ROTATE_UP)
	{

		_rotationX = _rotationX + 1;
	}


	Translate(&_matTranslate, _positionX, _positionY, _positionZ);
	RotateX(&_matRotateX, _rotationX);
	RotateY(&_matRotateY, _rotationY);

	_matWorld = _matScale * _matTranslate  * _matRotateX * _matRotateY;
}

/// <summary>
/// Create a new Terrain object.
/// </summary>
/// <param name="renderer">The renderer that needs to draw the terrain</param>
/// <param name="rawFile">Name of the height map file</param>
/// <param name="terrainTexture">- Texture file name</param>
/// <returns></returns>
bool Terrain::Initialize(Renderer* renderer, char* rawFile, char* terrainTexture)
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
	CustomVertex::PositionTextured* pVertices = NULL;
	TriangleStripGenerator::GeneratePositionTexturedWithHeight(&pVertices, width, width, _height);
	_vertexSize = sizeof(CustomVertex::PositionTextured);
	renderer->CreateVertexBuffer(_numVertices, sizeof(CustomVertex::PositionTextured), 0x002 | 0x100, NULL); //move this to the renderer TODO define somewhere
	renderer->FillVertexBuffer(_numVertices, pVertices, 0);

	// Generate indices
	int* pIndices = NULL;
	_numIndices = TriangleStripGenerator::GenerateIndices(&pIndices, width, width); //generate how many indices are needed for the trianglestrip
	renderer->CreateIndexBuffer(_numIndices, D3DFMT_INDEX32, NULL); //put this is in an enum : 
	renderer->FillIndexBuffer(_numIndices, pIndices, 0);
	Log::Instance()->LogMessage("Terrain - initialized successfully.", Log::MESSAGE_INFO);
	return true;
}

/// <summary>
/// Load the texture that will be used for the terrain from the resourcemanager
/// </summary>
/// <param name="resourceManager">the manager that will load the texture</param>
/// <param name="textureName">the name of the texture that needs to be loaded</param>
void Terrain::LoadTexture(ResourceManager* resourceManager, std::string textureName)
{
	std::string filePath = "..\\Assets\\Textures\\Terrain\\"; //the directory containing the texture file for the terrain
	_textureContainer = resourceManager->LoadTexture(filePath, textureName);
}

/// <summary>
/// Renders the terrain every second
/// </summary>
/// <param name="renderer">The renderer used to draw the terrain on the backbuffer.</param>
void Terrain::Render(Renderer* renderer)
{
	renderer->SetTransform(renderer->WORLD, &_matWorld); //set the transform position in the world
	renderer->SetTexture(_textureContainer->GetTexture(), 0); // set the texture that need to be drawn on screen
	renderer->SetStreamSource(0, 0, _vertexSize); 
	renderer->SetFVF();
	renderer->SetIndices();
	renderer->DrawIndexedPrimitive(Renderer::TRIANGLESTRIP, 0, 0, _numVertices, 0, _numIndices - 2); //draw the triangles for the terrain
}

/// <summary>
/// Deletes all pointers that can cause memory leaks
/// </summary>
void Terrain::CleanUp() {
	delete _textureContainer;
}


