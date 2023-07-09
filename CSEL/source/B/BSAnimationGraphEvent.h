#pragma once

#include "../B/BSFixedString.h"
#include "../T/TESObjectREFR.h"

namespace ConsoleRE
{
	class TESObjectREFR;

	struct BSAnimationGraphEvent
	{
	public:
		BSFixedString  tag;
		TESObjectREFR* holder;
		BSFixedString  payload;
	};
	static_assert(sizeof(BSAnimationGraphEvent) == 0x18);

}