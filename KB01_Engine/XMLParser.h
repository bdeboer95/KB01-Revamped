#ifndef __XMLPARSER_H__
#define __XMLPARSER_H__

#include <string>
#include <vector>

class XMLParser
{
public:
	XMLParser(); //Constructor
	~XMLParser(); //Destructor
	std::string GetFile(const std::string& fileName); //Get an xml file with a specified filename
	std::vector<std::string> XMLParser::GetData(const std::string& text, const std::string& tag); //Get the data in the xml file from a specific tag
	void StripTags(std::string& text); //Strip the tags in the xml file

};
#endif

