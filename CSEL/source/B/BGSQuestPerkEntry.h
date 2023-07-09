#pragma once
#include "../B/BGSPerkEntry.h"
#include "../T/TESQuest.h"

namespace ConsoleRE
{
	// 0x20
	class BGSQuestPerkEntry : public BGSPerkEntry
	{
	public:
		BGSQuestPerkEntry();
		virtual ~BGSQuestPerkEntry();
	public:
		TESQuest* quest;
		uint32_t  Unk18;
	};
}