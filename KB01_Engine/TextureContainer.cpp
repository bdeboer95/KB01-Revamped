#include "TextureContainer.h"

TextureContainer::TextureContainer(std::string fileName)
{
	_fileName = fileName;
}

TextureContainer::~TextureContainer()
{
	CleanUp();
}

void TextureContainer::SetTexture(void* texture)
{
	_texture = texture;
}

void* TextureContainer::GetTexture()
{
	return _texture;
}

void TextureContainer::CleanUp()
{
	delete _texture;
}