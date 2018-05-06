//-----------------------------------------------------------------------------
// File: WindowManager.cpp
//
// Desc: 
//-----------------------------------------------------------------------------

#include "WindowManager.h"

#include <iostream>
#include <vector>
#include <windows.h>

/// <summary>
/// Initializes a new instance of the <see cref="WindowManager"/> class.
/// </summary>
WindowManager::WindowManager()
{
	SetWindowClassEx();
	RegisterClassEx(&windowClassEx); 
	Log::Instance()->LogMessage("WindowManager - Created", Log::MESSAGE_INFO);
}

/// <summary>
/// Finalizes an instance of the <see cref="WindowManager"/> class.
/// </summary>
WindowManager::~WindowManager()
{
	CleanUp();
	Log::Instance()->LogMessage("~WindowManager - WindowManager cleaned up!", Log::MESSAGE_INFO);
}


//-----------------------------------------------------------------------------
// Name: CreateNewWindow()
// Desc: Create a new window
// source check hwnd = NULL: https://msdn.microsoft.com/en-us/library/windows/desktop/ff381409(v=vs.85).aspx
//-----------------------------------------------------------------------------
/// <summary>
/// Creates the new window.
/// </summary>
/// <param name="_rectangle">The _rectangle.</param>
/// <param name="_title">The _title.</param>
Window* WindowManager::CreateNewWindow(RECT _rectangle, std::string _title)
{
	Window* window = new Window(_rectangle, _title, windowClassEx);
	activeWindow = window;
	windows.push_back(window); // Add window to list of windows
	return window;
	Log::Instance()->LogMessage("WindowManager - Window with title: '"+_title+"' created", Log::MESSAGE_INFO);
}

/// <summary>
/// Adds the scenes to window.
/// </summary>
/// <param name="_scenes">The _scenes.</param>
/// <param name="_window">The _window.</param>
void WindowManager::AddScenesToWindow(std::vector<Scene*> _scenes, Window* _window)
{
	for (UINT i = 0; i < _scenes.size(); i++)
	{
		_window->AddScene(_scenes[i]);
	}
	Log::Instance()->LogMessage("WindowManager - Window with title: '" + _window->GetTitle() +"' created", Log::MESSAGE_INFO);
}

/// <summary>
/// Updates the windows.
/// </summary>
void WindowManager::UpdateWindows()
{
	for each(Window* window in windows)
	{
		window->CheckMessages();
	}
}

/// <summary>
/// Deletes the window.
/// </summary>
/// <param name="_hWnd">The _h WND.</param>
void WindowManager::DeleteWindow(HWND _hWnd)
{
	DestroyWindow(_hWnd);

	std::vector<Window*>::iterator it;
	for (it = windows.begin(); it != windows.end();)
	{
		if ((*it)->GetHandler() == _hWnd)
		{
			delete * it;
			it = windows.erase(it);
		}
		else
		{
			++it;
		}
	}

}

/// <summary>
/// Deletes all windows.
/// </summary>
void WindowManager::DeleteAllWindows()
{
	while (!windows.empty())
	{
		Window window = *windows.back();
		DestroyWindow(window.GetHandler());

		delete windows.back();
		windows.pop_back();
	}
}

/// <summary>
/// Cleans up.
/// </summary>
void WindowManager::CleanUp()
{
	UnregisterClass(L"WC", windowClassEx.hInstance);
	DeleteAllWindows();
	Log::Instance()->LogMessage("WindowManager - Cleanup successful.", Log::MESSAGE_INFO);

}

/// <summary>
/// The WindowManager's message handler. 
/// </summary>
/// <param name="_hWnd">The _h WND.</param>
/// <param name="_msg">The _MSG.</param>
/// <param name="_wParam">The _w parameter.</param>
/// <param name="_lParam">The _l parameter.</param>
/// <returns></returns>
LRESULT WINAPI WindowManager::WndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_msg)
	{
	case WM_DESTROY:
		PostQuitMessage(123);
		return 0;
	case WM_CLOSE:
		DestroyWindow(_hWnd);
		break;
	}

	return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
}

/// <summary>
/// The Static WindowManager's message handler. Since the WndProc function is called outside the main.cpp, it requires a static function to point to the correct window handler (ie window);
///	- http://www.directxtutorial.com/Lesson.aspx?lessonid=9-1-3
/// - http://www.experts-exchange.com/questions/20558866/Can-WndProc-come-from-within-a-Class.html
/// </summary>
/// <param name="_hWnd">The _h WND.</param>
/// <param name="_msg">The _MSG.</param>
/// <param name="_wParam">The _w parameter.</param>
/// <param name="_lParam">The _l parameter.</param>
/// <returns></returns>
LRESULT WINAPI WindowManager::StaticWndProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam)
{

	WindowManager* pThis;

	if (_msg == WM_NCCREATE)
	{
		pThis = static_cast<WindowManager*>(reinterpret_cast<CREATESTRUCT*>(_lParam)->lpCreateParams);

		SetLastError(0);
		if (!SetWindowLongPtr(_hWnd, GWL_USERDATA, reinterpret_cast<LONG_PTR>(pThis)))
		{
			if (GetLastError() != 0)
				return FALSE;
		}
	}
	else
	{
		pThis = reinterpret_cast<WindowManager*>(GetWindowLongPtr(_hWnd, GWL_USERDATA));
	}

	if (pThis)
	{
		pThis->WndProc(_hWnd, _msg, _wParam, _lParam);
	}

	return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
}

/// <summary>
/// Sets the window class ex.
/// </summary>
void WindowManager::SetWindowClassEx()
{
	windowClassEx.cbSize = sizeof(WNDCLASSEX);			// The size of the structure. Useless because we're using WNDCLASS
	windowClassEx.style = CS_HREDRAW|CS_VREDRAW;					// Class Styles (CS_*), not to be confused with Window Styles (WS_*) This can usually be set to 0
	windowClassEx.lpfnWndProc = StaticWndProc;			// Pointer to the window procedure for this window class
	windowClassEx.cbClsExtra = 0L;						// Amount of extra data allocated for this class in memory. Usually 0
	windowClassEx.cbWndExtra = 0L;						// Amount of extra data allocated in memory per window of this type. Usually 0
	windowClassEx.hInstance = GetModuleHandle(0);		// Handle to application instance (that we got in the first parameter of WinMain())
	windowClassEx.hIcon = NULL;							// Large (usually 32x32) icon shown when the user presses Alt + Tab
	windowClassEx.hCursor = NULL;						// Cursor that will be displayed over our window
	windowClassEx.hbrBackground = NULL;					// Background Brush to set the color of our window
	windowClassEx.lpszMenuName = NULL;					// Name of a menu resource to use for the windows with this class
	windowClassEx.lpszClassName = L"WC";				// Name to identify the class with
	windowClassEx.hIconSm = NULL;						// Small (usually 16x16) icon to show in the taskbar and in the top left corner of the window. Useless because we're using WNDCLASS
	windowClassEx.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);

	Log::Instance()->LogMessage("WindowManager - SetWindowClassEx successful.", Log::MESSAGE_INFO);
}

/// <summary>
/// Counts the windows.
/// </summary>
/// <returns></returns>
int WindowManager::CountWindows()
{
	return windows.capacity();
}

/// <summary>
/// Gets the active window.
/// </summary>
/// <returns></returns>
Window* WindowManager::GetActiveWindow()
{
	return activeWindow;
}