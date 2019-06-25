#include "Skybox.h"
#include <dinput.h>
#include "Vertex.h"

/// <summary>
/// Initializes a new instance of the <see cref="Skybox"/> class.
/// </summary>
/// <param name="skyboxCube">The skybox cube.</param>
Skybox::Skybox(Skybox_Cube skyboxCube)
{
	_skyboxCube = skyboxCube;
	_positionX = 0;
	_positionY = 0;
	_positionZ = 3;
	_scaleVector = Vector3(1000, 1000, 1000);
	_speed = 1.0f;
	SetUpMatrices();
}

/// <summary>
/// Finalizes an instance of the <see cref="Skybox"/> class.
/// </summary>
Skybox::~Skybox()
{
	delete _matRotateY;
	delete _matRotateX;
	delete _matScale;
	delete _matWorld;
	delete _matTranslate;
}

/// <summary>
/// Set up all the matrices and prepare them for transformation for the world matrix
/// </summary>
void Skybox::SetUpMatrices() {
	Translate(&_matTranslate, _positionX, _positionY, _positionZ);
	Scale(&_matScale, _scaleVector );
	RotateY(&_matRotateY, _rotationY);
	RotateX(&_matRotateX, _rotationX);
	_matWorld = _matScale * _matTranslate * _matRotateY * _matRotateX;
}

/// <summary>
/// Notifies the specified state.
/// </summary>
/// <param name="state">The array with the current state of the devices.</param>
void Skybox::Notify(TRANSFORMATIONEVENT transformationEvent, float x, float y)
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
	
	SetUpMatrices();
}

/// <summary>
/// Initializes the geometry.
/// </summary>
/// <param name="renderer">The renderer.</param>
/// <param name="resourceManager">The resource manager.</param>
/// <returns></returns>
bool Skybox::InitGeometry(Renderer* renderer, ResourceManager* resourceManager)
{
	HRESULT hr = 0;

	//hr = D3DXCreateMeshFVF(12,
	//	24,
	//	D3DXMESH_MANAGED, FVF_VERTEX, static_cast<LPDIRECT3DDEVICE9>(_renderer->GetDevice()), &mesh); //todo remove
	renderer->CreateMeshFVF();
	Vertex* v = 0;
	renderer->LockVertexBuffer(0,(void**)&v);
	//mesh->LockVertexBuffer(0, (void**)&v); //todo remove

	v[0] = Vertex(1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	v[1] = Vertex(1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[2] = Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);  //FRONT
	v[3] = Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

	v[4] = Vertex(1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	v[5] = Vertex(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f); //BACK
	v[6] = Vertex(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	v[7] = Vertex(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);

	v[8] = Vertex(-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	v[9] = Vertex(-1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);  //LEFT
	v[10] = Vertex(-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	v[11] = Vertex(-1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	v[12] = Vertex(1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	v[13] = Vertex(1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);//RIGHT
	v[14] = Vertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	v[15] = Vertex(1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	v[16] = Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	v[17] = Vertex(-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	v[18] = Vertex(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);  //top
	v[19] = Vertex(1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);

	v[20] = Vertex(-1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
	v[21] = Vertex(-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f); //BOTtom	
	v[22] = Vertex(1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
	v[23] = Vertex(1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
	/*mesh->UnlockVertexBuffer();todo remove*/
	renderer->UnlockVertexBuffer();
	unsigned short* i = 0;
	renderer->LockIndexBuffer(0, (void**)&i);
	/*mesh->LockIndexBuffer(0, (void**)&i);*/

	//This is made to set the indices for the squares
	i[0] = 0;  i[1] = 1;    i[2] = 2;
	i[3] = 0;  i[4] = 2;    i[5] = 3; // FRONT

	i[6] = 4;  i[7] = 5;   i[8] = 6;
	i[9] = 4;  i[10] = 6;   i[11] = 7; // BACK

	i[12] = 8;  i[13] = 9;   i[14] = 10;
	i[15] = 8;  i[16] = 10;  i[17] = 11;// LEFT

	i[18] = 12; i[19] = 13;  i[20] = 14;
	i[21] = 12; i[22] = 14;  i[23] = 15;// RIGHT

	i[24] = 16; i[25] = 17;  i[26] = 18;
	i[27] = 16; i[28] = 18;  i[29] = 19;// TOP

	i[30] = 20; i[31] = 21;  i[32] = 22;
	i[33] = 20; i[34] = 22;  i[35] = 23;// BOTTOM
	//mesh->UnlockIndexBuffer();
	renderer->UnlockIndexBuffer();

	unsigned long* attributeBuffer = 0;

	//Locks the mesh buffer that contains the mesh attribute data, and returns a pointer to it.
	//mesh->LockAttributeBuffer(0, &attributeBuffer);
	renderer->LockAttributeBuffer(0, &attributeBuffer);
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
	renderer->UnLockAttributeBuffer();
	//mesh->UnlockAttributeBuffer(); todo remove
	LoadTextures(resourceManager);

	return true;
}

std::wstring Skybox::StrToWStr(std::string str)
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

/// <summary>
/// Loads the textures.
/// </summary>
/// <param name="_resourceManager">The resource manager.</param>
void Skybox::LoadTextures(ResourceManager* _resourceManager)
{
	std::string filePath = "..\\Assets\\Textures\\Skyboxes\\";
	_textures[0] = _resourceManager->LoadTexture(filePath, _skyboxCube.front);
	_textures[1] = _resourceManager->LoadTexture(filePath, _skyboxCube.back);
	_textures[2] = _resourceManager->LoadTexture(filePath, _skyboxCube.left);
	_textures[3] = _resourceManager->LoadTexture(filePath, _skyboxCube.right);
	_textures[4] = _resourceManager->LoadTexture(filePath, _skyboxCube.top);
	_textures[5] = _resourceManager->LoadTexture(filePath, _skyboxCube.bottom);
}

/// <summary>
/// Renders the skybox with the specified renderer.
/// </summary>
/// <param name="_renderer">The renderer.</param>
void Skybox::Render(Renderer* renderer)
{
	//LPDIRECT3DDEVICE9 device = static_cast<LPDIRECT3DDEVICE9>(_renderer->GetDevice());
	//Disables the zbuffer for writing
	//static_cast<LPDIRECT3DDEVICE9>(_renderer->GetDevice())->SetRenderState(D3DRS_ZWRITEENABLE, false);
	renderer->SetTransform(Renderer::WORLD, &_matWorld);
	renderer->SetRenderState(Renderer::RENDERSTATETYPE_ZENABLE, false);
	renderer->SetRenderState(Renderer::RENDERSTATETYPE_CULLMODE, Renderer::CULL_NONE);
	//device->SetRenderState(D3DRS_ZENABLE, false); //todo remove
	//device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //todo remove

	//Loops through every square side of the cube
	for (int i = 0; i < 6; i++)
	{
		renderer->SetTexture(_textures[i]->GetTexture(), 0); //this is what gives a side of the skybox it's texture
		renderer->DrawSubset(NULL, i); // draws the subset
	}

	renderer->SetRenderState(Renderer::RENDERSTATETYPE_CULLMODE, Renderer::CULL_CCW); //dit ook in renderer

	//Enables the zbuffer for writing
	//device->SetRenderState(D3DRS_ZWRITEENABLE, true);
	renderer->SetRenderState(Renderer::RENDERSTATETYPE_ZENABLE, true);
	//device->SetRenderState(RENDERSTATETYPE_ZENABLE, true); //tdo remove
}
