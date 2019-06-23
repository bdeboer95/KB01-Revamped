/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 

Title : CTimer.h
Author : Chad Vernon
URL : http://www.c-unit.com

Description : Handles timing and frames per second.

Created :  08/09/2005
Modified : 12/03/2005

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN		    
#define DIRECTINPUT_VERSION 0x0800

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
#include <d3dx9.h>
#include <dinput.h>

#include <ctime>
#include <fstream>
#include "resource.h"

// Useful macros
#define SAFE_RELEASE(x) if( x ) { (x)->Release(); (x) = NULL; }
#define SAFE_DELETE(x) if( x ) { delete(x); (x) = NULL; }
#define SAFE_DELETE_ARRAY(x) if( x ) { delete [] (x); (x) = NULL; }
#define SHOWERROR(s,f,l) char buf[1024]; sprintf( buf, "File: %s\nLine: %d\n%s",f,l,s); MessageBox( 0, buf, "Error", 0 );
#include "CTimer.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
Summary: Default constructor.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
CTimer::CTimer()
{
    QueryPerformanceFrequency( (LARGE_INTEGER *)&m_ticksPerSecond );

    m_currentTime = m_lastTime = m_lastFPSUpdate = 0;
    m_numFrames = 0;
    m_runningTime = m_timeElapsed = m_fps = 0.0f;
    m_FPSUpdateInterval = m_ticksPerSecond >> 1;
    m_timerStopped = TRUE;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
Summary: Starts the timer.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CTimer::Start()
{
    if ( !m_timerStopped )
    {
        // Already started
        return;
    }
    QueryPerformanceCounter( (LARGE_INTEGER *)&m_lastTime );
    m_timerStopped = FALSE;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
Summary: Stops the timer.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CTimer::Stop()
{
    if ( m_timerStopped )
    {
        // Already stopped
        return;
    }
    INT64 stopTime = 0;
    QueryPerformanceCounter( (LARGE_INTEGER *)&stopTime );
    m_runningTime += (float)(stopTime - m_lastTime) / (float)m_ticksPerSecond;
    m_timerStopped = TRUE;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
Summary: Updates the timer. Calculates the time elapsed since the last Update call.
Updates the frames per second and updates the total running time.     
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CTimer::Update()
{
    if ( m_timerStopped )
    {
        return;
    }

    // Get the current time
    QueryPerformanceCounter( (LARGE_INTEGER *)&m_currentTime );
    
    m_timeElapsed = (float)(m_currentTime - m_lastTime) / (float)m_ticksPerSecond;
    m_runningTime += m_timeElapsed;

    // Update FPS
    m_numFrames++;
    if ( m_currentTime - m_lastFPSUpdate >= m_FPSUpdateInterval )
    {
        float currentTime = (float)m_currentTime / (float)m_ticksPerSecond;
        float lastTime = (float)m_lastFPSUpdate / (float)m_ticksPerSecond;
        m_fps = (float)m_numFrames / (currentTime - lastTime);

        m_lastFPSUpdate = m_currentTime;
        m_numFrames = 0;
    }

    m_lastTime = m_currentTime;
}