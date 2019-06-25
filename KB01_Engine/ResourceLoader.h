#ifndef __RESOURCELOADER_H__
#define __RESOURCELOADER_H__

#include "Resource.h"
#include "Renderer.h"
#include "Log.h"

#include <vector>

class ResourceLoader
{
protected:
	Renderer*				_renderer;			//The renderer that is used to load the resources

public:
	virtual					~ResourceLoader(){}; //Deconstructor
	virtual Resource*		LoadResource(std::string _filePath, std::string _fileName) = 0; //Load a resource from a file path and filename
	virtual void			CleanUp() = 0; //The resourceLoader does not have an implementation for this function, but all his children do
};

#endif