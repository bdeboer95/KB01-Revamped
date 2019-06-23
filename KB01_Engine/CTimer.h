/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

Title : CTimer.h
Author : Chad Vernon
URL : http://www.c-unit.com

Description : Handles timing and frames per second.

Created :  08/09/2005
Modified : 12/03/2005

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef CTIMER_H
#define CTIMER_H
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// DirectX Header Files
#include <d3d9.h>
#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\d3dx9.h"
#include <dinput.h>

#include <ctime>
#include <fstream>
#include "resource.h"

// Useful macros
#define SAFE_RELEASE(x) if( x ) { (x)->Release(); (x) = NULL; }
#define SAFE_DELETE(x) if( x ) { delete(x); (x) = NULL; }
#define SAFE_DELETE_ARRAY(x) if( x ) { delete [] (x); (x) = NULL; }
#define SHOWERROR(s,f,l) char buf[1024]; sprintf( buf, "File: %s\nLine: %d\n%s",f,l,s); MessageBox( 0, buf, "Error", 0 );

class CTimer
{
public:
    CTimer();
    void Start();
    void Stop();
    void Update();

    BOOL IsStopped() { return m_timerStopped; }
    float GetFPS() { return m_fps; }
    float GetRunningTime() { return m_runningTime; }
    float GetElapsedTime() { return m_timerStopped ? 0.0f : m_timeElapsed; }

private:
    INT64 m_ticksPerSecond;
    INT64 m_currentTime;
    INT64 m_lastTime;
    INT64 m_lastFPSUpdate;
    INT64 m_FPSUpdateInterval;
    UINT m_numFrames;
    float m_runningTime;
    float m_timeElapsed;
    float m_fps;
    BOOL m_timerStopped;
};
#endif