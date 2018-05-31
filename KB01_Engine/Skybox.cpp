#include "Skybox.h"
#include <dinput.h>
#include "Vertex.h"

Skybox::Skybox(Skybox_Cube skyboxCube)
{
	_skyboxCube = skyboxCube;

	_positionX = 0;
	_positionY = 0;
	_positionZ = 3;

	_speed = 1.0f;
	_mesh = new MeshDx("");

	SetupMatrices();
}

Skybox::~Skybox()
{

}

void Skybox::LoadTextures(ResourceManager* resourceManager)
{
	std::string filePath = "..\\Assets\\Textures\\Skyboxes\\";
	_textures[0] = resourceManager->LoadTexture(filePath, _skyboxCube._front);
	_textures[1] = resourceManager->LoadTexture(filePath, _skyboxCube._back);
	_textures[2] = resourceManager->LoadTexture(filePath, _skyboxCube._left);
	_textures[3] = resourceManager->LoadTexture(filePath, _skyboxCube._right);
	_textures[4] = resourceManager->LoadTexture(filePath, _skyboxCube._top);
	_textures[5] = resourceManager->LoadTexture(filePath, _skyboxCube._bottom);
}

void Skybox::Render(Renderer* renderer)
{
	//Disables the zbuffer for writing
	renderer->SetTransform(Renderer::WORLD, &_matWorld);
	renderer->SetRenderState(Renderer::ZENABLE, false);
	renderer->SetRenderState(Renderer::CULLMODE, Renderer::CULL_NONE);

	//Loops through every square side of the cube
	for (int i = 0; i < 6; i++)
	{
		renderer->SetTexture(_textures[i]->GetTextures(), 0); //this is what gives a side of the skybox it's texture
		renderer->DrawSubset(_mesh->GetMesh(), i); // draws 
	}

	renderer->SetRenderState(Renderer::CULLMODE, Renderer::CULL_CCW); //dit ook in renderer

																	  //Enables the zbuffer for writing
	renderer->SetRenderState(Renderer::ZENABLE, true);
}

void Skybox::SetupMatrices()
{
	_matTranslate.Translate(_positionX, _positionY, _positionZ);

	_matRotateX.RotateX(_rotationX);
	_matRotateY.RotateY(_rotationY);

	_matScale.Scale(1000, 1000, 1000);

	_matWorld = _matScale * _matTranslate * _matRotateY * _matRotateX;
}


bool Skybox::InitGeometry(Renderer* renderer, ResourceManager* resourceManager)
{
	if (FAILED(renderer->CreateMeshFVF(12, 24, Renderer::MESH_MANAGED, FVF_VERTEX, _mesh))) //
	{
		return false;
	}

	Vertex* v = 0;
	_mesh->LockVertexBuffer(0, (void**)&v);

	//				 | x |  | y |  | z | | nx || ny || nz || tu || tv |
	v[0] = Vertex(1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);	//
	v[1] = Vertex(1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);		//
	v[2] = Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);	// FRONT
	v[3] = Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);	//

	v[4] = Vertex(1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);		//
	v[5] = Vertex(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f); 		//
	v[6] = Vertex(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);		// BACK
	v[7] = Vertex(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);	//

	v[8] = Vertex(-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);	//
	v[9] = Vertex(-1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);  	//
	v[10] = Vertex(-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);	// LEFT
	v[11] = Vertex(-1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);	//

	v[12] = Vertex(1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);	//
	v[13] = Vertex(1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);	//
	v[14] = Vertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);		// RIGHT
	v[15] = Vertex(1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);	//

	v[16] = Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);	//
	v[17] = Vertex(-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);	//
	v[18] = Vertex(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);		// TOP
	v[19] = Vertex(1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);	//

	v[20] = Vertex(-1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);	//
	v[21] = Vertex(-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f); //	
	v[22] = Vertex(1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);	// BOTTOM
	v[23] = Vertex(1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);	//

	_mesh->UnlockVertexBuffer();

	WORD* i = 0;
	_mesh->LockIndexBuffer(0, (void**)&i);

	i[0] = 0;  i[1] = 1;    i[2] = 2;	//
	i[3] = 0;  i[4] = 2;    i[5] = 3;	// FRONT

	i[6] = 4;  i[7] = 5;   i[8] = 6;	//
	i[9] = 4;  i[10] = 6;   i[11] = 7; 	// BACK

	i[12] = 8;  i[13] = 9;   i[14] = 10;//
	i[15] = 8;  i[16] = 10;  i[17] = 11;// LEFT

	i[18] = 12; i[19] = 13;  i[20] = 14;//
	i[21] = 12; i[22] = 14;  i[23] = 15;// RIGHT

	i[24] = 16; i[25] = 17;  i[26] = 18;//
	i[27] = 16; i[28] = 18;  i[29] = 19;// TOP

	i[30] = 20; i[31] = 21;  i[32] = 22;//
	i[33] = 20; i[34] = 22;  i[35] = 23;// BOTTOM

	_mesh->UnlockIndexBuffer();


	DWORD* attributeBuffer = 0;
	_mesh->LockAttributeBuffer(0, &attributeBuffer);

	for (int a = 0; a < 2; a++)     //--triangles 1-4   
	{
		attributeBuffer[a] = 0;    //--subset 0   
	}
	for (int b = 2; b < 4; b++)     //--triangles 5-8   
	{
		attributeBuffer[b] = 1;    //--subset 1   
	}
	for (int c = 4; c < 6; c++)     //--triangles 9-12   
	{
		attributeBuffer[c] = 2;    //--subset 2   
	}
	for (int d = 6; d < 8; d++)     //--triangles 1-4   
	{
		attributeBuffer[d] = 3;    //--subset 0   
	}
	for (int e = 8; e < 10; e++)     //--triangles 5-8   
	{
		attributeBuffer[e] = 4;    //--subset 1   
	}
	for (int f = 10; f < 12; f++)     //--triangles 9-12   
	{
		attributeBuffer[f] = 5;    //--subset 2   
	}

	_mesh->UnlockAttributeBuffer();

	LoadTextures(resourceManager);

	return true;
}

/// <summary>
/// Notifies the specified state.
/// </summary>
/// <param name="state">The array with the current state of the devices.</param>
void Skybox::Notify(TRANSFORMATIONEVENT transformationEvent, float x, float y)
{

	if (transformationEvent == TRANSFORMATIONEVENT::MOVE_RIGHT)
	{
		_positionX = _positionX + _speed;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::MOVE_LEFT)
	{
		_positionX = _positionX - _speed;
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
		_rotationY = _rotationY + y;
	}
	if (transformationEvent == TRANSFORMATIONEVENT::ROTATE_DOWN)
	{

	}

	SetupMatrices();
}

std::wstring Skybox::StrToWStr(std::string str)  //TODO remove
{
	int length;
	int string_length = static_cast<int>(str.length() + 1);

	length = MultiByteToWideChar(CP_ACP, 0, str.c_str(), string_length, 0, 0);
	wchar_t* wide_char = new wchar_t[length];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), string_length, wide_char, length);
	std::wstring wstr(wide_char);
	delete[] wide_char;

	return wstr;
}

