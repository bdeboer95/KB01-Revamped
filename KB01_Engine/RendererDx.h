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
	LPDIRECT3D9					direct3D; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9			direct3DDevice; // Our rendering device
	LPDIRECT3DVERTEXBUFFER9		vertexBuffer; // Our vertex buffer
	LPDIRECT3DINDEXBUFFER9		indexBuffer; // our index buffer
	LPDIRECT3DSWAPCHAIN9*		swapChain;

	struct CUSTOMVERTEX
	{
		float x, y, z;		// The transformed position for the vertex
		unsigned long color;        // The vertex color
	};

public:
	RendererDx();
	virtual						~RendererDx();
	virtual bool				Cleanup();
	virtual bool				InitDevice(HWND _hWnd);
	virtual void*				GetDevice();
	virtual void*				GetVertexBuffer();
	virtual void*				GetIndexBuffer();
	virtual bool				InitVertexBuffer();
	virtual void				ClearBuffer(int R, int G, int B);
	virtual void				SetTransform(unsigned int transformStateType, Matrix* matrix);
	virtual void				SetIndexBuffer(void* _indexBuffer);
	virtual void				SetVertexBuffer(void* _vertexBuffer);
	virtual void				SetTexture(void* _texture, UINT _index);
	virtual void				SetMaterial(void* _material, UINT _index);
	virtual void				DrawSubset(void* _mesh, UINT _index);
	virtual void				SetViewPort(void* _viewPort);
	virtual void				Present(HWND _hwnd);
	virtual void*				GetBackBuffer();
	virtual float				GetBackBufferWidth();
	virtual float				GetBackBuffferHeight();
	virtual void				DrawIndexedPrimitive(UINT _numberOfVertices, UINT _primitiveCount);
	virtual void				SetStreamSource(UINT _vertexSize);
	virtual void				InitCamera();
};

#endif

