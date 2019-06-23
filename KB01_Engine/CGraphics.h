/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

Title : CGraphics.h
Author : Chad Vernon
URL : http://www.c-unit.com

Description : DirectX Graphics wrapper

Created :  08/26/2005
Modified : 12/01/2005

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CGRAPHICS_H
#define CGRAPHICS_H

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// DirectX Header Files
#include <d3d9.h>
#include "d3dx9.h"
#include <dinput.h>

#include <ctime>
#include <fstream>
#include "resource.h"

// Useful macros
#define SAFE_RELEASE(x) if( x ) { (x)->Release(); (x) = NULL; }
#define SAFE_DELETE(x) if( x ) { delete(x); (x) = NULL; }
#define SAFE_DELETE_ARRAY(x) if( x ) { delete [] (x); (x) = NULL; }
#define SHOWERROR(s,f,l) char buf[1024]; sprintf( buf, "File: %s\nLine: %d\n%s",f,l,s); MessageBox( 0, buf, "Error", 0 );

class CGraphics
{
public:
    CGraphics();
    ~CGraphics() { Release(); }
    BOOL Initialize( HWND hWnd, BOOL bWindowed );
    void Release();
    BOOL Reset();
    LPDIRECT3D9       GetD3D()          { return m_pD3D9; }
    LPDIRECT3DDEVICE9 GetDevice()       { return m_pDevice; }
    D3DDISPLAYMODE*   GetDisplayMode()  { return &m_displayMode; }
    BOOL Windowed;

private:
    BOOL BuildPresentParameters();
    HWND                    m_hWnd;
    HINSTANCE               m_hInstance;
    LPDIRECT3D9             m_pD3D9;
    LPDIRECT3DDEVICE9       m_pDevice;
    D3DCAPS9                m_caps;
    D3DPRESENT_PARAMETERS   m_pp;
    D3DDISPLAYMODE          m_displayMode;
};

#endif