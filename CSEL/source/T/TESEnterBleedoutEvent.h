#pragma once

#include "../N/NiSmartPointer.h"

namespace ConsoleRE
{
	class TESObjectREFR;

	struct TESEnterBleedoutEvent
	{
	public:
		NiPointer<TESObjectREFR> actor;
	public:
	};
}