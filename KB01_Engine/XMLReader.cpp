#include "XmlReader.h"
#include "Log.h"
#include <sstream>

XmlReader::XmlReader(std::string fileName) : _fileName(fileName.c_str())
{
	if (Exist())
	{
		Log::Instance()->LogMessage("XmlReader - File " + fileName + " registrated.", Log::MESSAGE_INFO);
	}
}

XmlReader::~XmlReader()
{
	delete(_file);
	//delete(_fileName);
}

std::vector<std::string> XmlReader::LoadContents()
{
	// Open stream
	std::fstream stream(_fileName);

	// Copy to a buffer
	std::stringstream buffer(std::string((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>()));

	// Used to store the results  from the buffer and each line
	std::string line;
	std::vector<std::string> result;

	// Compare each tag
	while (std::getline(buffer, line, '\n'))
	{
		if (line.find("Entity"))
		{
			result.push_back(line);
		}
		if (line.find("Skybox") != std::string::npos)
		{
			result.push_back(line);
		}
		if (line.find("Terrain") != std::string::npos)
		{
			result.push_back(line);
		}

		Log::Instance()->LogMessage("XmlReader - Read " + line, Log::MESSAGE_INFO);
	}

	return result;
}

std::string XmlReader::GetValue(std::string raw, std::string attribute)
{
	std::string key = raw.substr(raw.find(attribute));		// Find correct attribute
	std::string temp = key.substr(key.find('='));			// Go to the part after '=' to get the value
	std::string value = temp.substr(0, temp.find(' ', 0));	// Remove everything after value

	value.erase(0, 2);				// Remove special characters in front
	value.erase(value.size() - 1);	// And back

	return value;
}

bool XmlReader::Exist()
{
	if (!fopen_s(&_file, _fileName.c_str(), "rb"))
	{
		fclose(_file);
		return true;
	}

	return false;
}
