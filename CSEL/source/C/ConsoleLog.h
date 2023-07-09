#pragma once

#include "../B/BSString.h"

namespace ConsoleRE
{
	class ConsoleLog
	{
	public:
		static ConsoleLog* GetSingleton();
		static bool        IsConsoleMode();

		void Print(const char* a_fmt, ...);
		void VPrint(const char* a_fmt, va_list a_args);
	public:
		char          lastMessage[0x400];  // 001
		uint8_t		  pad401;              // 401
		uint16_t	  pad402;              // 402
		uint32_t	  pad404;              // 404
		BSString      buffer;              // 408
	};
	static_assert(sizeof(ConsoleLog) == 0x418);
}
