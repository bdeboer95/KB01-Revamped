#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE) 

#include "Heightmap.h"
#include "Renderer.h"
#include "Texture.h"

class Terrain
{
public:
	struct CUSTOMVERTEX
	{
		FLOAT x, y, z;		// The transformed position for the vertex
		DWORD color;        // The vertex color
	};
	BITMAPINFOHEADER bmpinfo;
	int width;
	int height;
	Terrain();
	~Terrain();
	
	void Initialize(Renderer* _renderer, Texture* _texture);
	void FillVertexBuffer(Renderer* _renderer);
	void FillIndexBuffer(Renderer* _renderer);
	void Render(Renderer* _renderer);
private:
	Texture* texture;
};
#endif

