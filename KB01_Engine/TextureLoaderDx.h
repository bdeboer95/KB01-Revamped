#ifndef __TEXTURELOADERDX_H__
#define __TEXTURELOADERDX_H__

#include "ResourceLoader.h"
#include "TextureDx.h"

class TextureLoaderDx : public ResourceLoader
{
private:
	std::vector<TextureDx> textures;

public:
	TextureLoaderDx(Renderer* _renderer);
	~TextureLoaderDx();

	virtual TextureDx*			LoadResource(char* _filePath, char* _fileName);
	virtual void				Cleanup();
};

#endif