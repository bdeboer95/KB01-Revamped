//#ifndef __CAMERA_H__
//#define __CAMERA_H__
//
//#include "Renderer.h"
//#include "Entity.h"
//
//class Camera : public Entity
//{
//public:
//	Camera();
//	~Camera(void);
//	DXVector3 m_right = DXVector3(0.0f, 0.0f, 0.0f);
//	DXVector3 cameraUpVector = DXVector3(0.0f, 0.0f, 0.0f);
//	DXVector3 cameraTarget = DXVector3(0.0f, 0.0f, 0.0f);
//	DXVector3 cameraPosition = DXVector3(0.0f, 0.0f, 0.0f); //todo make this abstract
//
//	void SetCamera(Renderer* _renderer);
//};
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Renderer.h"
#include "Entity.h"

class Camera : public Entity
{
public:
	Camera();
	~Camera(void);

	void SetCamera(Renderer* _renderer);
};

#endif


