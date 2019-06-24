#ifndef __SKYBOX_H__
#define __SKYBOX_H__
#define FVF_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1) 


#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\d3dx9.h"
	/*#include <d3dx9.h>*/
#include "Renderer.h"
#include "ResourceManager.h"
#include "InputListener.h"
#include "Entity.h"

struct Skybox_Cube
{
		std::string			left; //filename for left part of the cube
		std::string			right; //filename for right side of the cube
		std::string			bottom; //filename for bottom side of the cube F
		std::string			top; //filename for top side of the cube
		std::string			back; //filename for back side of the cube
		std::string			front; //filename for front side of the cube
};

class Skybox: public InputListener, Entity
{
private:
	LPD3DXMESH					mesh;
	TextureContainer*			textures[6];  //  a list of 6 textures that define the 6 sides of the skybox
	Skybox_Cube					skyboxCube; //the main part of the skybox is the cube, that will contain the name of the texture files
	
	float						positionX;
	float						positionY;
	float						positionZ;
	float						rotationX;
	float						rotationY;
	float						rotationZ;
	float						speed;
	Matrix						_matRotateX;							//the matrix for the rotation on the x-axis
	Matrix						_matRotateY;							//the matrix for the rotation on the y-axis
	Matrix						_matRotateZ;							//the matrix for the rotation on the z-axis
	Matrix						matWorld;								//the matrix that contains  the multiplication of all the modification matrices (scale, rotate, translate)
	Matrix						matScale;								//the matrix for the scaling of the skybox
	Matrix						_matTranslate;									
	void						LoadTextures(ResourceManager* _resourceManager);

public:
								Skybox(Skybox_Cube skyboxCube);			//Constructor
								~Skybox();								//Destructor	
	bool						SetTexture(std::string _TextureFilePath, int id);  
	bool						InitGeometry(Renderer* _renderer, ResourceManager* _resourceManager);
	std::wstring				StrToWStr(std::string str); //Convert String to WSTR TODO: do we need this?
	void						Render(Renderer* _renderer); //	
	virtual void				Notify(TRANSFORMATIONEVENT transformationEvent, float x = 0, float y = 0); //The skybox needs to move/rotation every time the system detects a change of state for the devices connected
	virtual void				Multiply(D3DXMATRIX* _originalMat, D3DXMATRIX* _modifiedMat); 
};

#endif
