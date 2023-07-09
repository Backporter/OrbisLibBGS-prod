#include "Logger.h"

namespace Logger
{
	Relocation<uint32_t(*)(void*, const char*)> LOGVM("SkyrimScript::Logger:Write", 0xABEC80);

	uint32_t Write(void* a_this, const char* msg)
	{
		if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->EnableVirtualMachineLog)
		{
			xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kDebug, "[BSScript::Internal::VirtualMachine sent] [%s]", msg);
		}

		return LOGVM(a_this, msg);
	}
}