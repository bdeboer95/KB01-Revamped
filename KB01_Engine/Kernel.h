#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "InputListener.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "RendererDx.h"

class Kernel : public InputListener
{
private:
	WindowManager*			windowManager;
	SceneManager*			sceneManager;
	ResourceManager*		resourceManager;
	InputManager*			inputManager;
	Renderer*				renderer;

	void					DeleteAllManagers();

public:
	Kernel();
	~Kernel();

	void					Init();
	void					LoadLevel(const std::string &_level);
	bool					Run();
	void					Step();
	virtual void			Notify(TRANSFORMATIONEVENT transformationEvent,float x = 0, float y = 0);
};
#endif