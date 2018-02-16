#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "RendererDx.h"
#include "Scene.h"
#include <vector>
#include "Log.h"

class Window
{
private:
	HWND					hWnd;
	std::vector<Scene*>		scenes;
	RECT					rectangle; //this is the rectangle representation of the window on the screen
	std::string				title;
	WNDCLASSEX				windowClassEx;

	void					CreateHandler();
	std::wstring			StrToWStr(std::string str);

public:
	Window(RECT _rectangle, std::string _title, WNDCLASSEX _windowClassEx);
	~Window();
	RECT					GetRectangleBackBuffer(Renderer* _renderer);
	HWND					GetHandler();
	std::string				GetTitle(); //UPDATE IN KD
	void					AddScene(Scene* scene);
	void					CheckMessages();

};


#endif