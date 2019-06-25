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
/// It also handles the graphical devices and can do certain actions with the buffer(s)
/// </summary>
class Renderer
{
public:
	/// <summary>
	/// Primitype types used to draw vertices
	/// </summary>
	typedef enum _PRIMITIVETYPE {
		POINTLIST = 1,
		LINELIST = 2,
		LINESTRIP = 3,
		TRIANGLELIST = 4,
		TRIANGLESTRIP = 5,
		TRIANGLEFAN = 6
	} PRIMITIVETYPE;

	/// <summary>
	/// Pool types
	/// </summary>
	typedef enum _POOL :unsigned long {
		DEFAULT = 0,
		MANAGED = 1,
		SYSTEMMEM = 2,
		SCRATCH = 3,
	} POOL;

	/// <summary>
	/// The render state type for the back buffer
	/// </summary>
	typedef enum _RENDERSTATETYPE {
		RENDERSTATETYPE_ZENABLE = 7,    /* D3DZBUFFERTYPE (or TRUE/FALSE for legacy) */
		RENDERSTATETYPE_CULLMODE = 22
	}RENDERSTATETYPE;

	/// <summary>
	/// Which type of culling mode (drawing backwards) is it
	/// </summary>
	typedef enum _CULL :unsigned long {
		CULL_NONE = 1,
		CULL_CW = 2,
		CULL_CCW = 3,
	} CULL;

	virtual			~Renderer() {}																														//Destructor
	virtual void	Release() = 0;																														//release the indexbuffer and the vertexbuffer
	virtual bool	Cleanup() = 0;																														//Delete all pointers and variables that can cause memory leaks
	virtual bool	InitDevice(HWND hWnd) = 0;																											//Init the graphics device
	virtual void*	GetDevice() = 0;																													//Get the graphics device
	virtual void*	GetBackBuffer() = 0;																												//Get the backbuffer
	virtual float	GetBackBufferWidth() = 0;																											//Get the width of the backbuffer
	virtual float	GetBackBufferHeight() = 0;																											//Get the height of the backbuffer
	virtual void	ClearBuffer(int r, int g, int b) = 0;																								//Clear the backbuffer with a backgroundcolor
	virtual void	LockVertexBuffer(unsigned long flags, void** ppData) = 0;																			//Lock the vertex buffer
	virtual void	LockAttributeBuffer(unsigned long flags, unsigned long** ppData)=0 ;																//Lock the attribute buffer
	virtual void	UnlockVertexBuffer()=0;
	virtual void	UnlockIndexBuffer()=0;
	virtual void	UnLockAttributeBuffer()=0;
	virtual void	LockIndexBuffer(unsigned long flags, void** ppData)=0;																				//Lock the indexbuffer
	virtual bool	CreateVertexBuffer(unsigned int numVertices, unsigned int vertexSize, unsigned long fvf, HANDLE handle, bool dynamic = false) = 0;
	virtual void*	GetVertexBuffer() = 0;
	virtual bool	FillVertexBuffer(unsigned int numVertices, void *pVertices, unsigned long flags) = 0;
	virtual void	SetIndices() = 0;
	virtual void	CreateIndexBuffer(unsigned int numIndices, unsigned long format, HANDLE handle, bool dynamic = false) = 0;
	virtual void*	GetIndexBuffer() = 0;
	virtual void	FillIndexBuffer(unsigned int numIndices, void *pIndices, unsigned long flags) = 0;
	virtual void	DrawIndexedPrimitive(unsigned int primitiveType, unsigned int baseVertexIndex, unsigned int minVertexIndex, unsigned int numberOfVertices, unsigned int startIndex, unsigned int primitiveCount) = 0;
	virtual void	DrawPrimitive(unsigned int primitiveType, unsigned int startVertex, unsigned int primitiveCount) = 0;
	virtual void	DrawSubset(void* mesh, unsigned int index) = 0;
	virtual void	SetTransform(unsigned int transformStateType, Matrix* matrix) = 0; //Updates the Transform based on the state type that was given (World, view, etc) with the provided matrix
	virtual void	SetStreamSource(unsigned int streamNumber, unsigned int offsetInBytes, unsigned int strude) = 0;
	virtual void	SetViewPort(void* viewPort) = 0;
	virtual void	SetRenderState(RENDERSTATETYPE renderStateType, unsigned long value) = 0;
	virtual void	SetMaterial(void* material, unsigned int index) = 0;
	virtual void	SetTexture(void* texture, unsigned int index) = 0;
	virtual void	SetFVF() = 0;
	virtual void	Present(HWND hwnd) = 0;
	virtual bool	BeginScene() = 0;
	virtual void	EndScene() = 0;
	virtual bool	CreateMeshFVF()=0;

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



