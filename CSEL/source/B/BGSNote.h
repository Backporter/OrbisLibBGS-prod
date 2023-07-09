#pragma once

#include "../B/BSTList.h"
#include "../T/TESBoundObject.h"
#include "../T/TESModel.h"
#include "../T/TESFullName.h"
#include "../B/BGSPickupPutdownSounds.h"

namespace ConsoleRE
{
	class BGSNote :
		public TESBoundObject,
		public TESModel,
		public TESFullName,
		public BGSPickupPutdownSounds
	{
	public:
		static constexpr int TypeID = 48;
	public:
		~BGSNote() override;

		// override (TESBoundObject)
		void InitializeData() override;
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
		void LoadGame(BGSLoadFormBuffer* a_buf) override;
		void Revert(BGSLoadFormBuffer* a_buf) override;
		void InitItemImpl() override;
		bool Activate(TESObjectREFR* a_targetRef, TESObjectREFR* a_activatorRef, uint8_t a_arg3, TESBoundObject* a_object, int32_t a_targetCount) override;
	public:
		TESTopic*               unk88;
		TESActorBase*           unk90;
		BSSimpleList<TESQuest*> unk98;
		uint64_t				UnkA0;
	};
	static_assert(sizeof(BGSNote) == 0xA0);
}