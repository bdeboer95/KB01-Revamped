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

class CTerrain : public CWorldTransform, public InputListener
{
public:

	CTerrain();
	~CTerrain() { Release(); }
	float positionX;
	float positionY;
	float positionZ;
	float rotationX;
	float rotationY;
	BOOL Initialize(LPDIRECT3DDEVICE9 pDevice, char* rawFile, char* terrainTexture);
	void Render(LPDIRECT3DDEVICE9 pDevice);
	void Release();

private:
	CVertexBuffer m_vb;
	CIndexBuffer m_ib;
	LPDIRECT3DTEXTURE9 m_pTexture;
	UCHAR* m_pHeight;
	UINT m_numVertices;
	UINT m_numIndices;
	D3DXMATRIX			 matRotateX; //the matrix for the rotation on the x-axis
	D3DXMATRIX			 matRotateY;//the matrix for the rotation on the y-axis
	D3DXMATRIX			 matRotateZ;//the matrix for the rotation on the z-axis
	D3DXMATRIX			 matWorld; //the matrix that contains  the multiplication of all the modification matrices (scale, rotate, translate)
	D3DXMATRIX			 matScale; //the matrix for the scaling of the skybox
	D3DXMATRIX			 matTranslate;
	float speed;
	void Notify(TRANSFORMATIONEVENT transformationEvent, float x, float y);

};

#endif