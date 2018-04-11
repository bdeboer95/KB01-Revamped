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

/// <summary>
/// Initializes a new instance of the <see cref="RendererDx"/> class.
/// </summary>
RendererDx::RendererDx()
{
	direct3D = NULL; // Used to create the D3DDevice
					 //InitDevice(GetForegroundWindow());
	vertexBuffer = NULL; // Buffer to hold vertices
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
	if (vertexBuffer != NULL)
		if (FAILED(vertexBuffer->Release()))
		{
			return false;
		}


	if (direct3DDevice != NULL)
		if (FAILED(direct3DDevice->Release()))
		{
			return false;
		}

	if (direct3D != NULL)
		if (FAILED(direct3D->Release()))
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
bool RendererDx::InitDevice(HWND _hWnd)
{

	// Create the D3D object.
	if (NULL == (direct3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return false;
	}
	D3DDISPLAYMODE d3dmm;   //定义一个保存当前适配器属性的结构    
	if (FAILED(direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3dmm)))
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
	if (FAILED(direct3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&direct3DDevice)))
	{
		Log::Instance()->LogMessage("RendererDx - Unable to create rendering device.", Log::MESSAGE_ERROR);
		return E_FAIL;
	}
	direct3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	direct3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	direct3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	//direct3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	return true;
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

//-----------------------------------------------------------------------------
// Name: SetMaterial()
// Desc: Sets the material using the direct3DDevice
//-----------------------------------------------------------------------------
///
void RendererDx::SetMaterial(void* _material, UINT _index)
{
	//Unsigned ints can hold a larger positive value, and no negative value.
	//Signed ints can not hold a less large positive value and negative values.
	if (FAILED(direct3DDevice->SetMaterial(&DIRECT3DMATERIAL(_material)[_index])))
	{
		Log::Instance()->LogMessage("RendererDx - Material was failed to be set to the direct3DDevice.", Log::MESSAGE_ERROR);
	}
}

/// <summary>
/// Sets the texture.
/// </summary>
void RendererDx::SetTexture(void* _texture, UINT _index)
{

	if (FAILED(direct3DDevice->SetTexture(0, DIRECT3DTEXTURE(_texture)[_index])))
	{
		Log::Instance()->LogMessage("RendererDx - Texture was failed to set to the direct3DDevice", Log::MESSAGE_ERROR);
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
	if (FAILED(direct3DDevice->CreateVertexBuffer(6 * sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &vertexBuffer, NULL)))
	{
		Log::Instance()->LogMessage("RendererDx - Failed to initialize vertexbuffer", Log::MESSAGE_ERROR);
		return false;
	}

	return true;
}

/// <summary>
/// Sets the view port.
/// </summary>
/// <param name="_viewPort">The _view port.</param>
void RendererDx::SetViewPort(void* _viewPort)
{
	direct3DDevice->SetViewport(static_cast<D3DVIEWPORT9*>(_viewPort));
}

/// <summary>
/// Gets the back buffer.
/// </summary>
/// <returns></returns>
void* RendererDx::GetBackBuffer()
{
	LPDIRECT3DSURFACE9 backBuffer = NULL;
	direct3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
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
float RendererDx::GetBackBuffferHeight()
{
	D3DSURFACE_DESC surfaceDescription;
	static_cast<LPDIRECT3DSURFACE9>(GetBackBuffer()) //Cast the value returned from GetBackBuffer to LPDIRECT3DSURFACE9, because it's a void*
		->GetDesc(&surfaceDescription);//Retrieves a description of the surface.
	return surfaceDescription.Height;
}

/// <summary>
/// Gets the device.
/// </summary>
/// <returns></returns>
void* RendererDx::GetDevice()
{
	return direct3DDevice;
}

/// <summary>
/// Used to present the backbuffer to the frontbuffer for the device.
/// </summary>
void RendererDx::Present(HWND _hWnd)
{
	direct3DDevice->Present(NULL, NULL, _hWnd, NULL);
}

/// <summary>
/// Gets the vertex buffer.
/// </summary>
/// <returns></returns>
void* RendererDx::GetVertexBuffer()
{
	return vertexBuffer;
}

void* RendererDx::GetIndexBuffer()
{
	return indexBuffer;
}
void RendererDx::SetIndexBuffer(void* _indexBuffer)
{
	indexBuffer = static_cast<LPDIRECT3DINDEXBUFFER9>(_indexBuffer);
}
void RendererDx::SetVertexBuffer(void* _vertexBuffer)
{
	vertexBuffer = static_cast<LPDIRECT3DVERTEXBUFFER9>(_vertexBuffer);
}
/// <summary>
/// Clears the buffer.
/// </summary>
/// <param name="R">The r.</param>
/// <param name="G">The g.</param>
/// <param name="B">The b.</param>
void RendererDx::ClearBuffer(int R, int G, int B)
{
	if (FAILED(direct3DDevice->Clear(0, NULL, D3DCLEAR_TARGET /*| D3DCLEAR_ZBUFFER,*/, D3DCOLOR_XRGB(200, 200, 200), 1.0f, 0)))
	{
		Log::Instance()->LogMessage("RendererDx - Unable to clear buffer.", Log::MESSAGE_INFO);
	}
}






//-----------------------------------------------------------------------------
// Name: DrawSubset()
// Desc: Draw the mesh subset for 1 material
//-----------------------------------------------------------------------------
void RendererDx::DrawSubset(void* _mesh, UINT _index)
{
	if FAILED(DIRECT3DMESH(_mesh)->DrawSubset(_index))
	{
		Log::Instance()->LogMessage("RendererDx - The subset could not be drawn with number: ", Log::MESSAGE_ERROR);
	}

}

/// <summary>
/// Draws the primitive.
/// </summary>
void RendererDx::DrawIndexedPrimitive(UINT _numberOfVertices, UINT _primitiveCount)
{
	direct3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _numberOfVertices, 0, _primitiveCount);
}

/// <summary>
/// Sets the stream source.
/// </summary>
void RendererDx::SetStreamSource(UINT _vertexSize)
{
	direct3DDevice->SetStreamSource(0, vertexBuffer, 0, _vertexSize);
}
void RendererDx::SetTransform(unsigned int transformStateType, Matrix* matrix) {
	direct3DDevice->SetTransform(D3DTS_WORLD, reinterpret_cast<D3DXMATRIX*>(matrix)); //CHANGE THE D3DTW_WORLD to trasnformstatetype, which apparently isnt an unsigned int
}
void RendererDx::InitCamera()
{
	D3DXMATRIX matWorld, matWorldX, matWorldY, matWorldZ;
	D3DXMATRIX matView;
	D3DXMATRIX matProj;
	D3DXVECTOR3 cameraPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 cameraTarget = D3DXVECTOR3(0.0f, 0.0f, 5.0f);
	D3DXVECTOR3 cameraUpVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 m_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXMatrixLookAtLH(&matView, &cameraPosition, &cameraTarget, &cameraUpVector);
	static_cast<LPDIRECT3DDEVICE9>(GetDevice())->SetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 2000.0f);
	//
	static_cast<LPDIRECT3DDEVICE9>(GetDevice())->SetTransform(D3DTS_PROJECTION, &matProj);

}
