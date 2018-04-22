#ifndef __WINDOWMANAGERFACADE_H__
#define __WINDOWMANAGERFACADE_H__

#include "Kernel.h"
#include "WindowManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"

class WindowManagerFacade
{
private:
	Kernel* kernel;
	WindowManager* windowManager;
	SceneManager* sceneManager;
	InputManager* inputManager;
	Renderer* renderer;
	ResourceManager* resourceManager;

	void CreateInput();
	// TODO: CLEANUP VAN POINTERS

public:
	WindowManagerFacade();
	~WindowManagerFacade();
	template <class T> struct access_by;
	template <class T> friend struct access_by;
	void CreateNewWindow(std::string _name, int _top, int _left, int _bottom, int _right, int _amountOfScenes, int _levelIndex);
	void UpdateWindows();

};

#endif