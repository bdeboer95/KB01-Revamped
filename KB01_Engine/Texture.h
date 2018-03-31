#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Resource.h"

class Texture : public Resource
{
	//In renderer zit een API-specifieke vertaler voor de resources
private:
	void* meshTextures;

	int width;
	int height;

public:
	Texture(std::string _fileName);
	~Texture();

	virtual void			Cleanup();

	void					SetTextures(void* _meshTextures);
	void*					GetTextures();

	int						GetWidth();
	int						GetHeight();

	void					SetWidth(int _width);
	void					SetHeight(int _height);
};
#endif