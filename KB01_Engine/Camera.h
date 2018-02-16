#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Renderer.h"
#include "Entity.h"
class Camera: public Entity
{
public:
	Camera();
	~Camera(void);
	D3DXVECTOR3  m_right;
	D3DXVECTOR3 cameraUpVector;
	D3DXVECTOR3  cameraTarget;
	D3DXVECTOR3  cameraPosition;


	void SetCamera(Renderer* _renderer);//--转换和和摄影机的设置 

};


#endif

