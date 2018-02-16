#ifndef __ENTITYMODEL_H__
#define __ENTITYMODEL_H__

#include "Mesh.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "InputListener.h"
#include "Entity.h"

class EntityModel: public InputListener, public Entity
{
private:
	Texture*			texture;
	int					rotation; //float
	float				positionX;
	float				positionY;
	float				positionZ;
	float				rotationX;
	float				rotationY;
	float				rotationZ;
	std::string			fileName;

public:
	Mesh*				mesh;

						EntityModel(std::string _fileName, std::string _textureName,float _positionX, float _positionY, float _positionZ);
						~EntityModel();

	void				ChangeRotation(Renderer* _renderer);
	void				SetupMatrices(Renderer* _renderer);
	void				SetRotation(int _rotation);
	int					GetRotation();
	virtual void		Notify(byte _state[]);
	HRESULT				InitGeometry(ResourceManager* _resourceManager);
	void				Render(Renderer* _renderer);	
};
	
#endif
