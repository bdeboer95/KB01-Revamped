#ifndef __INPUTLISTENER_H__
#define __INPUTLISTENER_H__

#include <Windows.h>


class InputListener
{
public:
	virtual void Notify(byte state[]) = 0;
	//virtual bool Pressed(byte _keyPressed, byte state[]) = 0;
};

#endif