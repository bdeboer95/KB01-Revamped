#ifndef __SKYBOX_H__
#define __SKYBOX_H__
#define FVF_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1) 

#include "d3dx9.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "InputListener.h"
#include "Entity.h"
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
		std::string			left; //filename for left part of the cube
		std::string			right; //filename for right side of the cube
		std::string			bottom; //filename for bottom side of the cube
		std::string			top; //filename for top side of the cube
		std::string			back; //filename for back side of the cube
		std::string			front; //filename for front side of the cube
};

class Skybox: public InputListener, Entity
{
private:
	LPD3DXMESH          mesh;
	Texture*			textures[6];  //  a list of 6 textures that define the 6 sides of the skybox
	Skybox_Cube			skyboxCube; //the main part of the skybox is the cube, that will contain the name of the texture files
	
	float				positionX;
	float				positionY;
	float				positionZ;
	float				rotationX;
	float				rotationY;
	float				rotationZ;
	float				speed;
	D3DXMATRIX matRotateX; //the matrix for the rotation on the x-axis
	D3DXMATRIX matRotateY;//the matrix for the rotation on the y-axis
	D3DXMATRIX matRotateZ;//the matrix for the rotation on the z-axis
	D3DXMATRIX matWorld; //the matrix that contains  the multiplication of all the modification matrices (scale, rotate, translate)
	D3DXMATRIX matScale; //the matrix for the scaling of the skybox
	D3DXMATRIX matTranslate;
	void				LoadTextures(ResourceManager* _resourceManager);

public:
	Skybox(Skybox_Cube skyboxCube); //CONSTRUCTOR
	~Skybox(); //DESTRUCTOR

	bool				SetTexture(std::string _TextureFilePath, int id);  
	bool				InitGeometry(Renderer* _renderer, ResourceManager* _resourceManager);
	std::wstring		StrToWStr(std::string str); //Convert String to WSTR TODO: do we need this?
	void				Render(Renderer* _renderer); //	
	virtual void		Notify(TRANSFORMATIONEVENT transformationEvent, float x = 0, float y = 0); //The skybox needs to move/rotation every time the system detects a change of state for the devices connected
	virtual void		Multiply(D3DXMATRIX* _originalMat, D3DXMATRIX* _modifiedMat); 
};

#endif
