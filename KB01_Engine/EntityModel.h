#ifndef __ENTITYMODEL_H__
#define __ENTITYMODEL_H__

#include "Entity.h"
#include "ResourceManager.h"
#include "InputListener.h"
#include "Device.h"

class EntityModel: public InputListener, public Entity
{
private:
	Texture*			texture;
	int					rotation; //float remove this
	float				positionX;
	float				positionY;
	float				positionZ;
	float				rotationX;
	float				rotationY;
	float				rotationZ;
	float				speed;
	D3DXMATRIX			matRotateX; //the matrix for the rotation on the x-axis
	D3DXMATRIX			 matRotateY;//the matrix for the rotation on the y-axis
	D3DXMATRIX			 matRotateZ;//the matrix for the rotation on the z-axis
	D3DXMATRIX			 matWorld; //the matrix that contains  the multiplication of all the modification matrices (scale, rotate, translate)
	D3DXMATRIX			 matScale; //the matrix for the scaling of the skybox
	D3DXMATRIX			 matTranslate;
	std::string			fileName;

public:
	Mesh*				mesh;

						EntityModel(std::string _fileName, std::string _textureName,float _positionX, float _positionY, float _positionZ);
						~EntityModel();

	void				ChangeRotation(Renderer* _renderer);
	void				SetupMatrices(Renderer* _renderer);
	void				SetRotation(int _rotation);
	int					GetRotation();
	virtual void		Notify(TRANSFORMATIONEVENT transformationEvent);
	HRESULT				InitGeometry(ResourceManager* _resourceManager);
	void				Render(Renderer* _renderer);	
};
	
#endif
