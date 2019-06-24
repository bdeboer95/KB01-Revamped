#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <string>

class Resource
{
protected:
	std::string					    _fileName; //the name of the file containing the resource

public:
	virtual							~Resource() {}; //Destructor
	virtual std::string				GetFileName() { return _fileName; } //Get the name of the file containing the resource
	virtual void					CleanUp() = 0; //Delete all variables and or pointers that can cause memory leaks
};

#endif