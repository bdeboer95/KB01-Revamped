#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "TriangleStripGenerator.h"
#include "CustomVertex.h"
#include "InputListener.h"
#include "Entity.h"

class Renderer;
class TextureContainer;
class ResourceManager;


/// <summary>
/// The ground of the game that can be customized with a texture and placed on a position 
/// </summary>
class Terrain : public InputListener, public Entity
{
public:
								Terrain(std::string heightmapName, std::string textureName);			//Constructor							//Constructor
								~Terrain();																//Deconstructor

	float						_positionX;																//position on the horizontal axis
	float						_positionY;																//position on the vertical axis
	float						_positionZ;																//position on the depth axis
	float						_rotationX;																//horizontal rotation
	float						_rotationY;																//vertical rotation
	std::string					_textureName;															//the name of the texture
	
	bool						Initialize(Renderer* renderer, char* rawFile, char* terrainTexture);	//Initialize the terrain by setting it's initial position and vertices
	void						Render(Renderer* renderer);												//Function that is used to draw the terrain so that it is visible at all times
	void						LoadTexture(ResourceManager* resourceManager);							//Load the texture of the terrain using a resource manager					//retrieve the texture using a resource manager and saves it

private:
	unsigned char*				_height;																//the height of the terrain
	float						_speed;																	//the speed on which the terrain is moving
	unsigned int				_numVertices;															//the amount of vertices that is used to draw the terrain
	unsigned int				_numIndices;															//the amount of indices that is used to draw the terrain
	unsigned int				_vertexSize;															//the size of one vertex that is used to draw the terrain
	Matrix  					_matRotateX;															//the matrix for the rotation on the x-axis
	Matrix  					_matRotateY;															//the matrix for the rotation on the y-axis
	Matrix  					_matRotateZ;															//the matrix for the rotation on the z-axis   
	Matrix  					_matWorld;																//the matrix that contains  the multiplication of all the modification matrices (scale, rotate, translate)
	Matrix  					_matScale;																//the matrix for the scaling of the skybox
	Matrix  					_matTranslate;															//the matrix for the translation of the 
	TextureContainer*			_textureContainer;														//the texture that will define the terrain's looks
	
	void						SetUpMatrices();														//Set up the matrices for the terrain
	void						Notify(TRANSFORMATIONEVENT transformationEvent, float x, float y);		//the function that notifies the Renderer if the terrain should be drawn on another way
	void						CleanUp();																//Deletes all pointers and variables that may cause memory leaks

};

#endif