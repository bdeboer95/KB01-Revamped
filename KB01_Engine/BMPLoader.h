#ifndef __BMLOADER_H__
#define __BMLOADER_H__

#include <Windows.h>

class BMPLoader
{
private:
#pragma pack(2)
	typedef struct tagBITMAPFILEHEADER
	{
		WORD    bfType;				// must be 'BM' 
		DWORD   bfSize;				// size of the whole .bmp file
		WORD    bfReserved1;		// must be 0
		WORD    bfReserved2;		// must be 0
		DWORD   bfOffBits;
	} BITMAPFILEHEADER;

#pragma pack(2)
	typedef struct tagBITMAPINFOHEADER
	{
		unsigned long   biSize;				// size of the structure
		LONG   biWidth;				// image width
		LONG   biHeight;			// image height
		WORD   biPlanes;			// bitplanes
		WORD   biBitCount;			// resolution 
		unsigned long   biCompression;		// compression
		unsigned long   biSizeImage;			// size of the image
		LONG   biXPelsPerMeter;		// pixels per meter X
		LONG   biYPelsPerMeter;		// pixels per meter Y
		DWORD  biClrUsed;			// colors used
		DWORD  biClrImportant;		// important colors
	} BITMAPINFOHEADER;

public:
	BYTE* LoadBMPToTexture(int* _width, int* _height, long* _size, LPCTSTR _bmpfile);
	BYTE* LoadBMPToHeightMap();
};

#endif