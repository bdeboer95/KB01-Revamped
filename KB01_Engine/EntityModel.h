#ifndef __ENTITYMODEL_H__
#define __ENTITYMODEL_H__

#include "Entity.h"
#include "ResourceManager.h"
#include "InputListener.h"

/// <summary>
/// The entitymodel is an entity that contains a mesh and texture
/// </summary>
class EntityModel : public InputListener, public Entity
{
private:
	TextureContainer*		_textureContainer;	//the container containing the texture that will define the looks of an entitymodel
	std::string				_fileName; //the filename of the entitymodel's mesh
	Mesh*					_mesh;
public:
							EntityModel(std::string _fileName, std::string _textureName, float _positionX, float _positionY, float _positionZ, Vector3 scaleVector); //Constructor
							~EntityModel(); //Destructor
	void					SetupMatrices();
	virtual void			Notify(TRANSFORMATIONEVENT transformationEvent, float x = 0, float y = 0);
	HRESULT					InitGeometry(ResourceManager* _resourceManager);
	void					Render(Renderer* _renderer);
};

#endif
