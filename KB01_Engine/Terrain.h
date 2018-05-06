#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "CTriangleStripPlane.h"
#include "CUtility.h"
#include "CustomVertex.h"

#include "InputListener.h"
#include "Entity.h"

class Renderer;

 //forward declared classes, solution for associtions > dependencies?
class Terrain : public InputListener, public Entity
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

private:
	LPDIRECT3DTEXTURE9	_texture;
	unsigned char*		_height;

	unsigned int		_numVertices;
	unsigned int		_numIndices;
	unsigned int		_vertexSize;
	Matrix  			_matRotateX; //the matrix for the rotation on the x-axis
	Matrix  			_matRotateY;//the matrix for the rotation on the y-axis
	Matrix  			_matRotateZ;//the matrix for the rotation on the z-axis
		    
	Matrix  			_matWorld; //the matrix that contains  the multiplication of all the modification matrices (scale, rotate, translate)
	Matrix  			_matScale; //the matrix for the scaling of the skybox
	Matrix  			_matTranslate; //the matrix for the translation of the 

	float				_speed;

	void Notify(TRANSFORMATIONEVENT transformationEvent, float x, float y);

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