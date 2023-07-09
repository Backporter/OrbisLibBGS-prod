#pragma once

#include "../B/BGSSceneAction.h"

namespace ConsoleRE
{
	class BGSSceneActionTimer : public BGSSceneAction
	{
	public:
		~BGSSceneActionTimer() override;
	public:
		float			timerSeconds;
		uint32_t		unk24;
		uint64_t		unk28;
	};
	static_assert(sizeof(BGSSceneActionTimer) == 0x28);
}