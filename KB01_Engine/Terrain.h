#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "CWorldTransform.h"
#include "CTriangleStripPlane.h"
#include "CUtility.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CustomVertex.h"

#include "InputListener.h"
#include "Entity.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Renderer;

 //forward declared classes, solution for associtions > dependencies?
class Terrain : public CWorldTransform, public InputListener, public Entity
{
public:
	Terrain();
	~Terrain();

	float _positionX;
	float _positionY;
	float _positionZ;
		  
	float _rotationX;
	float _rotationY;


	bool Initialize(Renderer* renderer, char* rawFile, char* terrainTexture);
	void Render(Renderer* renderer);
	void Release();

private:
	VertexBuffer*		_vertexBuffer;
	IndexBuffer*		_indexBuffer;

	LPDIRECT3DTEXTURE9	_texture;
	unsigned char*		_height;

	unsigned int		_numVertices;
	unsigned int		_numIndices;

	Matrix  			_matRotateX; //the matrix for the rotation on the x-axis
	Matrix  			_matRotateY;//the matrix for the rotation on the y-axis
	Matrix  			_matRotateZ;//the matrix for the rotation on the z-axis
		    
	Matrix  			_matWorld; //the matrix that contains  the multiplication of all the modification matrices (scale, rotate, translate)
	Matrix  			_matScale; //the matrix for the scaling of the skybox
	Matrix  			_matTranslate; //the matrix for the translation of the 

	float				_speed;

	void Notify(TRANSFORMATIONEVENT transformationEvent, float x, float y);

};

#endif