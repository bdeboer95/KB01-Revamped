#include "Terrain.h"

#include <mmsystem.h>
#include <d3dx9.h>
#include <fstream>

#define WIDTH 64
#define HEIGHT 64
/// <summary>
/// Initializes a new instance of the <see cref="Terrain"/> class.
/// </summary>
Terrain::Terrain()
{
	
	Log::Instance()->LogMessage("Terrain - Terrain created.", Log::MESSAGE_INFO);
}

/// <summary>
/// Finalizes an instance of the <see cref="Terrain"/> class.
/// </summary>
Terrain::~Terrain()
{
	//TODO
	Log::Instance()->LogMessage("~Terrain - Terrain cleaned up!", Log::MESSAGE_INFO);
}

/// <summary>
/// Initializes this instance.
/// </summary>
void Terrain::Initialize(Renderer* _renderer, Texture* _texture)
{
	texture = _texture;
	FillVertexBuffer(_renderer);
	FillIndexBuffer(_renderer);
	
}

void Terrain::FillVertexBuffer(Renderer* _renderer)
{
	LPDIRECT3DDEVICE9 pd3dDevice = static_cast<LPDIRECT3DDEVICE9>(_renderer->GetDevice());
	LPDIRECT3DVERTEXBUFFER9 pVB = static_cast<LPDIRECT3DVERTEXBUFFER9>(_renderer->GetVertexBuffer());

	//This array contains WIDTH* HEIGHT vertices
	CUSTOMVERTEX cv_Vertices[WIDTH * HEIGHT];
	std::ifstream f_DataFile;
	//Open the file with the height data with this specific name
	f_DataFile.open("..\\Assets\\Heightmaps\\heightdata.raw", std::ios::binary);
	//If the file is opened
	if (f_DataFile.is_open())
	{

		for (int x = 0; x < WIDTH; x++)
		{
			for (int y = 0; y < HEIGHT; y++)
			{
				cv_Vertices[y * WIDTH + x].x = -x; //cv_vertices[0].x=-0;
				cv_Vertices[y * WIDTH + x].y = y;  //cv_vertices[0].y= 0;
				// load byte after byte as our Z coordinate! We divide by 50, otherwise the Z coordinates would be way too high
				cv_Vertices[y * WIDTH + x].z = f_DataFile.get() / 50; //f_DataFile.get()->Extracts characters from the stream, as unformatted input
				cv_Vertices[y * WIDTH + x].color = 0xffffffff; //cv_vertices[0]=0xffffffff = white
			}
		}
	}
	else
	{
		Log::Instance()->LogMessage("Terrain - File not found.", Log::MESSAGE_WARNING);
	}
	//close the file
	f_DataFile.close();

	if (FAILED(pd3dDevice->CreateVertexBuffer(WIDTH * HEIGHT * sizeof(CUSTOMVERTEX), 0, D3DFVF_XYZ | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &pVB, NULL)))
	{
		Log::Instance()->LogMessage("Terrain -VertexBuffer not initialized ", Log::MESSAGE_WARNING);
	}

	VOID* p_Vertices;
	//Lock the vertexbuffer to avoid conflicts with other functions trying to write to it
	if (FAILED(pVB->Lock(0, WIDTH * HEIGHT * sizeof(CUSTOMVERTEX), (void**)&p_Vertices, 0)))
	{
		Log::Instance()->LogMessage("Terrain - VertexBuffer is not locked.", Log::MESSAGE_WARNING);
	}
	else
	{
		//Copies the values of num bytes from the location pointed (cv_vertices)to by source directly to the memory block pointed to by destination (p_vertices). 
		memcpy(p_Vertices, cv_Vertices, WIDTH * HEIGHT * sizeof(CUSTOMVERTEX));
		pVB->Unlock();
	}
	Log::Instance()->LogMessage("Terrain - VertexBuffer is successfully filled.", Log::MESSAGE_INFO);
	//Set the vertexbuffer in the renderer to this vertexbuffer
	_renderer->SetVertexBuffer(pVB);
}

