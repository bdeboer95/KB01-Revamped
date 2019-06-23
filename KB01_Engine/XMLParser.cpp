#include "XMLParser.h"
#include <fstream>


XMLParser::XMLParser()
{
}


XMLParser::~XMLParser()
{

}
std::string XMLParser::GetFile(const std::string& filename)
{
	std::string buffer;
	char c;

	std::ifstream in(filename);  
	while (in.get(c)) buffer += c;
	in.close();

	return buffer;
}


//======================================================================


std::vector<std::string> XMLParser::GetData(const std::string& text, const std::string& tag)
{
	std::vector<std::string> collection;
	unsigned int pos = 0, start;

	while (true)
	{
		start = text.find("<" + tag, pos);   if (start == std::string::npos) return collection;
		start = text.find(">", start);
		start++;

		pos = text.find("</" + tag, start);   if (pos == std::string::npos) return collection;
		collection.push_back(text.substr(start, pos - start));
	}
}


//======================================================================


void XMLParser::StripTags(std::string& text)
{
	unsigned int start = 0, pos;

	while (start < text.size())
	{
		start = text.find("<", start);    if (start == std::string::npos) break;
		pos = text.find(">", start);    if (pos == std::string::npos) break;
		text.erase(start, pos - start + 1);
	}
}