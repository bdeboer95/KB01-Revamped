#ifndef __VERTEXBUFFER_H__
#define __VERTEXBUFFER_H__

#include "Buffer.h"

class IndexBuffer;

class VertexBuffer : public Buffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	bool CreateBuffer(Renderer* renderer, unsigned int numVertices, unsigned long FVF, unsigned int vertexSize,	bool dynamic = false);
	void Render(Renderer* renderer, unsigned int numPrimitives, unsigned int primitiveType);
	void SetIndexBuffer(IndexBuffer* indexBuffer);

	virtual bool Lock(unsigned int offsetToLock, unsigned int SizeToLock, void** ppbData, unsigned long Flags);
	virtual bool Unlock();
	virtual void Release();
	virtual bool SetData(unsigned int numVertices, void* pVertices, unsigned long flags);

private:
	VertexBuffer*			_vertexBuffer;
	IndexBuffer*			_indexBuffer;
	unsigned int            _numVertices;
	unsigned int            _vertexSize;
	unsigned long           _FVF;
};

#endif