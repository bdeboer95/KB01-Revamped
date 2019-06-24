#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Resource.h"

class TextureContainer : public Resource
{
	//In renderer zit een API-specifieke vertaler voor de resources
private:
	void*					_texture;								//the texture that needs to be converted by the renderer depending on directX, openGL or another SDK

public:
							TextureContainer(std::string fileName); //Constructor
							~TextureContainer();					//Destructor
	void					SetTexture(void* texture);				//Set the texture
	void*					GetTexture();							//Get the texture
	virtual void			CleanUp();								//Clean up all the pointers or variables so that there are no memory leaks
};
#endif