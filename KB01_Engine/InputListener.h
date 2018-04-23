#ifndef __INPUTLISTENER_H__
#define __INPUTLISTENER_H__

#include <vector>
#include "TransformationEvent.h"

class InputListener
{

public:
	virtual void Notify(TRANSFORMATIONEVENT transformationEvent, float x=0, float y=0) = 0;
};



#endif