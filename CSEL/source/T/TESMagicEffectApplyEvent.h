#pragma once

#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class TESObjectREFR;

	struct TESMagicEffectApplyEvent
	{
	public:
		NiPointer<TESObjectREFR> target;
		NiPointer<TESObjectREFR> caster;
		uint32_t                 magicEffect;
		uint32_t				 pad14;
	};
	static_assert(sizeof(TESMagicEffectApplyEvent) == 0x18);
}