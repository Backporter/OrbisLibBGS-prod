#pragma once

#include "../B/BGSStoryManagerTreeForm.h"
#include "../T/TESCondition.h"

namespace ConsoleRE
{
	class BGSStoryManagerBranchNode;

	class BGSStoryManagerNodeBase : public BGSStoryManagerTreeForm
	{
	public:
		struct Flags
		{
		public:
			enum class NodeFlag
			{
				kNone = 0,
				kRandom = 1 << 0,
				kWarnIfNoChildQuestStarted = 1 << 1
			};

			enum class QuestFlag
			{
				kNone = 0,
				kDoAllBeforeRepeating = 1 << 0,
				kSharesEvent = 1 << 1,
				kNumQuestsToRun = 1 << 2
			};
		public:
			uint16_t	nodeFlags;
			uint16_t	questFags;
		};
		static_assert(sizeof(Flags) == 0x4);
	public:
		~BGSStoryManagerNodeBase() override;
	public:
		BGSStoryManagerBranchNode* parent;
		BGSStoryManagerNodeBase*   previousSibling;
		uint32_t				   maxQuests;
		Flags                      flags;
		TESCondition               conditions;
	};
}