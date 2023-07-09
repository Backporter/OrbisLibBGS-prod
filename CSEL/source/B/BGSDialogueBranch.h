#pragma once

#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSDialogueBranch : public TESForm
	{
	public:
		static constexpr int TypeID = 115;

		~BGSDialogueBranch() override;
	public:
		uint32_t						 flags;
		uint32_t                         pad24;
		TESQuest*                        quest;
		TESTopic*                        startingTopic;
		uint32_t						 type;
		uint32_t						 pad3C;
	};
}