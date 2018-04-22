#ifndef __TEXTURELOADERDX_H__
#define __TEXTURELOADERDX_H__

#include "ResourceLoader.h"
#include "Texture.h"

class TextureLoaderDx : public ResourceLoader
{
private:
	std::vector<Texture> textures;

public:
	TextureLoaderDx(Renderer* _renderer);
	~TextureLoaderDx();

	virtual Texture*			LoadResource(std::string _filePath, std::string _fileName);
	virtual void				Cleanup();
};

#endif