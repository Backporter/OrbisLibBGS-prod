#pragma once

namespace ConsoleRE
{
	struct BGSActorEvent
	{
	public:
		uint32_t actor;
	};
	static_assert(sizeof(BGSActorEvent));
}