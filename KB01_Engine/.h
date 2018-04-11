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

#include <windows.h>

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
#include <d3dx9.h>
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