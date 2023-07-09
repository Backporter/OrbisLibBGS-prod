#pragma once

#include "../B/BGSDestructibleObjectForm.h"
#include "../B/BGSKeywordForm.h"
#include "../B/BGSPickupPutdownSounds.h"
#include "../T/TESBoundObject.h"
#include "../T/TESFullName.h"
#include "../T/TESModelTextureSwap.h"
#include "../T/TESValueForm.h"
#include "../T/TESWeightForm.h"

namespace ConsoleRE
{
	class TESObjectMISC : 
		public TESBoundObject, 
		public TESFullName, 
		public TESModelTextureSwap, 
		public TESValueForm, 
		public TESWeightForm, 
		public BGSDestructibleObjectForm, 
		public BGSPickupPutdownSounds, 
		public BGSKeywordForm
	{
	public:
		static constexpr int TypeID = 32;
	public:
		~TESObjectMISC() override;

		// override (TESBoundObject)
		bool Load(TESFile* a_mod) override;
		void SaveGame(BGSSaveFormBuffer* a_buf) override;
		void LoadGame(BGSLoadFormBuffer* a_buf) override;
		void InitItemImpl() override;

		// override (BGSKeywordForm)
		BGSKeyword* GetDefaultKeyword() const override;
		
		// add
		virtual void SaveImpl();
		virtual void LoadImpl(TESFile* a_mod, uint32_t a_chunkID);
		virtual void InitImpl();
	public:
	};
	static_assert(sizeof(TESObjectMISC) == 0xD0);
}