#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Log.h"

#include <Windows.h>
#include <string>

class Matrix;
class Vector3;
class VertexBuffer;
class IndexBuffer;

class Renderer
{
public:
	virtual					~Renderer() {};

	virtual bool			Cleanup() = 0;
	virtual bool			InitDevice(HWND _hWnd) = 0;
	virtual void*			GetDevice() = 0;

	virtual void*			GetBackBuffer() = 0;
	virtual float			GetBackBufferWidth() = 0;
	virtual float			GetBackBuffferHeight() = 0;
	virtual void			ClearBuffer(int R, int G, int B) = 0;

	virtual bool			InitVertexBuffer() = 0; // why no initindexbuffer?
	virtual void*			GetVertexBuffer() = 0;
	virtual void			SetVertexBuffer(VertexBuffer* _vertexBuffer) = 0;

	virtual void*			GetIndexBuffer() = 0;
	virtual void			SetIndexBuffer( IndexBuffer* _indexBuffer) = 0;

	virtual void			DrawIndexedPrimitive(unsigned int primitiveType, UINT baseVertexIndex, UINT minVertexIndex, UINT _numberOfVertices, UINT startIndex, UINT _primitiveCount) = 0;
	virtual void			DrawPrimitive(unsigned int primitiveType, UINT startVertex, UINT primitiveCount) = 0;
	virtual void			DrawSubset(void* _mesh, UINT _index) = 0;

	virtual void			SetTransform(unsigned int transformStateType, Matrix* matrix) = 0; //Updates the Transform based on the state type that was given (World, view, etc) with the provided matrix
	virtual void			SetStreamSource(UINT streamNumber, VertexBuffer* streamData, UINT offsetInBytes, UINT strude) = 0;
	virtual void			SetViewPort(void* _viewPort) = 0;
	virtual void			SetMaterial(void* _material, UINT _index) = 0;
	virtual void			SetTexture(void* _texture, UINT _index) = 0;
	virtual void			SetFVF(DWORD FVF);

	virtual void			Present(HWND _hwnd) = 0;

	// Overerving enumerations?
	typedef enum _TRANSFORMSTATETYPE {
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
	} TRANSFORMSTATETYPE;

	// Primitives supported by draw-primitive API
	typedef enum _PRIMITIVETYPE {
		POINTLIST = 1,
		LINELIST = 2,
		LINESTRIP = 3,
		TRIANGLELIST = 4,
		TRIANGLESTRIP = 5,
		TRIANGLEFAN = 6,
		FORCE_DWORD = 0x7fffffff /* force 32-bit size enum */
	} PRIMITIVETYPE;

	/* Pool types */
	typedef enum _POOL {
		DEFAULT = 0,
		MANAGED = 1,
		SYSTEMMEM = 2,
		SCRATCH = 3,
		FORCE_DWORD = 0x7fffffff /* force 32-bit size enum */
	} POOL;

	const float	PI = 3.141592654f;
	const long	USAGE_DYNAMIC = 0x00000200L;   // pool usage
	const long	USAGE_WRITEONLY = 0x00000008L; // pool usage
	const unsigned long	LOCK_DISCARD = 0x00002000L;	   // lock discard
};

#endif



