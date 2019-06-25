#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "Entity.h"

class Renderer;
class Camera : public Entity //should camera be an entity? TODO
{
public:
	Camera();
	~Camera(void);

	void					SetCamera(Renderer* _renderer);
};

#endif


