#pragma once

#include "../B/BGSSceneAction.h"

#include <stdint.h>

namespace ConsoleRE
{
	class TESTopic;

	class BGSSceneActionDialogue : public BGSSceneAction
	{
	public:
		~BGSSceneActionDialogue() override;
	public:
		TESTopic*		topic; // 0x18
		int32_t			headtrackActorID;
		float			loopingMax;
		float			loopingMin;
		uint32_t		unk34;
		uint32_t		emotionType;
		uint32_t		emotionValue;
	};
	static_assert(sizeof(BGSSceneActionDialogue) == 0x38);
}