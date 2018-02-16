#ifndef __STRINGTOWSTRINGCONVERTER_H__
#define __STRINGTOWSTRINGCONVERTER_H__

#include <string>
#include "Window.h"
#include <iostream>

class StringToWStringConverter
{
public:
	StringToWStringConverter();
	~StringToWStringConverter();
	std::wstring Convert(std::string string);
};

#endif