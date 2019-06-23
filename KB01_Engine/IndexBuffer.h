#ifndef __INDEXBUFFER_H__
#define __INDEXBUFFER_H__

#include "Buffer.h"

class IndexBuffer : public Buffer
{
	IndexBuffer();
	~IndexBuffer();

	bool CreateBuffer(Renderer* renderer, unsigned int numVertices, unsigned long FVF, unsigned int vertexSize, bool dynamic = false);
	void SetIndexBuffer(IndexBuffer* pIB);

	virtual bool Lock(unsigned int offsetToLock, unsigned int SizeToLock, void** ppbData, unsigned long Flags);
	virtual bool Unlock();
	virtual void Release();
	virtual bool SetData(unsigned int numVertices, void* pVertices, unsigned long flags);

};

#endif
