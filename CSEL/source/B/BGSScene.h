#pragma once

#include "../B/BSTArray.h"
#include "../T/TESCondition.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSSceneAction;

	class BGSScenePhase
	{
	public:
		TESCondition              startConditions;
		TESCondition              completionConditions;
		BGSStoryManagerQuestNode* questNode;
	};
	static_assert(sizeof(BGSScenePhase) == 0x18);

	class BGSScene : public TESForm
	{
	public:
		static constexpr int TypeID = 122;
	public:
		~BGSScene() override;
		
		// override (TESForm)
		void InitializeData() override;
		bool Load(TESFile* a_mod) override;
		void SaveGame(BGSSaveFormBuffer* a_buf) override;
		void LoadGame(BGSLoadFormBuffer* a_buf) override;
		void InitLoadGame(BGSLoadFormBuffer* a_buf) override;
		void Revert(BGSLoadFormBuffer* a_buf) override;
		void InitItemImpl() override;
	public:
		BSTArray<BGSScenePhase*>                                    phases;
		BSTArray<uint32_t>                                          actors;
		BSTArray<uint32_t>											actorFlags;
		BSTArray<uint32_t>											actorProgressionFlags;
		BSTArray<BGSSceneAction*>                                   actions;
		TESQuest*                                                   parentQuest;
		uint32_t													flags;
		uint32_t													padA4;
		TESCondition												conditions;
		uint32_t													unkB0;
		uint32_t													unkB4;
		uint32_t													unkB8;
		uint32_t													unkBC;
		uint32_t													unkC0;
		uint32_t													padC4;
	};
	static_assert(sizeof(BGSScene) == 0xA0);
}