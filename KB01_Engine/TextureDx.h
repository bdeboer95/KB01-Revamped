#ifndef __TEXTUREDX_H__
#define __TEXTUREDX_H__

#include "Texture.h"

class TextureDx : public Texture
{
public:
	TextureDx(char* textureLocation);
	virtual ~TextureDx();

	virtual std::string		GetFileName();
	virtual void			Cleanup();

	virtual void			SetTextures(void* meshTextures);
	virtual void*			GetTextures();

	virtual int				GetWidth();
	virtual int				GetHeight();

	virtual void			SetWidth(int width);
	virtual void			SetHeight(int height);

};

#endif
