#ifndef __SKYBOX_H__
#define __SKYBOX_H__

#define FVF_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1) 

#include "Entity.h"
#include "InputListener.h"

struct Skybox_Cube
{
	std::string			_left; //filename for left part of the cube
	std::string			_right; //filename for right side of the cube
	std::string			_bottom; //filename for bottom side of the cube
	std::string			_top; //filename for top side of the cube
	std::string			_back; //filename for back side of the cube
	std::string			_front; //filename for front side of the cube
};

class Skybox: public InputListener, Entity
{
public:
	Skybox(Skybox_Cube skyboxCube);	
	~Skybox(); 

	std::wstring		StrToWStr(std::string str); //Convert String to WSTR TODO: do we need this?
	
private:
	Texture*			_textures[6];  //  a list of 6 textures that define the 6 sides of the skybox
	Skybox_Cube			_skyboxCube; //the main part of the skybox is the cube, that will contain the name of the texture files

	void				LoadTextures(ResourceManager* _resourceManager);
	virtual void		Render(Renderer* _renderer); //	
	virtual void		SetupMatrices();
	virtual bool		InitGeometry(Renderer* renderer, ResourceManager* resourceManager);
	virtual void		Notify(TRANSFORMATIONEVENT transformationEvent, float x = 0, float y = 0); //The skybox needs to move/rotation every time the system detects a change of state for the devices connected

};

#endif
