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
	WindowManager*			windowManager;																			//The manager that handles all the windows that contain the scenes of the game
	SceneManager*			sceneManager;																			//the manager that handles all the scenes that contain the entities of the game
	ResourceManager*		resourceManager;																		//the manager that loads the resources
	InputManager*			inputManager;                                                                          
	Renderer*				renderer;

public:
	Kernel();
	~Kernel();

	void					Init();
	void					LoadLevel(const std::string &_level);
	bool					Run();
	void					Step();
	virtual void			Notify(TRANSFORMATIONEVENT transformationEvent,float x = 0, float y = 0);
	void					CleanUp(); //Delete all pointers and/or variables that can cause memory leaks
};
#endif