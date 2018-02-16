#include "ResourceLoader.h"
#include <d3dx9.h>

void ResourceLoader::SetDevice(void* _device)
{
	direct3DDevice = static_cast<LPDIRECT3DDEVICE9>(_device);
}