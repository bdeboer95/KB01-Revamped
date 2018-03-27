#include "Skybox.h"
#define DIRECT3DDEVICE(device) (static_cast<LPDIRECT3DDEVICE9>(device))
Skybox::Skybox(	Skybox_Cube _skyboxCube)
{

	skyboxCube = _skyboxCube;
}

Skybox::~Skybox(void)
{
}

bool Skybox::InitGeometry(Renderer* _renderer, ResourceManager* _resourceManager)
{
	HRESULT hr = 0;
	
	hr = D3DXCreateMeshFVF(12,  
		24,    
		D3DXMESH_MANAGED, FVF_VERTEX, DIRECT3DDEVICE(_renderer->GetDevice()), &mesh);

	Vertex* v = 0;
	mesh->LockVertexBuffer(0, (void**)&v);   

	//The coordinates for the vertices, that will form the cube. Every set of 4 forms a side of the cube
	//x   //y    //z    nx   ny       nz  tu       tv
	//v[0] = Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	//v[1] = Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	//v[2] = Vertex(1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	//v[3] = Vertex(1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	//
	//v[4] = Vertex(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	//v[5] = Vertex(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	//v[6] = Vertex(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	//v[7] = Vertex(1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	// 
	//v[8] = Vertex(-1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	//v[9] = Vertex(-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	//v[10] = Vertex(-1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//v[11] = Vertex(-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	//v[12] = Vertex(1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	//v[13] = Vertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	//v[14] = Vertex(1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	//v[15] = Vertex(1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	//v[16] = Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	//v[17] = Vertex(-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	//v[18] = Vertex(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	//v[19] = Vertex(1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	// 
	//v[20] = Vertex(-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
	//v[21] = Vertex(-1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
	//v[22] = Vertex(1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
	//v[23] = Vertex(1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f);				
	
	//x   //y    //z    nx   ny       nz  tu       tv
	v[0] = Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[1] = Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = Vertex(1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);  //FRONT
	v[3] = Vertex(1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

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
	mesh->UnlockVertexBuffer();


	WORD* i = 0;
	mesh->LockIndexBuffer(0, (void**)&i);    
	
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
	mesh->UnlockIndexBuffer();    


	DWORD* attributeBuffer = 0; 
	
	//Locks the mesh buffer that contains the mesh attribute data, and returns a pointer to it.
	mesh->LockAttributeBuffer(0, &attributeBuffer);  
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
	mesh->UnlockAttributeBuffer();   
	LoadTextures(_resourceManager);

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
void Skybox::LoadTextures(ResourceManager* _resourceManager)
{
	std::string filePath = "..\\Assets\\Textures\\Skyboxes\\";
	textures[0] = _resourceManager->LoadTexture(filePath, skyboxCube.front);
	textures[1] = _resourceManager->LoadTexture(filePath,skyboxCube.back);
	textures[2] = _resourceManager->LoadTexture(filePath,skyboxCube.left);
	textures[3] = _resourceManager->LoadTexture(filePath,skyboxCube.right);
	textures[4] = _resourceManager->LoadTexture(filePath,skyboxCube.top);
	textures[5] = _resourceManager->LoadTexture(filePath,skyboxCube.bottom);
}

void Skybox::Render(Renderer* _renderer)
{
	D3DXMATRIX matWorld, matWorldX, matWorldY, matWorldZ;
	D3DXMatrixTranslation(&matWorld, 0, -0.1f, 3);
	DIRECT3DDEVICE(_renderer->GetDevice())->SetTransform(D3DTS_WORLD, &matWorld);
	//Disables the zbuffer for writing
	DIRECT3DDEVICE(_renderer->GetDevice())->SetRenderState(D3DRS_ZWRITEENABLE, false);
	DIRECT3DDEVICE(_renderer->GetDevice())->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//Loops through every square side of the cube
	for (int i = 0; i < 6; i++)
	{
		_renderer->SetTexture(textures[i]->GetTextures(), 0); //this is what gives a side of the skybox it's texture
		_renderer->DrawSubset(mesh,i); // draws 
	}
	
	DIRECT3DDEVICE(_renderer->GetDevice())->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//Enables the zbuffer for writing
	DIRECT3DDEVICE(_renderer->GetDevice())->SetRenderState(D3DRS_ZWRITEENABLE, true);
}
