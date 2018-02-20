#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Renderer.h"
#include "Entity.h"

class Camera : public Entity
{
public:
	Camera();
	~Camera(void);
	Vector3	m_right;
	Vector3	cameraUpVector;
	Vector3 cameraTarget;
	Vector3 cameraPosition;

	void SetCamera(Renderer* _renderer);
};

#endif

