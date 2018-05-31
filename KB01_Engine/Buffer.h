#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "Renderer.h"

class Buffer
{
public:
	virtual bool Lock(unsigned int offsetToLock, unsigned int SizeToLock, void** ppbData, unsigned long Flags) = 0;
	virtual bool Unlock() = 0;
	virtual void Release() = 0;
	virtual bool SetData(unsigned int numVertices, void* pVertices, unsigned long flags) = 0;
};

#endif
