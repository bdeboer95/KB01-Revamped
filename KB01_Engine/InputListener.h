#ifndef __INPUTLISTENER_H__
#define __INPUTLISTENER_H__

#include <vector>
#include "TransformationEvent.hpp"

class InputListener
{

public:
	virtual void Notify(TRANSFORMATIONEVENT transformationEvent) = 0;
};



#endif