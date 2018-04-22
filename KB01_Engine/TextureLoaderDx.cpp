#include "TextureLoaderDx.h"

#include <Windows.h>
#include "StringToWStringConverter.h"
#include <string>

TextureLoaderDx::TextureLoaderDx(Renderer* _renderer)
{
	renderer = _renderer;

	Log::Instance()->LogMessage("TextureLoaderDx - TextureLoaderDx created.", Log::MESSAGE_INFO);
}

TextureLoaderDx::~TextureLoaderDx()
{
	Log::Instance()->LogMessage("~TextureLoaderDx - TextureLoaderDx cleaned up!", Log::MESSAGE_INFO);

}

Texture* TextureLoaderDx::LoadResource(std::string _filePath, std::string _fileName)
{
	Texture* texture = new Texture(_fileName);

	LPDIRECT3DTEXTURE9* meshTextures = new LPDIRECT3DTEXTURE9();

	StringToWStringConverter converter;
	std::wstring path = converter.Convert(_filePath);
	std::wstring name = converter.Convert(_fileName);
	std::wstring temp = path + name;
	LPCWSTR directory = temp.c_str();

	// Fill LPDIRECT3DTEXTURE9
	if (FAILED(D3DXCreateTextureFromFile(
		static_cast<LPDIRECT3DDEVICE9>(renderer->GetDevice()), 
		directory,
		meshTextures)))
	{
		Log::Instance()->LogMessage("TextureLoaderDx - Failed to load Texture using the direct3Ddevice. Could not find the file." + _fileName, Log::MESSAGE_WARNING);
		return NULL;
	}

	texture->SetTextures(meshTextures);

	return texture;
}

void TextureLoaderDx::Cleanup()
{

}