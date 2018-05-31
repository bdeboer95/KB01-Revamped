#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Log.h"
#include <Windows.h>
#include <string>

class Matrix;
class Vector3;
class VertexBuffer;
class IndexBuffer;
class MeshDx;

class Renderer
{
public:
	// Primitives supported by draw-primitive API
	typedef enum _PRIMITIVETYPE {
		POINTLIST		= 1,
		LINELIST		= 2,
		LINESTRIP		= 3,
		TRIANGLELIST	= 4,
		TRIANGLESTRIP	= 5,
		TRIANGLEFAN		= 6
	} PRIMITIVETYPE;

	/* Pool types */
	typedef enum _POOL :unsigned long {
		DEFAULT		= 0, //ask Vincent if we should make this 
		MANAGED		= 1,
		SYSTEMMEM	= 2,
		SCRATCH		= 3,
	} POOL;

	virtual					~Renderer() {}
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

	virtual void			CreateIndexBuffer(unsigned int numIndices, unsigned long format, HANDLE handle, bool dynamic = false) = 0;
	virtual void*			GetIndexBuffer() = 0;
	virtual void			FillIndexBuffer(unsigned int numIndices, void *pIndices, unsigned long flags) = 0;
	virtual void			SetIndices() = 0;

	virtual long			CreateMeshFVF(unsigned long numFaces, unsigned long numVertices, unsigned long options, unsigned long FVF, MeshDx* mesh) = 0;

	virtual void			DrawIndexedPrimitive(unsigned int primitiveType, unsigned int baseVertexIndex, unsigned int minVertexIndex, unsigned int numberOfVertices, unsigned int startIndex, unsigned int primitiveCount) = 0;
	virtual void			DrawPrimitive(unsigned int primitiveType, unsigned int startVertex, unsigned int primitiveCount) = 0;
	virtual void			DrawSubset(void* mesh, unsigned int index) = 0;

	virtual void			SetRenderState(unsigned int renderStateType, DWORD state) = 0;
	virtual void			SetTransform(unsigned int transformStateType, Matrix* matrix) = 0; //Updates the Transform based on the state type that was given (World, view, etc) with the provided matrix
	virtual void			SetStreamSource(unsigned int streamNumber, unsigned int offsetInBytes, unsigned int strude) = 0;
	virtual void			SetViewPort(void* viewPort) = 0;
	virtual void			SetMaterial(void* material, unsigned int index) = 0;
	virtual void			SetTexture(void* texture, unsigned int index) = 0;
	virtual void			SetFVF() = 0;

	virtual HRESULT			CreateTextureFromFile(LPWSTR sourceFile, void* texture) = 0;

	virtual void			Present(HWND hwnd) = 0;
	virtual long			BeginScene() = 0;
	virtual void			EndScene() = 0;

	// Overerving enumerations?
	typedef enum _TRANSFORMSTATETYPE {
		VIEW		= 2,
		PROJECTION	= 3,
		TEXTURE0	= 16,
		TEXTURE1	= 17,
		TEXTURE2	= 18,
		TEXTURE3	= 19,
		TEXTURE4	= 20,
		TEXTURE5	= 21,
		TEXTURE6	= 22,
		TEXTURE7	= 23,
		FORCE_DWORD = 0x7fffffff, /* force 32-bit size enum */
		WORLD		= 256
	} TRANSFORMSTATETYPE;

