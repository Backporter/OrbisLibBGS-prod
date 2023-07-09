#pragma once

#include "../B/BSTArray.h"
#include "../B/BSTEvent.h"
#include "../B/BSTHashMap.h"
#include "../B/BSTTuple.h"

namespace ConsoleRE
{
	class TESQuest;
	struct TESQuestStageItemDoneEvent;

	class BGSStoryTeller : public BSTEventSink<TESQuestStageItemDoneEvent>
	{
	public:
		~BGSStoryTeller() override;

		// override (BSTEventSink<TESQuestStageItemDoneEvent>)
		BSEventNotifyControl ProcessEvent(const TESQuestStageItemDoneEvent* a_event, BSTEventSource<TESQuestStageItemDoneEvent>* a_eventSource) override;
		
		static BGSStoryTeller* GetSingleton();
	public:
		BSTArray<TESQuest*>                                             queuedStartQuests;
		BSTArray<TESQuest*>                                             runningQuests;
		BSTArray<TESQuest*>                                             queuedStopQuests;
		BSTArray<TESQuest*>                                             infoClearQuests;
		BSTArray<TESQuest*>                                             helloTopicQuests;
		BSTArray<TESQuest*>                                             greetingTopicQuests;
		bool                                                            startUpQuestsInitialized;
		uint8_t															padA1;
		uint16_t														padA2;
		BSTHashMap<uint32_t, BSTArray<BSTTuple<uint32_t, uint32_t>>*>	questStageWaitMap;
	};
	static_assert(sizeof(BGSStoryTeller) == 0x90);
}