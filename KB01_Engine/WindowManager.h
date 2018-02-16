#ifndef __WINDOWMANAGER_H__
#define __WINDOWMANAGER_H__

#include "RendererDx.h"
#include "Window.h"
#include <vector>
#include <windows.h>

class WindowManager
{
private:
	WNDCLASSEX						windowClassEx;
	Window*							activeWindow; //The current window that the user is using
	std::vector<Window*>			windows; //The list of windows that is currently being displayed on the screen

	static LRESULT WINAPI			StaticWndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);
	LRESULT WINAPI					WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam); 
	void							SetWindowClassEx();  
	Window							GetWindow();
	

public:
	WindowManager();
	~WindowManager();

	Window*							CreateNewWindow(RECT _rect, std::string _title);
	void							UpdateWindows();
	void							AddScenesToWindow(std::vector<Scene*> _scenes, Window* _window);
	void							DeleteWindow(HWND _hWnd); //TODO:new name: DeleteWindowByHandler
	Window*							GetActiveWindow();
	void							DeleteAllWindows();//This needs to be private

private:
	void							CleanUp(); 
	int								CountWindows(); //TODO: remove this if not needed
	
};

#endif

