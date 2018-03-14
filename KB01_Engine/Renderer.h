#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <Windows.h>
#include <string>
#include "Log.h"
#include "DXVector3.h"

class Renderer
{
public:
	virtual ~Renderer(){};

	virtual bool			Cleanup() = 0;
	virtual bool			InitDevice(HWND _hWnd) = 0;
	virtual void*			GetDevice() = 0;
	virtual void*			GetVertexBuffer() = 0;
	virtual void*			GetIndexBuffer() = 0;
	virtual bool			InitVertexBuffer() = 0;
	virtual void			SetIndexBuffer(void* _indexBuffer ) = 0;
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
	
	// CAMERA
	virtual void			SetCamera(DXVector3 * const &_m_right, DXVector3 * const &_cameraPosition, DXVector3 * const &_cameraTarget, DXVector3 * const &_cameraUpVector) = 0;
};



#endif