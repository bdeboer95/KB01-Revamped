#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\KB01_engine\Log.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace KB01EngineTest
{
	TEST_CLASS(LogTest)
	{
	public:
		
		TEST_METHOD(MessageInfo)
		{
			Log::Instance()->LogMessage("MessageInfo - Test Log", Log::MESSAGE_INFO);
		}
		TEST_METHOD(MessageWarning)
		{
			Log::Instance()->LogMessage("MessageWarning - Test Log", Log::MESSAGE_WARNING);
		}
		TEST_METHOD(MessageError)
		{
			Log::Instance()->LogMessage("MessageError - Test Log", Log::MESSAGE_ERROR);
		}

	};
}