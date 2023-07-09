#pragma once

#include "../../../../.././../OrbisUtil/include/Logger.h"
#include "../../../../.././../OrbisUtil/include/FileSystem.h"

#include "../../../../../source/G/GFxLog.h"

class GFxLog : public ConsoleRE::GFxLog
{
public:
	GFxLog() : ConsoleRE::GFxLog() 
	{ 
		xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kUserInterfaceLog)->OpenRelitive(1, (char*)"OSEL/GFxLog.txt");
	}

	~GFxLog() override = default;

	void LogMessageVarg(LogMessageType a_messageType, const char* a_fmt, va_list a_argList) override
	{ 
		xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kUserInterfaceLog)->WriteVA((uint32_t)a_messageType, xUtilty::Log::logLevel::kInfo, a_fmt, a_argList);
	}
};
static_assert(sizeof(GFxLog) == 0x18);