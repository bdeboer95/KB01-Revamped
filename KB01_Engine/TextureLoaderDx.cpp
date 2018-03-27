#include "TextureLoaderDx.h"
#include "StringToWStringConverter.h"
#include <string>

TextureLoaderDx::TextureLoaderDx()
{
	Log::Instance()->LogMessage("TextureLoaderDx - TextureLoaderDx created.", Log::MESSAGE_INFO);
}


TextureLoaderDx::~TextureLoaderDx()
{
	Log::Instance()->LogMessage("~TextureLoaderDx - TextureLoaderDx cleaned up!", Log::MESSAGE_INFO);

}



Texture* TextureLoaderDx::LoadTexture(std::string _filePath, std::string _fileName)
{
	Texture* texture = new Texture(_fileName);
	LPDIRECT3DTEXTURE9* meshTextures = new LPDIRECT3DTEXTURE9();
	StringToWStringConverter converter;
	std::wstring tempPath = converter.Convert(_filePath);
	std::wstring tempName = converter.Convert(_fileName);
	std::wstring tempResult = std::wstring(tempPath) + std::wstring(tempName);
	LPCWSTR result = tempResult.c_str();

	if (FAILED(D3DXCreateTextureFromFile(direct3DDevice,
		result, meshTextures)))
	{
		Log::Instance()->LogMessage("Skybox - Could not find file: '"+ _filePath + _fileName + "'", Log::MESSAGE_WARNING);
		return NULL;
	}
	texture->SetTextures(meshTextures);
	return texture;
}
