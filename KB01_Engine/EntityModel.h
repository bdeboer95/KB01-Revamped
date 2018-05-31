#ifndef __ENTITYMODEL_H__
#define __ENTITYMODEL_H__

#include "Entity.h"
#include "InputListener.h"

class EntityModel : public InputListener, public Entity
{
public:
	EntityModel(std::string meshLocation, std::string textureLocation, float positionX, float positionY, float positionZ);
	~EntityModel();

	void				SetRotation(int rotation);
	int					GetRotation();

	virtual void		Render(Renderer* renderer);
	virtual void		SetupMatrices();
	virtual bool		InitGeometry(Renderer* renderer, ResourceManager* resourceManager);
	virtual void		Notify(TRANSFORMATIONEVENT transformationEvent, float x = 0, float y = 0);
};

#endif
