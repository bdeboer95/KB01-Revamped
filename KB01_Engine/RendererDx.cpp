//-----------------------------------------------------------------------------
// File: RendererDx.cpp
//
// Desc: The RendererDx implements all the methods from Renderer and uses DirextX9.0 3D as it's base
//-----------------------------------------------------------------------------
#include "RendererDx.h"
#include <mmsystem.h>
#include <timeapi.h>
#include <windows.h>
#include <strsafe.h>
#include <vector>
#include <iostream>
#include "Vector3.h"
#include "Matrix.h"

/// <summary>
/// Initializes a new instance of the <see cref="RendererDx"/> class.
/// </summary>
RendererDx::RendererDx()
{
	_direct3D = NULL; // Used to create the D3DDevice
					 //InitDevice(GetForegroundWindow());
	_vertexBuffer = NULL; // Buffer to hold vertices
}

/// <summary>
/// Finalizes an instance of the <see cref="RendererDx"/> class.
/// </summary>
RendererDx::~RendererDx()
{
	Cleanup();
	Log::Instance()->LogMessage("~RendererDx - RendererDx cleaned up!", Log::MESSAGE_INFO);
}

/// <summary>
/// Cleanups this instance.
/// </summary>
bool RendererDx::Cleanup()
{
	if (_vertexBuffer != NULL)
		if (FAILED(_vertexBuffer->Release()))
		{
			return false;
		}

	if (_direct3DDevice != NULL)
		if (FAILED(_direct3DDevice->Release()))
		{
			return false;
		}

	if (_direct3D != NULL)
		if (FAILED(_direct3D->Release()))
		{
			return false;
		}

	return true;
}

/// <summary>
/// Initializes the device.
/// </summary>
/// <param name="_hWnd">The _h WND.</param>
/// <returns></returns>
bool RendererDx::InitDevice(HWND hWnd)
{
	// Create the D3D object.
	if (NULL == (_direct3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return false;
	}

	D3DDISPLAYMODE d3dmm;   //定义一个保存当前适配器属性的结构    
	if (FAILED(_direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3dmm)))
	{
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//d3dpp.BackBufferFormat = d3dmm.Format;
	//d3dpp.BackBufferWidth = d3dmm.Width;
	//d3dpp.BackBufferHeight = d3dmm.Height;
	//d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	//d3dpp.EnableAutoDepthStencil = true;

	if (FAILED(_direct3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&_direct3DDevice)))
	{
		Log::Instance()->LogMessage("RendererDx - Unable to create rendering device.", Log::MESSAGE_ERROR);
		return E_FAIL;
	}

	_direct3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	_direct3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	_direct3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	//direct3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	return true;
}

/// <summary>
/// Gets the device.
/// </summary>
/// <returns></returns>
void* RendererDx::GetDevice()
{
	return _direct3DDevice;
}

/// <summary>
/// Gets the back buffer.
/// </summary>
/// <returns></returns>
void* RendererDx::GetBackBuffer()
{
	LPDIRECT3DSURFACE9 backBuffer = NULL;
	_direct3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	return backBuffer;
}

/// <summary>
/// Gets the width of the back buffer.
/// </summary>
/// <returns></returns>
float RendererDx::GetBackBufferWidth()
{
	D3DSURFACE_DESC surfaceDescription;
	static_cast<LPDIRECT3DSURFACE9>(GetBackBuffer()) //Cast the value returned from GetBackBuffer to LPDIRECT3DSURFACE9, because it's a void*
		->GetDesc(&surfaceDescription);//Retrieves a description of the surface.

	return surfaceDescription.Width;
}

/// <summary>
/// Gets the height of the back bufffer.
/// </summary>
/// <returns></returns>
float RendererDx::GetBackBufferHeight()
{
	D3DSURFACE_DESC surfaceDescription;
	static_cast<LPDIRECT3DSURFACE9>(GetBackBuffer()) //Cast the value returned from GetBackBuffer to LPDIRECT3DSURFACE9, because it's a void*
		->GetDesc(&surfaceDescription);//Retrieves a description of the surface.

	return surfaceDescription.Height;
}

/// <summary>
/// Clears the buffer.
/// </summary>
/// <param name="R">The r.</param>
/// <param name="G">The g.</param>
/// <param name="B">The b.</param>
void RendererDx::ClearBuffer(int R, int G, int B)
{
	if (FAILED(_direct3DDevice->Clear(0, NULL, D3DCLEAR_TARGET /*| D3DCLEAR_ZBUFFER,*/, D3DCOLOR_XRGB(200, 200, 200), 1.0f, 0)))
	{
		Log::Instance()->LogMessage("RendererDx - Unable to clear buffer.", Log::MESSAGE_INFO);
	}
}

/// <summary>
/// Initializes the vertex buffer.
/// </summary>
/// <returns></returns>
bool RendererDx::InitVertexBuffer()
{
	// Create the vertex buffer. Here we are allocating enough memory
	// (from the default pool) to hold all our 3 custom vertices. We also
	// specify the FVF, so the vertex buffer knows what data it contains.
	if (FAILED(_direct3DDevice->CreateVertexBuffer(6 * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &_vertexBuffer, NULL)))
	{
		Log::Instance()->LogMessage("RendererDx - Failed to initialize vertexbuffer", Log::MESSAGE_ERROR);

		return false;
	}

	return true;
}

