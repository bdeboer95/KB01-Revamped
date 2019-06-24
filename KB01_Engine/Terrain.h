#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "TriangleStripGenerator.h"
#include "CustomVertex.h"
#include "InputListener.h"
#include "Entity.h"

class Renderer;
class TextureContainer;
class ResourceManager;

/*
** Name: Terrain
** Description: The ground of the game that can be customized with a texture and placed on a position 
** Parent: InputListener, so that it moves based on the keyboard and mouse input of the user
** Parent: Entity, because it has a position in the world 
*/
class Terrain : public InputListener, public Entity
{
public:
								Terrain(std::string heightmapName);										//Constructor
								~Terrain();																//Deconstructor

	float						_positionX;																//position on the horizontal axis
	float						_positionY;																//position on the vertical axis
	float						_positionZ;																// position on the depth axis
	float						_rotationX;																//horizontal rotation
	float						_rotationY;																// vertical rotation

	bool						Initialize(Renderer* renderer, char* rawFile, char* terrainTexture);	//Initialize the terrain by setting it's initial position and vertices
	void						Render(Renderer* renderer);												//Function that is used to draw the terrain so that it is visible at all times
	void						LoadTexture(ResourceManager* resourceManager, std::string textureName);							//retrieve the texture using a resource manager and saves it
private:
	//LPDIRECT3DTEXTURE9			_texture;															//the texture that is used to customize the terrain's looks
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

	void						Notify(TRANSFORMATIONEVENT transformationEvent, float x, float y);		//the function that notifies the Renderer if the terrain should be drawn on another way
	void						CleanUp();																//Deletes all pointers and variables that may cause memory leaks
	/*void Reset();
	void TranslateAbs(float x, float y, float z);
	void TranslateRel(float x, float y, float z);
	void RotateAbs(float x, float y, float z);
	void RotateRel(float x, float y, float z);
	void ScaleAbs(float x, float y, float z);
	void ScaleRel(float x, float y, float z);

	D3DXMATRIX* GetTransform();
	float GetXPosition() { return m_translate._41; }
	float GetYPosition() { return m_translate._42; }
	float GetZPosition() { return m_translate._43; }
	float GetXRotation() { return m_rotationX; }
	float GetYRotation() { return m_rotationY; }
	float GetZRotation() { return m_rotationZ; }
	float GetXScale() { return m_scale._11; }
	float GetYScale() { return m_scale._22; }
	float GetZScale() { return m_scale._33; }
	void SetXPosition(float x) { m_translate._41 = x; }
	void SetYPosition(float y) { m_translate._42 = y; }
	void SetZPosition(float z) { m_translate._43 = z; }
	void SetXRotation(float x) { RotateAbs(x, m_rotationY, m_rotationZ); }
	void SetYRotation(float y) { RotateAbs(m_rotationX, y, m_rotationZ); }
	void SetZRotation(float z) { RotateAbs(m_rotationX, m_rotationY, z); }
	void SetXScale(float x) { m_scale._11 = x; }
	void SetYScale(float y) { m_scale._22 = y; }
	void SetZScale(float z) { m_scale._33 = z; }*/
};

#endif