#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Renderer.h"


class Camera 
{
public:
	Camera();
	~Camera(void);

	void SetCamera(Renderer* _renderer);
};

#endif


