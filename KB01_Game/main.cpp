//-----------------------------------------------------------------------------
// File: main.cpp
//
// Desc: The application's startingpoint. 
//		 
//		 - Declare a new kernel to start your engine with
//		 - Init(ialize) the kernel -> set the managers and create the windows
//		 - Load the first level on the windows
//		 - Set the kernel to "active" by calling Run()
//		 - While the kernel is "active", every step, perform Step()
//-----------------------------------------------------------------------------

#include "Kernel.h"
#include "WindowManagerFacade.h"

/// <summary>
/// Sandboxes this instance.
/// </summary>
void Sandbox()
{
	WindowManagerFacade* wmf = new WindowManagerFacade();

	wmf->CreateNewWindow("test_facade1", 100, 100, 100, 500, 1, 1);
	wmf->UpdateWindows();
}

/// <summary>
/// Noobs this instance.
/// </summary>
void Noob()
{
	Kernel kernel = Kernel();

	kernel.LoadLevel("..\\Assets\\Levels\\level1.txt");

	while (kernel.Run())
	{
		kernel.Step();
	}
}

/// <summary>
/// Mains this instance.
/// </summary>
/// <returns>0 or 1</returns>
int main()
{
	//Sandbox();
	Noob();

	return 0;
}