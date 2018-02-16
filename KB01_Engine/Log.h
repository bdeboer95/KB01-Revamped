#ifndef __LOG_H__
#define __LOG_H__

#include <string>
#include <fstream>
#include <time.h>

class Log
{
private:	
	Log(); 	// To ensure the Log class cannot be made by another class.
	std::fstream fs;
	static Log* instancePtr;
	std::string GetOperatingSystem();
	std::string GetDirectory();
	std::string GetCurrentDateAndTime();
	std::string GetCurrentUser();

public:
	enum MessageType
	{
		MESSAGE_ERROR,
		MESSAGE_WARNING,
		MESSAGE_INFO
	};

	static Log* Instance(); //note bij KD
	void OpenLogFile(std::string _file);
	void CloseLogFile();
	void LogMessage(std::string message, MessageType kind);
};

#endif