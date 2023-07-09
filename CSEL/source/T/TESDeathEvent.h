#pragma once

#include "../N/NiSmartPointer.h"
#include "../T/TESObjectREFR.h"

#include <stdint.h>

namespace ConsoleRE
{
	struct TESDeathEvent
	{
	public:
		NiPointer<TESObjectREFR> actorDying;
		NiPointer<TESObjectREFR> actorKiller;
		bool                     dead;
		uint8_t                  pad11{ 0 };
		uint16_t                 pad12{ 0 };
	};
}