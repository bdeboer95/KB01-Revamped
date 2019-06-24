#include "Log.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <Lmcons.h>
#include "Windows.h"

// Global variable to make sure only ONE instance of Log is made.
Log* Log::instancePtr;

/*
	Sources:
	- fstream
	http://www.cplusplus.com/reference/fstream/fstream/open/
	- __TIME__
	https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html
	- OS Check
	http://stackoverflow.com/questions/5919996/how-to-detect-reliably-mac-os-x-ios-linux-windows-in-c-preprocessor
	-Directory check -The answer from Adam Yaxley	JUN 2 '13 22:03
	http://stackoverflow.com/questions/143174/how-do-i-get-the-directory-that-a-program-is-running-from

	Comments:
	- Each line in a file stored in the Common Log Format has the following syntax:

	user				date					description			status					operating system	directory
	Babita de Boer	[Nov 17 2015 18:40:16]	"This is an error"	"Build not succesful"	Windows             C://Users/bdeboer/Desktop/KB01_Engine.exe
	*/



	/// <summary>
	/// Instances this instance.
	/// </summary>
	/// <returns></returns>
Log* Log::Instance()
{
	if (!instancePtr)
	{
		instancePtr = new Log();
	}

	return instancePtr;
}

/// <summary>
/// Prevents a default instance of the <see cref="Log"/> class from being created.
/// - in  --> File open for reading
///	- out --> File open for writing
///	- app --> Append to existing content
/// </summary>
Log::Log()
{
	fs.open("KB01_Engine_Log.txt", std::fstream::in | std::fstream::out | std::fstream::app);

	std::string dateAndTime = GetCurrentDateAndTime();
	std::string userName = GetCurrentUser();
	std::string operatingSystem = GetOperatingSystem();
	std::string directory = GetDirectory();

	fs << "---------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
	fs << std::left << std::setw(15) << "Username" << std::left << std::setw(30) << "[Date And Time         ]" << std::left << std::setw(25) << "Operating System" << std::left << std::setw(55) << "Directory" << std::endl;
	fs << std::left << std::setw(15) << userName << std::left << std::setw(30) << "[" + dateAndTime + "]" << std::left << std::setw(25) << operatingSystem << std::left << std::setw(55) << directory << std::endl;
	fs << "" << std::endl;
}

/// <summary>
/// Opens the log file.
/// </summary>
/// <param name="_file">The _file.</param>
void Log::OpenLogFile(std::string _file)
{
	fs.open(_file, std::fstream::in | std::fstream::out | std::fstream::app);
}

/// <summary>
/// Closes the log file.
/// </summary>
void Log::CloseLogFile()
{
	fs.close();
}

/// <summary>
/// Logs the message.
/// </summary>
/// <param name="message">The message.</param>
/// <param name="kind">The kind.</param>
void Log::LogMessage(std::string message, MessageType kind)
{
	switch (kind)
	{
	case MESSAGE_ERROR:
		fs << GetCurrentDateAndTime().substr(0, 20) + "ERROR: ";
		fs << message << std::endl;
		break;
	case MESSAGE_WARNING:
		fs << GetCurrentDateAndTime().substr(0, 20) + "WARNING: ";
		fs << message << std::endl;
		break;
	case MESSAGE_INFO:
		fs << GetCurrentDateAndTime().substr(0, 20) + "INFO: ";
		fs << message << std::endl;
		break;
	}
}

/// <summary>
/// Gets the current date and time.
/// </summary>
/// <returns></returns>
std::string Log::GetCurrentDateAndTime()
{
	time_t now = time(0);
	char time[26];
	ctime_s(time, sizeof time, &now);

	return time;
}

/// <summary>
/// Gets the operating system.
/// WIN32	   --> checks if the OS is Windo
///	__linux__ --> checks if the OS is Linux
/// __APPLE__ --> checks if the OS is Apple
/// </summary>
/// <returns></returns>
std::string Log::GetOperatingSystem()
{
#ifdef _WIN32
	return "Windows";
#elif __linux__
	return "Linux";
#elif __APPLE__
	return "Mac";
#endif
}

/// <summary>
/// Gets the directory.
/// tempPath << charPath --> converts the path from char to stringstream (a char can not be returned as a string)
///	_pgmptr				--> global variable that contains the full path to the executable file associated with the process (application)
///	_get_pgmptr			--> gets the value of the pgmptr variable, which in this case is f.e C:\Users\BdeBoer\Source\Workspaces\Workspace\KB01\KB01_Engine\Debug\KB01_Engine.exe
/// </summary>
/// <returns></returns>
std::string Log::GetDirectory()
{
	std::stringstream tempPath;// converts the stringstream object to a string so we can return it
	std::string stringPath;
	CHAR buffer[MAX_PATH];
	char* charPath;
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	return buffer;
}

/// <summary>
/// Gets the current user.
/// </summary>
/// <returns></returns>
std::string Log::GetCurrentUser()
{
	TCHAR name[UNLEN + 1];
	DWORD size = UNLEN + 1;

	if (GetUserName((TCHAR*)name, &size))
	{
		TCHAR* t_string = name;
		std::wstring w_string(t_string); // convert tchar[] to wstring
		std::string string(w_string.begin(), w_string.end()); // convert wstring to string

		return string;
	}
	else
	{
		return "John Doe";
	}
}







