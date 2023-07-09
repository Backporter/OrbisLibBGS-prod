#pragma once

#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class TESObjectREFR;

	enum class ACTOR_COMBAT_STATE
	{
		kNone = 0,
		kCombat = 1,
		kSearching = 2
	};

	struct TESCombatEvent
	{
	public:
		NiPointer<TESObjectREFR>    actor;
		NiPointer<TESObjectREFR>    targetActor;
		uint32_t					State;
		uint32_t                    pad14{ 0 };
	};
	static_assert(sizeof(TESCombatEvent) == 0x18);
}