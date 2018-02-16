#include "Texture.h"

/// <summary>
/// Finalizes an instance of the <see cref="Texture"/> class.
/// </summary>
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