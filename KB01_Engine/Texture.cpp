#include "Texture.h"

Texture::Texture(std::string _fileName)
{
	fileName = _fileName;
}

Texture::~Texture()
{
	
}

void Texture::SetTextures(void* _meshTextures)
{
	meshTextures = _meshTextures;
}

void* Texture::GetTextures()
{
	return meshTextures;
}
void Texture::SetWidth(int _width)
{
	width = _width;
}
void Texture::SetHeight(int _height)
{
	height = _height;
}

int Texture::GetWidth()
{
	return width;
}
int Texture::GetHeight()
{
	return height;
}
void Texture::Cleanup()
{
	//TODO
}