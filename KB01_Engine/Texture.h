#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>
#include "Resource.h"

class Texture: public Resource
{
	//In renderer zit een API-specifieke vertaler voor de resources
private:
	
	
	void*	meshTextures;
 int width;
 int height;

public:
						Texture(std::string _fileName) : Resource(_fileName){}
						~Texture();
 void					SetTextures(void* _meshTextures);
 void*					GetTextures();
 virtual void			Cleanup();
 int					GetWidth();
 int					GetHeight();
 void					SetWidth(int _width);
 void					SetHeight(int _height);
};
#endif