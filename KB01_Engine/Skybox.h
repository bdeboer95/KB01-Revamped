#ifndef __SKYBOX_H__
#define __SKYBOX_H__
/*#define FVF_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)*/ 

#include "Renderer.h"
#include "ResourceManager.h"
#include "InputListener.h"
#include "Entity.h"

/// <summary>
/// A skybox consists out of 6 sides that all consists out of a texture filename
/// </summary>
struct Skybox_Cube
{
		std::string				left;																		//filename for left part of the cube
		std::string				right;																		//filename for right side of the cube
		std::string				bottom;																		//filename for bottom side of the cube F
		std::string				top;																		//filename for top side of the cube
		std::string				back;																		//filename for back side of the cube
		std::string				front;																		//filename for front side of the cube
};

/// <summary>
/// The sky that the player will be walking under
/// </summary>
class Skybox: public InputListener, Entity
{
private:
	TextureContainer*			_textures[6];																// A list of 6 textures that define the 6 sides of the skybox
	Skybox_Cube					_skyboxCube;																// the main part of the skybox is the cube, that will contain the name of the texture files														
	void						LoadTextures(ResourceManager* _resourceManager);							// Load the textures for the skybox

public:
								Skybox(Skybox_Cube skyboxCube);												// Constructor
								~Skybox();																	// Destructor	
	bool						InitGeometry(Renderer* renderer, ResourceManager* resourceManager);			// Init the vertices that are needed for making the cube of the skyboxs
	std::wstring				StrToWStr(std::string str);													// Convert String to WSTR TODO: do we need this?
	void						Render(Renderer* renderer);													// Render the skybox with the specified renderer
	virtual void				Notify(TRANSFORMATIONEVENT transformationEvent, float x = 0, float y = 0);	// The skybox needs to move/rotation every time the system detects a change of state for the devices connected
	void						SetUpMatrices();															// Set up the matrices needed to transform the skybox's world position
};

#endif
