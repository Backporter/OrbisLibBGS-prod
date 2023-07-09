#pragma once

#include "../B/BGSActorEvent.h"
#include "../B/BSFixedString.h"

namespace ConsoleRE
{
	struct BGSFootstepEvent : public BGSActorEvent
	{
	public:
		uint32_t		pad04;
		BSFixedString	tag;
	};
	static_assert(sizeof(BGSFootstepEvent) == 0x10);
}
