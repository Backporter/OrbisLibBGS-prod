#pragma once

#include "../B/BSTArray.h"
#include "../B/BGSPerkEntry.h"
#include "../T/TESCondition.h"
#include "../T/TESDescription.h"
#include "../T/TESForm.h"
#include "../T/TESFullName.h"

namespace ConsoleRE
{
	struct PerkData
	{
		bool        trait;
		int8_t		level;
		int8_t		numRanks;
		bool        playable;
		bool        hidden;
	};
	static_assert(sizeof(PerkData) == 0x5);

	class BGSPerk : public TESForm, public TESFullName, public TESDescription
	{
	public:
		static constexpr int TypeID = 92;
	public:
		~BGSPerk() override;

		// override (TESForm)
		void InitializeData() override;
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
	public:
		PerkData                data;
		uint8_t					pad45;
		uint16_t				pad46;
		TESCondition			perkConditions;
		BSTArray<BGSPerkEntry*> perkEntries;
		BGSPerk*				nextPerk;
	};
	static_assert(offsetof(BGSPerk, perkEntries) == 0x50);
	static_assert(sizeof(BGSPerk) == 0x68);
}