#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "InputListener.h"

#include "WindowManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"

class Kernel : public InputListener
{
private:
	WindowManager*			windowManager;
	InputManager*			inputManager;
	ResourceManager*		resourceManager;
	SceneManager*			sceneManager;
	Renderer*				renderer;

	void					DeleteAllManagers();

public:
	Kernel();
	~Kernel();

	void					Init();
	void					LoadLevel(std::string _level);
	bool					Run();
	void					Step();
	virtual void			Notify(byte state[]);
};
#endif