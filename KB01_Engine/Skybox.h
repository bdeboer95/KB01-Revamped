#ifndef __SKYBOX_H__
#define __SKYBOX_H__
#define FVF_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1) 

#include "d3dx9.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "InputListener.h"
struct Vertex
{
	Vertex(){}     
	Vertex(float x, float y, float z,
		float nx, float ny, float nz,
		float u, float v)  
	{
		_x = x;  _y = y;  _z = z;
		_nx = nx; _ny = ny; _nz = nz;
		_u = u;  _v = v;
	}

	float  _x, _y, _z;   
	float _nx, _ny, _nz;   
	float  _u, _v;       
};

struct Skybox_Cube
{
	std::string			left;
	std::string			right;
	std::string			bottom;
	std::string			top;
	std::string			back;
	std::string			front;
};

class Skybox: public InputListener
{
private:
	LPD3DXMESH          mesh;
	Texture*			textures[6];  
	Skybox_Cube			skyboxCube;
	D3DXMATRIX matRotateX;
	D3DXMATRIX matRotateY;
	D3DXMATRIX matRotateZ;
	D3DXMATRIX matWorld;
	D3DXMATRIX matWorldX;
	D3DXMATRIX matWorld;
	D3DXMATRIX matWorldZ;
	void				LoadTextures(ResourceManager* _resourceManager);

public:
	Skybox(Skybox_Cube skyboxCube);
	~Skybox();

	bool				SetTexture(std::string _TextureFilePath, int id);  
	bool				InitGeometry(Renderer* _renderer, ResourceManager* _resourceManager);
	std::wstring		StrToWStr(std::string str);
	void				Render(Renderer* _renderer);	
	virtual void		Notify(byte _state[]);
};

#endif