	typedef enum _RENDERSTATETYPE {
		ZENABLE						= 7,    /* D3DZBUFFERTYPE (or TRUE/FALSE for legacy) */
		FILLMODE					= 8,    /* D3DFILLMODE */
		SHADEMODE					= 9,    /* D3DSHADEMODE */
		ZWRITEENABLE				= 14,   /* TRUE to enable z writes */
		ALPHATESTENABLE				= 15,   /* TRUE to enable alpha tests */
		LASTPIXEL					= 16,   /* TRUE for last-pixel on lines */
		SRCBLEND					= 19,   /* D3DBLEND */
		DESTBLEND					= 20,   /* D3DBLEND */
		CULLMODE					= 22,   /* D3DCULL */
		ZFUNC						= 23,   /* D3DCMPFUNC */
		ALPHAREF					= 24,   /* D3DFIXED */
		ALPHAFUNC					= 25,   /* D3DCMPFUNC */
		DITHERENABLE				= 26,   /* TRUE to enable dithering */
		ALPHABLENDENABLE			= 27,   /* TRUE to enable alpha blending */
		FOGENABLE					= 28,   /* TRUE to enable fog blending */
		SPECULARENABLE				= 29,   /* TRUE to enable specular */
		FOGCOLOR					= 34,   /* D3DCOLOR */
		FOGTABLEMODE				= 35,   /* D3DFOGMODE */
		FOGSTART					= 36,   /* Fog start (for both vertex and pixel fog) */
		FOGEND						= 37,   /* Fog end      */
		FOGDENSITY					= 38,   /* Fog density  */
		RANGEFOGENABLE				= 48,   /* Enables range-based fog */
		STENCILENABLE				= 52,   /* BOOL enable/disable stenciling */
		STENCILFAIL					= 53,   /* D3DSTENCILOP to do if stencil test fails */
		STENCILZFAIL				= 54,   /* D3DSTENCILOP to do if stencil test passes and Z test fails */
		STENCILPASS					= 55,   /* D3DSTENCILOP to do if both stencil and Z tests pass */
		STENCILFUNC					= 56,   /* D3DCMPFUNC fn.  Stencil Test passes if ((ref & mask) stencilfn (stencil & mask)) is true */
		STENCILREF					= 57,   /* Reference value used in stencil test */
		STENCILMASK					= 58,   /* Mask value used in stencil test */
		STENCILWRITEMASK			= 59,   /* Write mask applied to values written to stencil buffer */
		TEXTUREFACTOR				= 60,   /* D3DCOLOR used for multi-texture blend */
		WRAP0						= 128,  /* wrap for 1st texture coord. set */
		WRAP1						= 129,  /* wrap for 2nd texture coord. set */
		WRAP2						= 130,  /* wrap for 3rd texture coord. set */
		WRAP3						= 131,  /* wrap for 4th texture coord. set */
		WRAP4						= 132,  /* wrap for 5th texture coord. set */
		WRAP5						= 133,  /* wrap for 6th texture coord. set */
		WRAP6						= 134,  /* wrap for 7th texture coord. set */
		WRAP7						= 135,  /* wrap for 8th texture coord. set */
		CLIPPING					= 136,
		LIGHTING					= 137,
		AMBIENT						= 139,
		FOGVERTEXMODE				= 140,
		COLORVERTEX					= 141,
		LOCALVIEWER					= 142,
		NORMALIZENORMALS			= 143,
		DIFFUSEMATERIALSOURCE		= 145,
		SPECULARMATERIALSOURCE		= 146,
		AMBIENTMATERIALSOURCE		= 147,
		EMISSIVEMATERIALSOURCE		= 148,
		VERTEXBLEND					= 151,
		CLIPPLANEENABLE				= 152,
		POINTSIZE					= 154,   /* float point size */
		POINTSIZE_MIN				= 155,   /* float point size min threshold */
		POINTSPRITEENABLE			= 156,   /* BOOL point texture coord control */
		POINTSCALEENABLE			= 157,   /* BOOL point size scale enable */
		POINTSCALE_A				= 158,   /* float point attenuation A value */
		POINTSCALE_B				= 159,   /* float point attenuation B value */
		POINTSCALE_C				= 160,   /* float point attenuation C value */
		MULTISAMPLEANTIALIAS		= 161,  // BOOL - set to do FSAA with multisample buffer
		MULTISAMPLEMASK				= 162,  // DWORD - per-sample enable/disable
		PATCHEDGESTYLE				= 163,  // Sets whether patch edges will use float style tessellation
		DEBUGMONITORTOKEN			= 165,  // DEBUG ONLY - token to debug monitor
		POINTSIZE_MAX				= 166,   /* float point size max threshold */
		INDEXEDVERTEXBLENDENABLE	= 167,
		COLORWRITEENABLE			= 168,  // per-channel write enable
		TWEENFACTOR					= 170,   // float tween factor
		BLENDOP						= 171,   // D3DBLENDOP setting
		POSITIONDEGREE				= 172,   // NPatch position interpolation degree. D3DDEGREE_LINEAR or D3DDEGREE_CUBIC (default)
		NORMALDEGREE				= 173,   // NPatch normal interpolation degree. D3DDEGREE_LINEAR (default) or D3DDEGREE_QUADRATIC
		SCISSORTESTENABLE			= 174,
		SLOPESCALEDEPTHBIAS			= 175,
		ANTIALIASEDLINEENABLE		= 176,
		MINTESSELLATIONLEVEL		= 178,
		MAXTESSELLATIONLEVEL		= 179,
		ADAPTIVETESS_X				= 180,
		ADAPTIVETESS_Y				= 181,
		ADAPTIVETESS_Z				= 182,
		ADAPTIVETESS_W				= 183,
		ENABLEADAPTIVETESSELLATION	= 184,
		TWOSIDEDSTENCILMODE			= 185,   /* BOOL enable/disable 2 sided stenciling */
		CCW_STENCILFAIL				= 186,   /* D3DSTENCILOP to do if ccw stencil test fails */
		CCW_STENCILZFAIL			= 187,   /* D3DSTENCILOP to do if ccw stencil test passes and Z test fails */
		CCW_STENCILPASS				= 188,   /* D3DSTENCILOP to do if both ccw stencil and Z tests pass */
		CCW_STENCILFUNC				= 189,   /* D3DCMPFUNC fn.  ccw Stencil Test passes if ((ref & mask) stencilfn (stencil & mask)) is true */
		COLORWRITEENABLE1			= 190,   /* Additional ColorWriteEnables for the devices that support D3DPMISCCAPS_INDEPENDENTWRITEMASKS */
		COLORWRITEENABLE2			= 191,   /* Additional ColorWriteEnables for the devices that support D3DPMISCCAPS_INDEPENDENTWRITEMASKS */
		COLORWRITEENABLE3			= 192,   /* Additional ColorWriteEnables for the devices that support D3DPMISCCAPS_INDEPENDENTWRITEMASKS */
		BLENDFACTOR					= 193,   /* D3DCOLOR used for a constant blend factor during alpha blending for devices that support D3DPBLENDCAPS_BLENDFACTOR */
		SRGBWRITEENABLE				= 194,   /* Enable rendertarget writes to be DE-linearized to SRGB (for formats that expose D3DUSAGE_QUERY_SRGBWRITE) */
		DEPTHBIAS					= 195,
		WRAP8						= 198,   /* Additional wrap states for vs_3_0+ attributes with D3DDECLUSAGE_TEXCOORD */
		WRAP9						= 199,
		WRAP10						= 200,
		WRAP11						= 201,
		WRAP12						= 202,
		WRAP13						= 203,
		WRAP14						= 204,
		WRAP15						= 205,
		SEPARATEALPHABLENDENABLE	= 206,  /* TRUE to enable a separate blending function for the alpha channel */
		SRCBLENDALPHA				= 207,  /* SRC blend factor for the alpha channel when D3DRS_SEPARATEDESTALPHAENABLE is TRUE */
		DESTBLENDALPHA				= 208,  /* DST blend factor for the alpha channel when D3DRS_SEPARATEDESTALPHAENABLE is TRUE */
		BLENDOPALPHA				= 209,  /* Blending operation for the alpha channel when D3DRS_SEPARATEDESTALPHAENABLE is TRUE */
	} RENDERSTATETYPE;

	typedef enum CULL {
		CULL_NONE	= 1,
		CULL_CW		= 2,
		CULL_CCW	= 3,
	} CULL;

	typedef enum _MESH {
		// Helper options
		MESH_SYSTEMMEM			= 0x110,	// D3DXMESH_VB_SYSTEMMEM | D3DXMESH_IB_SYSTEMMEM
		MESH_MANAGED			= 0x220,	// D3DXMESH_VB_MANAGED | D3DXMESH_IB_MANAGED
		MESH_WRITEONLY			= 0x440,	// D3DXMESH_VB_WRITEONLY | D3DXMESH_IB_WRITEONLY
		MESH_DYNAMIC			= 0x880,	// D3DXMESH_VB_DYNAMIC | D3DXMESH_IB_DYNAMIC
		MESH_SOFTWAREPROCESSING = 0x18000,	// D3DXMESH_VB_SOFTWAREPROCESSING | D3DXMESH_IB_SOFTWAREPROCESSING
	} MESH;

};

#endif



