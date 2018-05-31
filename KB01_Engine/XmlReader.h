#ifndef __XMLREADER_H__
#define __XMLREADER_H__

#include <stdio.h>
#include <vector>

class XmlReader
{
public: 
	XmlReader(std::string fileName);	//Constructor
	~XmlReader();						//Destructor

	std::vector<std::string> LoadContents();
	static std::string GetValue(std::string raw, std::string attribute);

private:
	std::string _fileName;
	FILE* _file;

	bool Exist();

};

#endif