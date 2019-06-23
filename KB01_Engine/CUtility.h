/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Title : CUtility.h
Author : Chad Vernon
URL : http://www.c-unit.com

Description : Utility functions

Created :  11/29/2005
Modified : 12/01/2005

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CUTILITY_H
#define CUTILITY_H
// Exclude rarely-used stuff from Windows headers
#pragma warning(disable:4996)
#define WIN32_LEAN_AND_MEAN		    
#define DIRECTINPUT_VERSION 0x0800

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
#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\d3dx9.h"
#include <dinput.h>

#include <ctime>
#include <fstream>
#include "resource.h"

class CUtility
{
public:
	static BOOL GetMediaFile(char* file, char path[]);
private:
	static BOOL SearchFolders(char* filename, char* exeFolder, char* exeName, char fullPath[]);
};

#endif