#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Resource.h"

class Texture : public Resource
{
public:
	virtual ~Texture() = 0;

	virtual std::string		GetFileName() = 0;
	virtual void			Cleanup() = 0;

	virtual void			SetTextures(void* meshTextures) = 0;
	virtual void*			GetTextures() = 0;

	virtual int				GetWidth() = 0;
	virtual int				GetHeight() = 0;

	virtual void			SetWidth(int width) = 0;
	virtual void			SetHeight(int height) = 0;

protected:
	char*					_textureLocation;
	void*					_meshTextures;

	int						_width;
	int						_height;

};
#endif