#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <string>
#include <Windows.h>

class Resource
{
public:
	Resource(std::string _fileName);
	virtual	~Resource() = 0;

	std::string						GetFileName();
	virtual void					Cleanup() = 0;

private:
	std::string					    fileName;
	
};

#endif