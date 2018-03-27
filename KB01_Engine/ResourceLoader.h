#ifndef __RESOURCELOADER_H__
#define __RESOURCELOADER_H__

#include "Resource.h"
#include "Log.h"
#include "d3dx9.h"

class ResourceLoader
{
protected:
	LPDIRECT3D9				direct3D; // Used to create the D3DDevice
	LPDIRECT3DDEVICE9		direct3DDevice; // Our rendering device
public:
	virtual	~ResourceLoader(){};
	void SetDevice(void* _device);
};

#endif