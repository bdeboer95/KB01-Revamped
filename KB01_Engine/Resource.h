#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <string>

class Resource
{
protected:
	std::string						_fileName;

public:
	virtual	~Resource() = 0;

	virtual std::string				GetFileName() = 0;
	virtual void					Cleanup() = 0;
	
};

#endif