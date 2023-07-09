#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSString.h"
#include "../B/BSTEvent.h"
#include "../B/BSTList.h"

#include "../N/NiSmartPointer.h"

#include <pthread.h>

namespace ConsoleRE
{
	class TESObjectREFR;

	class BGSDialogueBranch;
	class MenuOpenCloseEvent;
	class TESQuest;
	class TESTopic;
	class TESTopicInfo;
	struct PositionPlayerEvent;

	class MenuTopicManager : public BSTEventSink<MenuOpenCloseEvent>, public BSTEventSink<PositionPlayerEvent>   
	{
	public:
		struct Dialogue
		{
		public:
			BSString                         topicText;
		};
	public:
		~MenuTopicManager() override;

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent*, BSTEventSource<MenuOpenCloseEvent>*);
		
		// override (BSTEventSink<PositionPlayerEvent>)
		BSEventNotifyControl ProcessEvent(const PositionPlayerEvent*, BSTEventSource<PositionPlayerEvent>*);

		NiPointer<TESObjectREFR> GetDialogueTarget();

		static MenuTopicManager* GetSingleton();
	public:
		BSSimpleList<Dialogue*>*        selectedResponseNode;
		BSSimpleList<Dialogue*>*        dialogueList;
		uint64_t					    unk28;
		Dialogue*                       lastSelectedDialogue;
		pthread_mutex_t				    criticalSection;
		void*						    Unk40;
		uint32_t						speaker;
		uint32_t						lastSpeaker;
		TESTopicInfo*                   currentTopicInfo;
		TESTopicInfo*                   lastTopicInfo;
		BSTArray<BGSDialogueBranch*>    blockingBranches;
		BSTArray<BGSDialogueBranch*>    topLevelBranches;
		bool                            isGreetingPlayer;
		bool                            unkB1;
		bool                            isSayingGoodbye;
		bool                            unkB3;
		bool                            unkB4;
		bool                            unkB5;
		bool                            unkB6;
		bool                            unkB7;
		bool                            unkB8;
		bool                            unkB9;
		bool                            unkBA;
		bool                            unkBB;
		uint16_t					    padBC;
		BSTArray<TESTopic*>             unkC0;
	};
}