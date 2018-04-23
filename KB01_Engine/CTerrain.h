/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Title : CTerrain.h
Author : Chad Vernon
URL : http://www.c-unit.com

Description : Terrain class

Created :  08/11/2005
Modified : 12/05/2005

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma warning(disable:4996)
#ifndef CTERRAIN_H
#define CTERRAIN_H

#include "stdafx.h"
#include "CWorldTransform.h"
#include "CTriangleStripPlane.h"
#include "CUtility.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CustomVertex.h"
#include "InputListener.h"
#include "Renderer.h"
#include "Entity.h"

 //forward declared classes, solution for associtions > dependencies?
class CTerrain : public CWorldTransform, public InputListener, public Entity
{
public:

	CTerrain();
	~CTerrain() { Release(); }//verboden
	float positionX;
	float positionY;
	float positionZ;
	float rotationX;
	float rotationY;
	BOOL Initialize(LPDIRECT3DDEVICE9 pDevice, char* rawFile, char* terrainTexture);
	void Render(Renderer* renderer);
	void Release();

private:
	CVertexBuffer m_vb;
	CIndexBuffer m_ib;
	LPDIRECT3DTEXTURE9 m_pTexture;
	UCHAR*			 m_pHeight;
	UINT			 m_numVertices;
	UINT			 m_numIndices;
	Matrix			 matRotateX; //the matrix for the rotation on the x-axis
	Matrix			 matRotateY;//the matrix for the rotation on the y-axis
	Matrix			 matRotateZ;//the matrix for the rotation on the z-axis
	Matrix			 matWorld; //the matrix that contains  the multiplication of all the modification matrices (scale, rotate, translate)
	Matrix			 matScale; //the matrix for the scaling of the skybox
	Matrix			 matTranslate; //the matrix for the translation of the 
	float speed;
	void Notify(TRANSFORMATIONEVENT transformationEvent, float x, float y);

};


#endif