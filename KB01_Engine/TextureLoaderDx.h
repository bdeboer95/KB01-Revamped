#ifndef __TEXTURELOADERDX_H__
#define __TEXTURELOADERDX_H__

#include "ResourceLoader.h"
#include "Texture.h"

class TextureLoaderDx : public ResourceLoader
{
public:
	TextureLoaderDx();
	~TextureLoaderDx();
	Texture* LoadTexture(std::string _filePath, std::string _fileName);
};

#endif