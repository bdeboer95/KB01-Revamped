/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

Title : CFont.h
Author : Chad Vernon
URL : http://www.c-unit.com

Description : ID3DXFont wrapper

Created :  08/10/2005
Modified : 12/04/2005

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma warning(disable:4996)
#ifndef CFONT_H
#define CFONT_H

#include "stdafx.h"

// Font alignment
enum FONTALIGNMENT { FA_LEFT, FA_CENTER, FA_RIGHT, FA_TOPRIGHT, FA_TOPLEFT, FA_BOTTOMRIGHT, FA_BOTTOMLEFT };

class CFont
{
public:
    CFont();
    ~CFont() { Release(); }

    BOOL Initialize( LPDIRECT3DDEVICE9 pDevice, char* faceName, int size, BOOL bold = FALSE, 
        BOOL italic = FALSE );
    void Print( char* text, int xPosition, int yPosition, DWORD color, LPD3DXSPRITE sprite = NULL, 
        int textBoxWidth = 0, int textBoxHeight = 0, FONTALIGNMENT alignment = FA_LEFT );
    void OnLostDevice();
    void OnResetDevice();
    void Release();
private:
    LPD3DXFONT m_pFont;
};

#endif