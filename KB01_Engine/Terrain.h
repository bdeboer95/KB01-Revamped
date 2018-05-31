#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "Entity.h"
#include "InputListener.h"

class Renderer;

class Terrain : public InputListener, public Entity
{
public:
	Terrain(char* heightmapLocation, char* textureLocation);
	~Terrain();

private:
	char*				_heightMapLocation;

	//LPDIRECT3DTEXTURE9	_texture;
	unsigned char*		_height;

	unsigned int		_numVertices;
	unsigned int		_numIndices;
	unsigned int		_vertexSize;

	virtual void		Render(Renderer* renderer);
	virtual void		SetupMatrices();
	virtual bool		InitGeometry(Renderer* renderer, ResourceManager* resourceManager);
	void Notify(TRANSFORMATIONEVENT transformationEvent, float x, float y);

};

#endif