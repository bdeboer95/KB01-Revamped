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
	unsigned int				_vertexSize;
	unsigned long				_fvf;

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

	virtual bool			CreateVertexBuffer(unsigned int numVertices, unsigned int vertexSize, unsigned long fvf, HANDLE handle, bool dynamic=false); // why no initindexbuffer?
	virtual void*			GetVertexBuffer();
	virtual bool			FillVertexBuffer(unsigned int numVertices, void *pVertices, unsigned long flags);

	virtual void			CreateIndexBuffer(unsigned int numIndices, unsigned long format, HANDLE handle, bool dynamic = false);
	virtual void*			GetIndexBuffer();
	virtual void			FillIndexBuffer(unsigned int numIndices, void *pIndices, unsigned long flags = D3DLOCK_DISCARD);
	virtual void			SetIndices();
	virtual void			DrawIndexedPrimitive(unsigned int primitiveType, unsigned int baseVertexIndex, unsigned int minVertexIndex, unsigned int numberOfVertices, unsigned int startIndex, unsigned int primitiveCount);
	virtual void			DrawPrimitive(unsigned int primitiveType, unsigned int startVertex, unsigned int primitiveCount);
	virtual void			DrawSubset(void* mesh, unsigned int index);

	virtual void			SetTransform(unsigned int transformStateType, Matrix* matrix); //Updates the Transform based on the state type that was given (World, view, etc) with the provided matrix
	virtual void			SetStreamSource(unsigned int streamNumber,  unsigned int offsetInBytes, unsigned int stride);
	virtual void			SetViewPort(void* viewPort);
	virtual void			SetMaterial(void* material, unsigned int index);
	virtual void			SetTexture(void* texture, unsigned int index);
	virtual void			SetFVF();
	virtual void			Present(HWND hwnd);

};

#endif

