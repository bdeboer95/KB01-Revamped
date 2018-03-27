#include "ResourceLoader.h"

void ResourceLoader::SetDevice(void* _device)
{
	direct3DDevice = static_cast<LPDIRECT3DDEVICE9>(_device);
}