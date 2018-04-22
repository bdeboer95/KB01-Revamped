#include "StringToWStringConverter.h"

StringToWStringConverter::StringToWStringConverter()
{

}


StringToWStringConverter::~StringToWStringConverter()
{

}

std::wstring StringToWStringConverter::Convert(std::string str)
{
	int length;
	//calculates the length of the input string
	int string_length = static_cast<int>(str.length() + 1);
	//MultiByteToWideChar->Maps a character string to a UTF-16 (wide character) string
	//If we do not map this, the debugger will convert the wstring to chinese 
	//c.str()->Returns a pointer to an array that contains a null - terminated sequence of characters(i.e., a C - string) representing the current value of the string object.
	length = MultiByteToWideChar(CP_ACP, 0, str.c_str(), string_length, 0, 0);
	wchar_t* wide_char = new wchar_t[length];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), string_length, wide_char, length);
	std::wstring wstr(wide_char);

	return wstr;
}