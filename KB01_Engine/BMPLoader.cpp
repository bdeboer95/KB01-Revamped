//-----------------------------------------------------------------------------
// File: BMPLoader.cpp
//
// Desc: The bitmap consists of 3 parts;
//		- The file header, that holds information about type, size and layout of the file
//		- The info header, that holds information about dimension and color format of the image
//		- The image data
//-----------------------------------------------------------------------------

#include "BMPLoader.h"
#include "Log.h"

#include <iostream>

/// <summary>
/// Loads the BMP to texture.
/// </summary>
/// <param name="_width">The _width.</param>
/// <param name="_height">The _height.</param>
/// <param name="_size">The _size.</param>
/// <param name="_bmpfile">The _bmpfile.</param>
/// <returns></returns>
BYTE* BMPLoader::LoadBMPToTexture(int* _width, int* _height, long* _size, LPCTSTR _bmpfile)
{
	BITMAPFILEHEADER bmpheader;
	BITMAPINFOHEADER bmpinfo;
	DWORD bytesread;

	// Open the fileS
	HANDLE file = CreateFile(_bmpfile, GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (NULL == file)
		Log::Instance()->LogMessage("BMPLoader - File not found.", Log::MESSAGE_WARNING);
		return NULL;

	// Read file header
	if (ReadFile(file, &bmpheader, sizeof(BITMAPFILEHEADER), &bytesread, NULL) == false)
	{
		CloseHandle(file);
		return NULL;
	}

	// Read info header
	if (ReadFile(file, &bmpinfo, sizeof(BITMAPINFOHEADER), &bytesread, NULL) == false)
	{
		CloseHandle(file);
		return NULL;
	}

	// Check if it's a bitmap
	if (bmpheader.bfType != 'MB')
	{
		CloseHandle(file);
		return NULL;
	}

	// Check if it's uncompressed
	if (bmpinfo.biCompression != BI_RGB)
	{
		CloseHandle(file);
		return NULL;
	}

	// Check if it's 24 bit
	if (bmpinfo.biBitCount != 24)
	{
		CloseHandle(file);
		return NULL;
	}




	//int i;
	//FILE* f = fopen(filename, "rb");
	//unsigned char info[54];
	//fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

	//// extract image height and width from header
	//int width = *(int*)&info[18];
	//int height = *(int*)&info[22];

	//int size = 3 * width * height;
	//unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
	//fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
	//fclose(f);
	//unsigned char* dataGrayScale = new unsigned char[width*height];
	//int counter = 0;

	//for (i = 0; i < size; i += 3)
	//{
	//	dataGrayScale[i] = (data[i] + data[i + 1] + data[i + 2]) / 3 //the avg of the rgb is the grayscale value
	//		counter++;
	//}

	//delete[] data;
	//return dataGrayScale;
	






	// Get size and dimensions
	*_width = bmpinfo.biWidth;
	*_height = abs(bmpinfo.biHeight);
	*_size = bmpheader.bfSize - bmpheader.bfOffBits;

	// Buffer to hold the data
	BYTE* Buffer = new BYTE[*_size];

	// Pointer to start of the image data
	SetFilePointer(file, bmpheader.bfOffBits, NULL, FILE_BEGIN);

	// Read the data
	if (ReadFile(file, Buffer, *_size, &bytesread, NULL) == false)
	{
		delete[] Buffer;
		CloseHandle(file);
		return NULL;
	}

	// Wrap up
	CloseHandle(file);
	Log::Instance()->LogMessage("BMPLoader - BMP to Texture is loaded.", Log::MESSAGE_INFO);
	return Buffer;
}

/// <summary>
/// Loads the BMP to height map.
/// </summary>
/// <returns></returns>
BYTE* BMPLoader::LoadBMPToHeightMap()
{
	return 0;
}