void Terrain::Render(Renderer* _renderer)
{
	LPDIRECT3DDEVICE9 pd3dDevice = static_cast<LPDIRECT3DDEVICE9>(_renderer->GetDevice());
	LPDIRECT3DINDEXBUFFER9 pIB = static_cast<LPDIRECT3DINDEXBUFFER9>(_renderer->GetIndexBuffer());
	LPDIRECT3DVERTEXBUFFER9 pvB = static_cast<LPDIRECT3DVERTEXBUFFER9>(_renderer->GetVertexBuffer());
	//pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//_renderer->SetStreamSource(sizeof(CUSTOMVERTEX));
	LPCWSTR result = L"..\\Assets\\Textures\\Terrain\\terrainbrown.jpg";

	
	_renderer->SetTexture(texture->GetTextures(), 0);
	if (FAILED(pd3dDevice->SetStreamSource(0, pvB, 0, sizeof(CUSTOMVERTEX))))
	{
		Log::Instance()->LogMessage("Terrain -Streamsource is not set ", Log::MESSAGE_WARNING);
	}

	pd3dDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	if (FAILED(pd3dDevice->SetIndices(pIB)))
	{
		Log::Instance()->LogMessage("Terrain -Set indices not set ", Log::MESSAGE_WARNING);
	}
	D3DXMATRIX m_Translation;
	D3DXMATRIX matRotateY;
	D3DXMATRIX matWorld;
	D3DXMatrixTranslation(&m_Translation, 0, -64, 5);
	D3DXMatrixRotationY(&matRotateY, 1.0f);
	matWorld = m_Translation*matRotateY;
	pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);
	
	if (FAILED(pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, WIDTH * HEIGHT, 0, (WIDTH - 1)*(HEIGHT - 1) * 2)))
	{
		Log::Instance()->LogMessage("Terrain -Failed to draw primitive ", Log::MESSAGE_ERROR);
	}
	
	pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//_renderer->DrawIndexedPrimitive(width*height, (width - 1)*(height - 1) * 2);
}


void Terrain::FillIndexBuffer(Renderer* _renderer)
{
	//we use indices to store less vertices into the array
	LPDIRECT3DDEVICE9 pd3dDevice = static_cast<LPDIRECT3DDEVICE9>(_renderer->GetDevice());
	LPDIRECT3DINDEXBUFFER9 pIB = static_cast<LPDIRECT3DINDEXBUFFER9>(_renderer->GetIndexBuffer());

	//short-> this is used because this does not need to be a big variable
	short s_Indices[(WIDTH - 1)*(HEIGHT - 1) * 6];
	//There will be a total of WIDTH * HEIGHT squares
	//this will generate the indices for the terrain's width span
	for (int x = 0; x < WIDTH - 1; x++)
	{
		//this will generate the indices for the terrain's height span
		for (int y = 0; y < HEIGHT - 1; y++)
		{
			//Triangle 1
			s_Indices[(x + y*(WIDTH - 1)) * 6 + 2] = x + y * WIDTH;
			s_Indices[(x + y*(WIDTH - 1)) * 6 + 1] = (x + 1) + y * WIDTH;
			s_Indices[(x + y*(WIDTH - 1)) * 6] = (x + 1) + (y + 1) * WIDTH;

			//Triangle 2
			s_Indices[(x + y*(WIDTH - 1)) * 6 + 3] = (x + 1) + (y + 1) * WIDTH;
			s_Indices[(x + y*(WIDTH - 1)) * 6 + 4] = x + y * WIDTH;
			s_Indices[(x + y*(WIDTH - 1)) * 6 + 5] = x + (y + 1) * WIDTH;

			//Triangle 1 + Triangle 2= 1 Square
		}
	}

	if (FAILED(pd3dDevice->CreateIndexBuffer((WIDTH - 1)*(HEIGHT - 1) * 6 * sizeof(short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIB, NULL)))
	{
		Log::Instance()->LogMessage("Terrain - Indexbuffer not initialized.", Log::MESSAGE_WARNING);
	}

	VOID* p_Indices;
	if (FAILED(pIB->Lock(0, (WIDTH - 1)*(HEIGHT - 1) * 6 * sizeof(short), (void**)&p_Indices, 0)))
	{
		Log::Instance()->LogMessage("Terrain - Indexbuffer not locked.", Log::MESSAGE_WARNING);
	}
	else
	{
		memcpy(p_Indices, s_Indices, (WIDTH - 1)*(HEIGHT - 1) * 6 * sizeof(short));
		pIB->Unlock();
	}
	_renderer->SetIndexBuffer(pIB);
}
