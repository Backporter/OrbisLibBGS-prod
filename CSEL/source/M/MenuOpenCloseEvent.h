#pragma once

#include "../B/BSFixedString.h"

namespace ConsoleRE
{
	class MenuOpenCloseEvent
	{
	public:
		BSFixedString menuName;
		bool		  opening;
		uint8_t		  pad09;
		uint16_t	  pad0A;
		uint32_t	  pad0C;
	};
	static_assert(sizeof(MenuOpenCloseEvent) == 0x10);
}