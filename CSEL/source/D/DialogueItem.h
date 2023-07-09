#pragma once
#include "../B/BSIntrusiveRefCounted.h"

#include "../T/TESQuest.h"
#include "../T/TESTopic.h"
#include "../T/TESTopicInfo.h"

namespace ConsoleRE
{
	class Actor;

	class DialogueItem : public BSIntrusiveRefCounted
	{
	public:
		DialogueItem(TESQuest* a_quest, TESTopic* a_topic, TESTopicInfo* a_topicInfo, Actor* a_speaker)
		{
			// using func_t = void(decltype(this), TESQuest*, TESTopic*, TESTopicInfo*, Actor*);
			// Relocation<func_t*> func("", 0x0);
			// return func(this, a_quest, a_topic, a_topicInfo, a_speaker);
		}
	public:
	};
}