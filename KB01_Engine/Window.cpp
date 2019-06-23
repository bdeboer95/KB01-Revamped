//-----------------------------------------------------------------------------
// File: Window.cpp
//
// Desc: 
//-----------------------------------------------------------------------------

#include "Window.h"

#include <iostream>
#include <string>
#include <vector>
#include "StringTowStringConverter.h"

/// <summary>
/// Initializes a new instance of the <see cref="Window"/> class.
/// </summary>
/// <param name="_rectangle">The _rectangle.</param>
/// <param name="_title">The _title.</param>
/// <param name="_windowClassEx">The _window class ex.</param>
Window::Window(RECT _rectangle, std::string _title, WNDCLASSEX _windowClassEx)
{
	// 100, 100, 500, 500		600, 100, 500, 500		1100, 100, 500, 500
	rectangle = _rectangle;
	title = _title;
	windowClassEx = _windowClassEx;
	CreateHandler();
	Log::Instance()->LogMessage("Window - Window created.", Log::MESSAGE_INFO);
}

/// <summary>
/// Finalizes an instance of the <see cref="Window"/> class.
/// </summary>
Window::~Window()
{
	Log::Instance()->LogMessage("~Window - Window cleaned up!", Log::MESSAGE_INFO);
}

/// <summary>
/// Adds the scene.
/// </summary>
/// <param name="scene">The scene.</param>
void Window::AddScene(Scene* scene)
{
	scenes.push_back(scene);
	Log::Instance()->LogMessage("Window - Succeeded to add a scene to this window", Log::MESSAGE_INFO);
}

/// <summary>
/// Gets the rectangle back buffer.
/// </summary>
/// <returns></returns>
RECT Window::GetRectangleBackBuffer(Renderer* _renderer)
{
	RECT rectangleBackBuffer; //this is the rectangle representation of the backbufffer of the window
	rectangleBackBuffer.top = 0;
	rectangleBackBuffer.left = 0;
	rectangleBackBuffer.right = _renderer->GetBackBufferWidth();
	rectangleBackBuffer.bottom = _renderer->GetBackBufferHeight();

	return rectangleBackBuffer;
}

/// <summary>
/// Checks the messages.
/// </summary>
void Window::CheckMessages()
{
	MSG msg = {};
	if (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//for each(Scene* scene in scenes)
	//{
	//	scene->Render(renderer, hWnd);
	//	
	//}
	////Present the changes to the backbuffer/frontbuffer
	//renderer->Present();
	}

/// <summary>
/// Creates the handler.
/// </summary>
void Window::CreateHandler()
{
	StringToWStringConverter converter;
	std::wstring temp = converter.Convert(title);
	LPCWSTR titleResult = temp.c_str();

	hWnd = CreateWindow(
		L"WC",						// Name of the window class
		titleResult,			   // Title of the window
		WS_OVERLAPPEDWINDOW, 		// Window style
		rectangle.left, 			// X-position of the window
		rectangle.top, 				// Y-position of the window
		rectangle.right, 			// Width of the window
		rectangle.bottom,			// Height of the window
		NULL, 						// Parent window
		NULL,						// Menu
		windowClassEx.hInstance,	// Application handle
		NULL);						// Used with multiple windows, NULL

	Log::Instance()->LogMessage("Window - Created handler for window with title:'" + title + "'", Log::MESSAGE_INFO);
}

std::string	Window::GetTitle()
{
	return title;
}

/// <summary>
/// Gets the handler.
/// </summary>
/// <returns></returns>
HWND Window::GetHandler()
{
	return hWnd;
}
