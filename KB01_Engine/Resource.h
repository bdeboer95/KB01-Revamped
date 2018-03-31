#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <string>

class Resource
{
protected:
	std::string					    fileName;

public:
	virtual	~Resource() {};

	virtual std::string				GetFileName() { return fileName; }
	virtual void					Cleanup() = 0;
	
};

#endif