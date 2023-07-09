#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	struct LogEvent
	{
	public:
		const char* const errorMsg;
		uint32_t		  severity;
		uint32_t		  pad0C;
	};
	static_assert(sizeof(LogEvent) == 0x10);

}