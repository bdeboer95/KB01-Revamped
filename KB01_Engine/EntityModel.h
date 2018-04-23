#ifndef __ENTITYMODEL_H__
#define __ENTITYMODEL_H__

#include "Entity.h"
#include "ResourceManager.h"
#include "InputListener.h"
#include "Device.h"

class EntityModel: public InputListener, public Entity
{
private:
	Texture*			texture;	//the texture for this entitymodel
	int					rotation;	//float remove this
	float				positionX;	
	float				positionY;
	float				positionZ;
	float				rotationX;
	float				rotationY;
	float				rotationZ;
	float				speed;
	Matrix				matRotateX; //the matrix for the rotation on the x-axis
	Matrix				matRotateY;	//the matrix for the rotation on the y-axis
	Matrix				matRotateZ;	//the matrix for the rotation on the z-axis
	Matrix				matWorld;	//the matrix that contains  the multiplication of all the modification matrices (scale, rotate, translate)
	Matrix				matScale;	//the matrix for the scaling of the skybox
	Matrix				matTranslate; //the translation matrix for the entitymodel
	std::string			fileName; //the filename of the entitymodel's mesh

public:
	Mesh*				mesh;
						EntityModel(std::string _fileName, std::string _textureName,float _positionX, float _positionY, float _positionZ);
						~EntityModel();
	void				ChangeRotation(Renderer* _renderer);
	void				SetupMatrices(Renderer* _renderer);
	void				SetRotation(int _rotation);
	int					GetRotation();
	virtual void		Notify(TRANSFORMATIONEVENT transformationEvent, float x = 0, float y = 0);
	HRESULT				InitGeometry(ResourceManager* _resourceManager);
	void				Render(Renderer* _renderer);	
};
	
#endif
