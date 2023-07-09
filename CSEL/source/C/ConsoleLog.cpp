#include "../C/ConsoleLog.h"

#include "../../../OrbisUtil/include/Relocation.h"

namespace ConsoleRE
{
	ConsoleLog* ConsoleLog::GetSingleton()
	{
		Relocation<ConsoleLog**> singleton("", 0x30FD680);
		return *singleton;
	}

	bool ConsoleLog::IsConsoleMode()
	{
		__asm volatile ("int3");
	}

	void ConsoleLog::Print(const char* a_fmt, ...)
	{
		va_list args;
		va_start(args, a_fmt);
		VPrint(a_fmt, args);
		va_end(args);
	}

	void ConsoleLog::VPrint(const char* a_fmt, va_list a_args)
	{
		using func_t = decltype(&ConsoleLog::VPrint);
		Relocation<func_t> func("", 0x9E2A60);
		func(this, a_fmt, a_args);
	}
}