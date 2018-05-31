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
	//PI = ;
	//USAGE_DYNAMIC = 0x00000200L;
	//USAGE_WRITEONLY = 0x00000008L;
	//LOCK_DISCARD = 0x00002000L;
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
/// Cleanups this instance and releases the buffers and devices
/// </summary>
bool RendererDx::Cleanup()
{
	
	if (_direct3DDevice != NULL)
		if (FAILED(_direct3DDevice->Release()))
		{
			return false;
		}

	if (_direct3D != NULL)
		if (FAILED(_direct3D->Release()))
		{
			Log::Instance()->LogMessage("~RendererDx - Failed to release direct3d!", Log::MESSAGE_WARNING);
			return false;
		}

	return true;
}
void RendererDx::Release() {
	if (_vertexBuffer != NULL)
		if (FAILED(_vertexBuffer->Release()))
		{
			Log::Instance()->LogMessage("~RendererDx - Failed to release vertexbuffer!", Log::MESSAGE_WARNING);
		
		}
	if (_indexBuffer != NULL) {
		if (FAILED(_indexBuffer->Release()))
		{
			Log::Instance()->LogMessage("~RendererDx - Failed to release indexbuffer!", Log::MESSAGE_WARNING);
			
		}
	}
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

	D3DDISPLAYMODE d3dmm;
	if (FAILED(_direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3dmm)))
	{
		return false;
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
		return false;
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
void RendererDx::ClearBuffer(int r, int g, int b)
{
	if (FAILED(_direct3DDevice->Clear(0, NULL, D3DCLEAR_TARGET /*| D3DCLEAR_ZBUFFER,*/, D3DCOLOR_XRGB(200, 200, 200), 1.0f, 0)))
	{
		Log::Instance()->LogMessage("RendererDx - Unable to clear buffer.", Log::MESSAGE_INFO);
	}
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Creates the vertex buffer.
Parameters:
[in] pDevice - Pointer to IDirect3DDevice9
[in] numVertices - Max number of vertices allowed in the buffer
[in] FVF - Flexible Vertex Format
[in] vertexSize - Size of the vertex structure
[in] dynamic - TRUE for dynamic buffer, FALSE for static buffer
Returns: TRUE on success, FALSE on failure
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool RendererDx::CreateVertexBuffer(unsigned int numVertices, unsigned int vertexSize, unsigned long fvf, HANDLE handle, bool dynamic)
{
	// Create the vertex buffer. Here we are allocating enough memory
	// (from the default pool) to hold all our 3 custom vertices. We also
	// specify the FVF, so the vertex buffer knows what data it contains.
	_vertexSize = vertexSize;
	_fvf = fvf;
	// Dynamic buffers can't be in D3DPOOL_MANAGED
	D3DPOOL pool = dynamic ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED;
	DWORD usage = dynamic ? D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC : D3DUSAGE_WRITEONLY;
	if (FAILED(_direct3DDevice->CreateVertexBuffer(numVertices*vertexSize, usage, fvf, static_cast<D3DPOOL>(pool), &_vertexBuffer, NULL)))
	{
		Log::Instance()->LogMessage("RendererDx - Failed to create vertexbuffer", Log::MESSAGE_ERROR);

		return false;
	}
	Log::Instance()->LogMessage("RendererDx - Vertexbuffer is created", Log::MESSAGE_INFO);
	return true;
}
void RendererDx::CreateIndexBuffer(unsigned int numIndices, unsigned long format, HANDLE handle, bool dynamic) {

	D3DPOOL pool = dynamic ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED;
	unsigned int size = (format == D3DFMT_INDEX32) ? sizeof(unsigned int) : sizeof(unsigned short);
	DWORD usage = dynamic ? D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC : D3DUSAGE_WRITEONLY;
	unsigned int length = numIndices*size;

	if (FAILED(_direct3DDevice->CreateIndexBuffer(length, usage, static_cast<D3DFORMAT>(format), pool, &_indexBuffer, NULL)))
	{
		Log::Instance()->LogMessage("RendererDx - Failed to create vertexbuffer", Log::MESSAGE_ERROR);

	}
}
/// <summary>
/// Gets the vertex buffer.
/// </summary>
/// <returns></returns>
void* RendererDx::GetVertexBuffer()
{
	return _vertexBuffer;
}

void RendererDx::SetIndices() {
	if (_indexBuffer) {
		_direct3DDevice->SetIndices(_indexBuffer);
	}
	else {
		_direct3DDevice->SetIndices(NULL);
	}
}

void* RendererDx::GetIndexBuffer()
{
	return _indexBuffer;
}

void RendererDx::FillIndexBuffer(unsigned int numIndices, void *pIndices, unsigned long flags)
{

	if (_indexBuffer == NULL)
	{
		Log::Instance()->LogMessage("RendererDx - Indexbuffer is null", Log::MESSAGE_ERROR);

	}

	char *pData;

	D3DINDEXBUFFER_DESC desc;
	_indexBuffer->GetDesc(&desc);
	unsigned int size = (desc.Format == D3DFMT_INDEX32) ? sizeof(unsigned int) : sizeof(unsigned short);

	// Lock the index buffer
	if (FAILED(_indexBuffer->Lock(0, 0, (void**)&pData, flags)))
	{
		Log::Instance()->LogMessage("RendererDx - Failed to lock indexbuffer", Log::MESSAGE_ERROR);
	}

	memcpy(pData, pIndices, numIndices * size);

	// Unlock index buffer
	if (FAILED(_indexBuffer->Unlock()))
	{

		Log::Instance()->LogMessage("RendererDx - Failed to unlock indexbuffer", Log::MESSAGE_ERROR);
	}


}

/// <summary>
/// Draws the primitive.
/// </summary>
void RendererDx::DrawIndexedPrimitive(unsigned int primitiveType, unsigned int baseVertexIndex, unsigned int minVertexIndex, unsigned int numberOfVertices, unsigned int startIndex, unsigned int primitiveCount)
{
	if (_indexBuffer) {
		if (FAILED(_direct3DDevice->DrawIndexedPrimitive(
			static_cast<D3DPRIMITIVETYPE>(primitiveType),
			baseVertexIndex,
			minVertexIndex,
			numberOfVertices,
			startIndex,
			primitiveCount))) {
			Log::Instance()->LogMessage("RendererDx - Failed to draw indexed primitive", Log::MESSAGE_ERROR);
		}
	}
	else {
		_direct3DDevice->DrawPrimitive(static_cast<D3DPRIMITIVETYPE>(primitiveType), 0, primitiveCount);
	}
}

void RendererDx::DrawPrimitive(unsigned int primitiveType, unsigned int startVertex, unsigned int primitiveCount)
{

	if (FAILED(_direct3DDevice->DrawPrimitive(
		static_cast<D3DPRIMITIVETYPE>(primitiveType),
		startVertex,
		primitiveCount))) {
		Log::Instance()->LogMessage("RendererDx - Failed to draw primitive", Log::MESSAGE_ERROR);
	}
}

//-----------------------------------------------------------------------------
// Name: DrawSubset()
// Desc: Draw the mesh subset for 1 material
//-----------------------------------------------------------------------------
void RendererDx::DrawSubset(void* mesh, unsigned int index)
{
	if FAILED(DIRECT3DMESH(mesh)->DrawSubset(index))
	{
		Log::Instance()->LogMessage("RendererDx - The subset could not be drawn with number: ", Log::MESSAGE_ERROR);
	}
}

void RendererDx::SetTransform(unsigned int transformStateType, Matrix* matrix) {

	_direct3DDevice->SetTransform(
		static_cast<D3DTRANSFORMSTATETYPE>(transformStateType),
		reinterpret_cast<D3DXMATRIX*>(matrix)); 
}

/// <summary>
/// Sets the stream source.
/// </summary>
void RendererDx::SetStreamSource(unsigned int streamNumber, unsigned int offsetInBytes, unsigned int stride)
{
	if (FAILED(_direct3DDevice->SetStreamSource(
		streamNumber,
		_vertexBuffer,
		offsetInBytes,
		stride))) {
		Log::Instance()->LogMessage("RendererDx - Failed to set the streamsource ", Log::MESSAGE_WARNING);
	}
	
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
void RendererDx::SetMaterial(void* material, unsigned int index)
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
void RendererDx::SetTexture(void* texture, unsigned int index)
{

	if (FAILED(_direct3DDevice->SetTexture(0, DIRECT3DTEXTURE(texture)[index])))
	{
		Log::Instance()->LogMessage("RendererDx - Texture was failed to set to the direct3DDevice", Log::MESSAGE_ERROR);
	}

}

/// <summary>
/// TODO
/// </summary>
void RendererDx::SetFVF()
{
	if (FAILED(_direct3DDevice->SetFVF(_fvf))){
		Log::Instance()->LogMessage("RendererDx - Failed to set the FVF", Log::MESSAGE_WARNING);
	}
	
}

/// <summary>
/// Used to present the backbuffer to the frontbuffer for the device.
/// </summary>
void RendererDx::Present(HWND hWnd)
{
	_direct3DDevice->Present(NULL, NULL, hWnd, NULL);
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Fill up the vertex buffer
Parameters:
[in] numVertices - Number of vertices being put in the buffer.
[in] pVertices - Pointer to the vertex data
[in] flags - Lock flags
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool RendererDx::FillVertexBuffer(unsigned int numVertices, void *pVertices, unsigned long flags)
{
	if (_vertexBuffer == NULL)
	{
		Log::Instance()->LogMessage("RendererDx - There is no vertexbuffer", Log::MESSAGE_ERROR);
		return false;
	}

	char *pData;
	// Lock the vertex buffer
	if (FAILED(_vertexBuffer->Lock(0, 0, (void**)&pData, flags)))
	{
		Log::Instance()->LogMessage("RendererDx - IDirect3DVertexBuffer9::Lock failed", Log::MESSAGE_ERROR);
		return false;
	}

	// Copy vertices to vertex buffer
	memcpy(pData, pVertices, numVertices * _vertexSize);

	// Unlock vertex buffer
	if (FAILED(_vertexBuffer->Unlock()))
	{
		Log::Instance()->LogMessage("RIDirect3DVertexBuffer9::Unlock failed", Log::MESSAGE_ERROR);
		return false;
	}

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