#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class BGSSceneAction
	{
	public:
		virtual ~BGSSceneAction();
	public:
		uint32_t actorID;
		uint16_t startPhase;
		uint16_t endPhase;
		uint32_t flags;
		uint32_t index;
	};
	static_assert(sizeof(BGSSceneAction) == 0x18);
}