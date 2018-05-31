#include "TextureDx.h"

TextureDx::TextureDx(char * textureLocation)
{
	_textureLocation = textureLocation;
}

TextureDx::~TextureDx()
{

}

void TextureDx::SetTextures(void* meshTextures)
{
	_meshTextures = meshTextures;
}

void* TextureDx::GetTextures()
{
	return _meshTextures;
}

void TextureDx::SetWidth(int width)
{
	_width = width;
}

void TextureDx::SetHeight(int  height)
{
	_height = height;
}

int TextureDx::GetWidth()
{
	return _width;
}

int TextureDx::GetHeight()
{
	return _height;
}

std::string TextureDx::GetFileName()
{
	return _fileName;
}

void TextureDx::Cleanup()
{
	//TODO
}