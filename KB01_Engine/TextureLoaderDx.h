#ifndef __TEXTURELOADERDX_H__
#define __TEXTURELOADERDX_H__

#include "ResourceLoader.h"
#include "TextureContainer.h"

class TextureLoaderDx : public ResourceLoader
{
private:
	std::vector<TextureContainer> textures;

public:
	TextureLoaderDx(Renderer* _renderer);
	~TextureLoaderDx();

	virtual TextureContainer*	LoadResource(std::string _filePath, std::string _fileName);
	virtual void				CleanUp();
};

#endif