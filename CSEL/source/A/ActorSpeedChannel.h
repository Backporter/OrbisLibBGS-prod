#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	template <typename T, typename Y>
	class ActorSpeedChannel
	{
	public:
		uint32_t unk00;
		Y		 val;
		T*		 type;
	};
}