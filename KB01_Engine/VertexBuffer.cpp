#include "VertexBuffer.h"
#include "Renderer.h"
#include <cstring>

VertexBuffer::VertexBuffer()
{

}

VertexBuffer::~VertexBuffer()
{
	Release();
}

bool VertexBuffer::CreateBuffer(Renderer* renderer, unsigned int numVertices, unsigned long FVF, unsigned int vertexSize, bool dynamic)
{
	Release();

	_numVertices = numVertices;
	_FVF = FVF;
	_vertexSize = vertexSize;

	// Dynamic buffers can't be in D3DPOOL_MANAGED
	Renderer::POOL pool = dynamic ? renderer->DEFAULT : renderer->MANAGED;
	unsigned long usage = dynamic ? renderer->USAGE_WRITEONLY | renderer->USAGE_DYNAMIC : renderer->USAGE_WRITEONLY;

	//if (FAILED(renderer->CreateVertexBuffer(_numVertices * _vertexSize, usage, _FVF, pool, &_vertexBuffer, NULL)))
	//{
	//	return false;		//SHOWERROR( "CreateVertexBuffer failed.", __FILE__, __LINE__ );
	//}

	return true;
}

bool VertexBuffer::Lock(unsigned int offsetToLock, unsigned int SizeToLock, void ** ppbData, unsigned long Flags)
{
	return false;
}

bool VertexBuffer::Unlock()
{
	return false;
}

void VertexBuffer::Release()
{
	if (_vertexBuffer) 
	{ 
		_vertexBuffer->Release(); 
		_vertexBuffer = nullptr; 
	}

	_numVertices = 0;
	_FVF = 0;
	_vertexSize = 0;
	_indexBuffer = nullptr;	// IndexBuffer is released in CIndexBuffer
}

bool VertexBuffer::SetData(unsigned int numVertices, void* pVertices, unsigned long flags)
{
	if (_vertexBuffer == nullptr)
	{
		return false;
	}

	if (!flags)
	{
		flags = Renderer::LOCK_DISCARD;
	}

	char *pData;
	// Lock the vertex buffer
	if (_vertexBuffer->Lock(0, 0, (void**)&pData, flags))
	{
		//SHOWERROR( "IDirect3DVertexBuffer9::Lock failed.", __FILE__, __LINE__ );
		return false;
	}

	// Copy vertices to vertex buffer
	memcpy(pData, pVertices, numVertices * _vertexSize);

	// Unlock vertex buffer
	if (_vertexBuffer->Unlock())
	{
		//SHOWERROR( "IDirect3DVertexBuffer9::Unlock failed.", __FILE__, __LINE__ );
		return false;
	}

	return true;
}

void VertexBuffer::SetIndexBuffer(IndexBuffer* indexBuffer)
{
	_indexBuffer = indexBuffer;
}

void VertexBuffer::Render(Renderer* renderer, unsigned int numPrimitives, unsigned int primitiveType)
{
}

