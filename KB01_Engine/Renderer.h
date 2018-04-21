#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Log.h"

#include <Windows.h>
#include <string>
#include "Matrix.h"


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
	virtual void			SetTransform(unsigned int transformStateType, Matrix* matrix) = 0; //Updates the Transform based on the state type that was given (World, view, etc) with the provided matrix
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
};

#endif



