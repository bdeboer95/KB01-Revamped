#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Renderer.h"
#include "Entity.h"

class Camera : public Entity
{
public:
	Camera();
	~Camera(void);
	VECTOR3	m_right;
	VECTOR3	cameraUpVector;
	VECTOR3  cameraTarget;
	VECTOR3  cameraPosition;

	void SetCamera(Renderer* _renderer);
};




#endif