/// <summary>
/// Gets the vertex buffer.
/// </summary>
/// <returns></returns>
void* RendererDx::GetVertexBuffer()
{
	return _vertexBuffer;
}

void RendererDx::SetVertexBuffer(VertexBuffer* vertexBuffer)
{
	_vertexBuffer = static_cast<LPDIRECT3DVERTEXBUFFER9>(vertexBuffer);
}

void* RendererDx::GetIndexBuffer()
{
	return _indexBuffer;
}

void RendererDx::SetIndexBuffer(IndexBuffer* indexBuffer)
{
	_indexBuffer = static_cast<LPDIRECT3DINDEXBUFFER9>(indexBuffer);
}

/// <summary>
/// Draws the primitive.
/// </summary>
void RendererDx::DrawIndexedPrimitive(unsigned int primitiveType, UINT baseVertexIndex, UINT minVertexIndex, UINT numberOfVertices, UINT startIndex, UINT primitiveCount)
{
	_direct3DDevice->DrawIndexedPrimitive(
		static_cast<D3DPRIMITIVETYPE>(primitiveType),
		baseVertexIndex,
		minVertexIndex,
		numberOfVertices,
		startIndex,
		primitiveCount);
}

void RendererDx::DrawPrimitive(unsigned int primitiveType, UINT startVertex, UINT primitiveCount)
{
	_direct3DDevice->DrawPrimitive(
		static_cast<D3DPRIMITIVETYPE>(primitiveType),
		startVertex,
		primitiveCount);
}

//-----------------------------------------------------------------------------
// Name: DrawSubset()
// Desc: Draw the mesh subset for 1 material
//-----------------------------------------------------------------------------
void RendererDx::DrawSubset(void* mesh, UINT index)
{
	if FAILED(DIRECT3DMESH(mesh)->DrawSubset(index))
	{
		Log::Instance()->LogMessage("RendererDx - The subset could not be drawn with number: ", Log::MESSAGE_ERROR);
	}
}

void RendererDx::SetTransform(unsigned int transformStateType, Matrix* matrix) {

	_direct3DDevice->SetTransform(
		static_cast<D3DTRANSFORMSTATETYPE>(transformStateType),
		reinterpret_cast<D3DXMATRIX*>(matrix)); //CHANGE THE D3DTW_WORLD to trasnformstatetype, which apparently isnt an unsigned int
}

/// <summary>
/// Sets the stream source.
/// </summary>
void RendererDx::SetStreamSource(UINT streamNumber, VertexBuffer* streamData, UINT offsetInBytes, UINT strude)
{
	_direct3DDevice->SetStreamSource(
		streamNumber,
		static_cast<IDirect3DVertexBuffer9>(streamData),
		offsetInBytes,
		strude);
}

/// <summary>
/// Sets the view port.
/// </summary>
/// <param name="_viewPort">The _view port.</param>
void RendererDx::SetViewPort(void* viewPort)
{
	_direct3DDevice->SetViewport(static_cast<D3DVIEWPORT9*>(viewPort));
}

//-----------------------------------------------------------------------------
// Name: SetMaterial()
// Desc: Sets the material using the direct3DDevice
//-----------------------------------------------------------------------------
void RendererDx::SetMaterial(void* material, UINT index)
{
	//Unsigned ints can hold a larger positive value, and no negative value.
	//Signed ints can not hold a less large positive value and negative values.
	if (FAILED(_direct3DDevice->SetMaterial(&DIRECT3DMATERIAL(material)[index])))
	{
		Log::Instance()->LogMessage("RendererDx - Material was failed to be set to the direct3DDevice.", Log::MESSAGE_ERROR);
	}
}

/// <summary>
/// Sets the texture.
/// </summary>
void RendererDx::SetTexture(void* texture, UINT index)
{

	if (FAILED(_direct3DDevice->SetTexture(0, DIRECT3DTEXTURE(texture)[index])))
	{
		Log::Instance()->LogMessage("RendererDx - Texture was failed to set to the direct3DDevice", Log::MESSAGE_ERROR);
	}

}

void RendererDx::SetFVF(DWORD FVF)
{

}

/// <summary>
/// Used to present the backbuffer to the frontbuffer for the device.
/// </summary>
void RendererDx::Present(HWND hWnd)
{
	_direct3DDevice->Present(NULL, NULL, hWnd, NULL);
}










//void RendererDx::CreateSwapChain()
//{
//	D3DPRESENT_PARAMETERS swapChainParameters;
// ZeroMemory(&deviceConfig, sizeof(deviceConfig));
//	deviceConfig.Windowed = TRUE;
//	deviceConfig.SwapEffect = D3DSWAPEFFECT_DISCARD;
//	deviceConfig.BackBufferFormat = D3DFMT_UNKNOWN;
//	deviceConfig.BackBufferHeight = 1024;
//	deviceConfig.BackBufferWidth = 768;
//	deviceConfig.EnableAutoDepthStencil = TRUE;
//	deviceConfig.AutoDepthStencilFormat = D3DFMT_D16;
//	
//
//}

































