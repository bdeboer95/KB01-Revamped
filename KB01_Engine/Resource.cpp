#include "Resource.h"
#include "Log.h"

/// <summary>
/// Initializes a new instance of the <see cref="Resource"/> class.
/// </summary>
/// <param name="_fileName">Name of the _file.</param>
Resource::Resource(std::string _fileName)
{
	fileName = _fileName;
	Log::Instance()->LogMessage("Resource - Resource created.", Log::MESSAGE_INFO);
}

/// <summary>
/// Finalizes an instance of the <see cref="Resource"/> class.
/// </summary>
Resource::~Resource()
{
	Cleanup();
	Log::Instance()->LogMessage("~Resource - Resource cleaned up!", Log::MESSAGE_INFO);
}

/// <summary>
/// Gets the name of the file.
/// </summary>
/// <returns></returns>
std::string Resource::GetFileName()
{
	return fileName;
}

/// <summary>
/// Cleanups this instance.
/// </summary>
void Resource::Cleanup()
{
	//TODO
}