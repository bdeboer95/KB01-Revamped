/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

Title : CGameApp.h
Author : Chad Vernon
URL : http://www.c-unit.com

Description : Application header file

Created :  11/29/2005
Modified : 12/01/2005

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma warning(disable:4996)
#ifndef CGAMEAPP_H
#define CGAMEAPP_H

#include "stdafx.h"
#include "CFramework.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CWorldTransform.h"
#include "CUtility.h"
#include "CTriangleStripPlane.h"
#include "CFont.h"
#include "CustomVertex.h"
#include "CMesh.h"
#include "CTerrain.h"

class CGameApp : public CBaseApp
{
public:
    CGameApp();
    ~CGameApp() { Release(); }
    void SetFramework( CFramework* pFramework );
    BOOL Initialize();
    virtual void Release();
    virtual void OnCreateDevice( LPDIRECT3DDEVICE9 pDevice );
    virtual void OnResetDevice( LPDIRECT3DDEVICE9 pDevice );
    virtual void OnLostDevice();
    virtual void OnDestroyDevice();
    virtual void OnUpdateFrame( LPDIRECT3DDEVICE9 pDevice, float elapsedTime );
    virtual void OnRenderFrame( LPDIRECT3DDEVICE9 pDevice, float elapsedTime );
    virtual void ProcessInput( long xDelta, long yDelta, long zDelta, BOOL* pMouseButtons, BOOL* pPressedKeys, float elapsedTime );

private:
    CFramework*         m_pFramework;
    CFont               m_font;
    CTerrain            m_terrain;
    LPD3DXSPRITE        m_pTextSprite;

    char    m_fps[10];
    BOOL    m_showInstructions;
};
#endif