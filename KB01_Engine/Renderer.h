#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Log.h"
#include "Matrix.h"

#include <Windows.h>
#include <string>

class Renderer
{
public:
	virtual ~Renderer() {};

	virtual bool			Cleanup() = 0;
	virtual bool			InitDevice(HWND _hWnd) = 0;
	virtual void*			GetDevice() = 0;
	virtual void*			GetVertexBuffer() = 0;
	virtual void*			GetIndexBuffer() = 0;
	virtual bool			InitVertexBuffer() = 0;
	virtual void			SetIndexBuffer(void* _indexBuffer) = 0;
	virtual void			SetVertexBuffer(void* _vertexBuffer) = 0;
	virtual void			ClearBuffer(int R, int G, int B) = 0;
	virtual void			SetViewPort(void* _viewPort) = 0;
	virtual void			Present(HWND _hwnd) = 0;
	virtual void*			GetBackBuffer() = 0;
	virtual float			GetBackBufferWidth() = 0;
	virtual float			GetBackBuffferHeight() = 0;
	virtual void			SetMaterial(void* _material, UINT _index) = 0;
	virtual void			SetTexture(void* _texture, UINT _index) = 0;
	virtual void			DrawIndexedPrimitive(UINT _numberOfVertices, UINT _primitiveCount) = 0;
	virtual void			DrawSubset(void* _mesh, UINT _index) = 0;
	virtual void			SetStreamSource(UINT _vertexSize) = 0;

	virtual void			SetTransform(TRANSFORMSTATE _state, Matrix* _matrix) = 0;
	virtual void			SetRenderState(RENDERSTATE _state, DWORD _value) = 0;

	virtual void			InitCamera() = 0;


};

// Taken straight from d3d9types.h
typedef enum _CULLTING {
	CULL_NONE			= 1,
	CULL_CW				= 2,
	CULL_CCW			= 3,
	CULL_FORCE_DWORD	= 0x7fffffff, /* force 32-bit size enum */
} CULL;

typedef enum _RENDERSTATE {
	ZENABLE			= 7,    /* D3DZBUFFERTYPE (or TRUE/FALSE for legacy) */
	FILLMODE		= 8,    /* D3DFILLMODE */
	SHADEMODE		= 9,    /* D3DSHADEMODE */
	ZWRITEENABLE	= 14,   /* TRUE to enable z writes */
	ALPHATESTENABLE = 15,   /* TRUE to enable alpha tests */
	LASTPIXEL		= 16,   /* TRUE for last-pixel on lines */
	SRCBLEND		= 19,   /* D3DBLEND */
	DESTBLEND		= 20,   /* D3DBLEND */
	CULLMODE		= 22,   /* D3DCULL */
	ZFUNC			= 23	/* D3DCMPFUNC */
} RENDERSTATE;

typedef enum _TRANSFORMSTATE {
	VIEW = 2,
	PROJECTION = 3,
	TEXTURE0 = 16,
	TEXTURE1 = 17,
	TEXTURE2 = 18,
	TEXTURE3 = 19,
	TEXTURE4 = 20,
	TEXTURE5 = 21,
	TEXTURE6 = 22,
	TEXTURE7 = 23,
	FORCE_DWORD = 0x7fffffff, /* force 32-bit size enum */
	WORLD = 256
} TRANSFORMSTATE;
#endif



