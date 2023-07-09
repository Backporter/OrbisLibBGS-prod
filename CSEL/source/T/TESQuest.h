#pragma once

#include "../B/BGSStoryManagerTreeForm.h"
#include "../B/BSAtomic.h"
#include "../B/BSFixedString.h"
#include "../B/BSString.h"
#include "../B/BSTArray.h"
#include "../B/BSTHashMap.h"
#include "../B/BSTList.h"
#include "../N/NiSmartPointer.h"
#include "../T/TESCondition.h"
#include "../T/TESFullName.h"

namespace ConsoleRE
{
	class BGSBaseAlias;

	class TESQuest : public BGSStoryManagerTreeForm, public TESFullName
	{
	public:
		static constexpr int TypeID = 77;
	public:
		~TESQuest() override;

		// override (BGSStoryManagerTreeForm)
		void                                     InitializeData() override;
		void                                     ClearData() override;
		bool                                     Load(TESFile* a_mod) override;
		void                                     SaveGame(BGSSaveFormBuffer* a_buf) override;
		void                                     LoadGame(BGSLoadFormBuffer* a_buf) override;
		void                                     FinishLoadGame(BGSLoadFormBuffer* a_buf) override;
		void                                     Revert(BGSLoadFormBuffer* a_buf) override;
		void                                     InitItemImpl() override;
		const char*                              GetFormEditorID() const override;
		bool                                     SetFormEditorID(const char* a_str) override;
		TESCondition*                            QConditions() override;
		BGSStoryManagerTreeVisitor::VisitControl AcceptVisitor(BGSStoryManagerTreeVisitor& a_visitor) override;

		//
		bool                                     EnsureQuestStarted(bool& a_result, bool a_startNow);
	public:
		BSTArray<void*>				        Unk30;
		uint32_t					        Unk40;
		uint32_t					        Unk44;
		BSTArray<BGSBaseAlias*>		        Unk48;
		BSTHashMap<UnkKey, UnkValue>        Unk58;
		BSTHashMap<UnkKey, UnkValue>        Unk78;
		mutable BSSpinLock			        Unk98;
		uint32_t					        UnkA8;
		uint16_t					        UnkAC;
		uint8_t						        priority;
		uint8_t						        questType;
		uint32_t					        eventID;
		uint32_t					        UnkB4;
		void*								UnkB8;
		void*								UnkC0;
		void*								UnkC8;
		void*								UnkD0;
		void*                               UnkD8;
		void*								UnkE0;
		BSTHashMap<UnkValue, UnkValue>		UnkE8[2];
		BSTArray<void*>						topics[8 - 2];
		BSTArray<void*>						scenes;
		BSTArray<void*>*					textGlobals;
		uint16_t                            currentStage;
		bool                                alreadyRun;
		uint8_t                             Unk1A3;
		uint32_t                            Unk1A4;
		BSString                            formEditorID;
		void*								Unk1B8;
		NiPointer<void*>                    Unk1C0;
		BSTArray<void*>                     Unk1C8;
	};
	static_assert(offsetof(TESQuest, Unk30)			== 0x30, "offsetof(TESQuest, Unk30) != 0x30");
	static_assert(offsetof(TESQuest, Unk48)			== 0x48, "offsetof(TESQuest, Unk48) != 0x48");
	static_assert(offsetof(TESQuest, Unk58)			== 0x58, "offsetof(TESQuest, Unk48) != 0x48");
	static_assert(offsetof(TESQuest, priority)		== 0xAE, "offsetof(TESQuest, priority) != 0xAE");
	static_assert(offsetof(TESQuest, questType)		== 0xAF, "offsetof(TESQuest, questType) != 0xAF");
	static_assert(offsetof(TESQuest, eventID)		== 0xB0, "offsetof(TESQuest, eventID) != 0xB0");
	static_assert(offsetof(TESQuest, formEditorID)	== 0x1A8, "offsetof(TESQuest, formEditorID) != 1A8");
	static_assert(sizeof(TESQuest) == 0x1D8);
}