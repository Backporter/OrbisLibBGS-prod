#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	struct PositionPlayerEvent
	{
	public:
		enum class EVENT_TYPE
		{
			kPre = 0,
			kPreUpdatePackages = 1,
			kPostUpdatePackages = 2,
			kPost = 3,
			kFinish = 4
		};
	public:
		uint32_t type;
	};
	static_assert(sizeof(PositionPlayerEvent) == 0x4);
}