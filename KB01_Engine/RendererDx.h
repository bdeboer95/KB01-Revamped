#ifndef __RENDERERDX_H__
#define __RENDERERDX_H__

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)
#define DIRECT3DTEXTURE(texture) (static_cast<LPDIRECT3DTEXTURE9*>(texture)) //need to delete these
#define DIRECT3DMATERIAL(material) (static_cast<D3DMATERIAL9*> (material))
#define DIRECT3DMESH(mesh) (static_cast<LPD3DXMESH>(mesh))
#define DIRECT3DPRIMITIVETYPE(primitiveType) (static_cast<D3DPRIMITIVETYPE*> (primitiveType))

#include "Renderer.h"
#include <mmsystem.h>
#include <d3dx9.h>
#include <DXGI1_2.h>
#include "Log.h"

class RendererDx : public Renderer
{
private:
	LPDIRECT3D9					_direct3D; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9			_direct3DDevice; // Our rendering device
	LPDIRECT3DVERTEXBUFFER9		_vertexBuffer; // Our vertex buffer
	LPDIRECT3DINDEXBUFFER9		_indexBuffer; // our index buffer
	LPDIRECT3DSWAPCHAIN9*		_swapChain;

	struct CUSTOMVERTEX
	{
		float x, y, z;		// The transformed position for the vertex
		unsigned long color;        // The vertex color
	};

public:
	RendererDx();
	virtual					~RendererDx();
	virtual bool			Cleanup(); //Deletes all the pointers that have been initialized
	virtual bool			InitDevice(HWND hWnd); //Initializes the graphical device
	virtual void*			GetDevice(); //Gets the graphical device

	virtual void*			GetBackBuffer();
	virtual float			GetBackBufferWidth();
	virtual float			GetBackBufferHeight();
	virtual void			ClearBuffer(int r, int g, int b);

	virtual bool			InitVertexBuffer(); // why no initindexbuffer?
	virtual void*			GetVertexBuffer();
	virtual void			SetVertexBuffer(VertexBuffer* vertexBuffer);

	virtual void*			GetIndexBuffer();
	virtual void			SetIndexBuffer(IndexBuffer* indexBuffer);

	virtual void			DrawIndexedPrimitive(unsigned int primitiveType, UINT baseVertexIndex, UINT minVertexIndex, UINT numberOfVertices, UINT startIndex, UINT primitiveCount);
	virtual void			DrawPrimitive(unsigned int primitiveType, UINT startVertex, UINT primitiveCount);
	virtual void			DrawSubset(void* mesh, UINT index);

	virtual void			SetTransform(unsigned int transformStateType, Matrix* matrix); //Updates the Transform based on the state type that was given (World, view, etc) with the provided matrix
	virtual void			SetStreamSource(UINT streamNumber, VertexBuffer* streamData, UINT offsetInBytes, UINT strude);
	virtual void			SetViewPort(void* viewPort);
	virtual void			SetMaterial(void* material, UINT index);
	virtual void			SetTexture(void* texture, UINT index);
	virtual void			SetFVF(DWORD FVF);
	virtual void			Present(HWND hwnd);

};

#endif

