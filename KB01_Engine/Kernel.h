#ifndef __KERNEL_H__
#define __KERNEL_H__

#include "InputListener.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "RendererDx.h"

/// <summary>
/// The kernel manages all classes that are responsible for the creation of the key elements in the game
/// </summary>
class Kernel : public InputListener
{
private:
	WindowManager*			windowManager;																			// The manager that handles all the windows that contain the scenes of the game
	SceneManager*			sceneManager;																			// The manager that handles all the scenes that contain the entities of the game
	ResourceManager*		resourceManager;																		// The manager that loads the resources
	InputManager*			inputManager;																			// The manager that handles the input devices, such as mouse and keyboard
	Renderer*				renderer;																				// The renderer that draws entities on the scene

public:
							Kernel();																				// Constructor
							~Kernel();																				// Destructor
	void					Init();																					// Initialize all the needed components
	void					LoadLevel(const std::string &_level);													// Load the level through a level file
	bool					Run();																					// Run the application
	void					Step();																					// Step every few seconds so that the game constantly checks for changes and updates
	virtual void			Notify(TRANSFORMATIONEVENT transformationEvent,float x = 0, float y = 0);				// Subscribe to the notify event of an inputlistener to see if any keys have been pressed
	void					CleanUp();																				// Delete all pointers and/or variables that can cause memory leaks
};
#endif