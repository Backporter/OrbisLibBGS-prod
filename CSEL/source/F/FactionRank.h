#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class TESFaction;

	struct FactionRank
	{
	public:
		TESFaction*   faction;
		int8_t		  rank;
		uint8_t		  pad09;
		uint16_t	  pad0A;
		uint32_t	  pad0C;
	};
}