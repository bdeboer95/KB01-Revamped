#ifndef __RESOURCELOADER_H__
#define __RESOURCELOADER_H__

#include "Resource.h"
#include "Renderer.h"
#include "Log.h"
#include "XmlReader.h"

#include <vector>

class ResourceLoader
{
protected:
	Renderer*				renderer;

public:
	virtual	~ResourceLoader(){};
	virtual Resource*		LoadResource(std::string _filePath, std::string _fileName) = 0;
	virtual void			Cleanup() = 0;
};

#endif