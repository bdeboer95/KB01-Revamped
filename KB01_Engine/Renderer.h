#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Log.h"
#include <Windows.h>
#include <string>

class Matrix;
class Vector3;
class VertexBuffer;
class IndexBuffer;

/// <summary>
/// The renderer draws vertices, indices and background with color onto a window
/// </summary>
class Renderer
{
public:
	// Primitives supported by draw-primitive API
	typedef enum _PRIMITIVETYPE {
		POINTLIST = 1,
		LINELIST = 2,
		LINESTRIP = 3,
		TRIANGLELIST = 4,
		TRIANGLESTRIP = 5,
		TRIANGLEFAN = 6
	} PRIMITIVETYPE;

	/* Pool types */
	typedef enum _POOL :unsigned long {
		DEFAULT = 0, //ask Vincent if we should make this 
		MANAGED = 1,
		SYSTEMMEM = 2,
		SCRATCH = 3,
	} POOL;

	virtual					~Renderer() {} //Destructor
	virtual void			Release() = 0; //release the indexbuffer and the vertexbuffer
	virtual bool			Cleanup() = 0;
	virtual bool			InitDevice(HWND hWnd) = 0;
	virtual void*			GetDevice() = 0;

	virtual void*			GetBackBuffer() = 0;
	virtual float			GetBackBufferWidth() = 0;
	virtual float			GetBackBufferHeight() = 0;
	virtual void			ClearBuffer(int r, int g, int b) = 0;

	virtual bool			CreateVertexBuffer(unsigned int numVertices, unsigned int vertexSize, unsigned long fvf, HANDLE handle, bool dynamic = false) = 0; // why no initindexbuffer?
	virtual void*			GetVertexBuffer() = 0;
	virtual bool			FillVertexBuffer(unsigned int numVertices, void *pVertices, unsigned long flags) = 0;
	virtual void			SetIndices() = 0;
	virtual void			CreateIndexBuffer(unsigned int numIndices, unsigned long format, HANDLE handle, bool dynamic = false) = 0;
	virtual void*			GetIndexBuffer() = 0;
	virtual void			FillIndexBuffer(unsigned int numIndices, void *pIndices, unsigned long flags) = 0;
	virtual void			DrawIndexedPrimitive(unsigned int primitiveType, unsigned int baseVertexIndex, unsigned int minVertexIndex, unsigned int numberOfVertices, unsigned int startIndex, unsigned int primitiveCount) = 0;
	virtual void			DrawPrimitive(unsigned int primitiveType, unsigned int startVertex, unsigned int primitiveCount) = 0;
	virtual void			DrawSubset(void* mesh, unsigned int index) = 0;

	virtual void			SetTransform(unsigned int transformStateType, Matrix* matrix) = 0; //Updates the Transform based on the state type that was given (World, view, etc) with the provided matrix
	virtual void			SetStreamSource(unsigned int streamNumber, unsigned int offsetInBytes, unsigned int strude) = 0;
	virtual void			SetViewPort(void* viewPort) = 0;
	virtual void			SetMaterial(void* material, unsigned int index) = 0;
	virtual void			SetTexture(void* texture, unsigned int index) = 0;
	virtual void			SetFVF() = 0;

	virtual void			Present(HWND hwnd) = 0; 

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


};

#endif



