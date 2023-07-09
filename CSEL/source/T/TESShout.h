#pragma once

#include "../B/BGSEquipType.h"
#include "../B/BGSMenuDisplayObject.h"
#include "../F/FormTypes.h"
#include "../T/TESDescription.h"
#include "../T/TESForm.h"
#include "../T/TESFullName.h"

namespace ConsoleRE
{
	class TESShout : public TESForm, public TESFullName, public BGSMenuDisplayObject, public BGSEquipType, public TESDescription
	{
	public:
		static constexpr int TypeID = 119;
		
		struct VariationIDs
		{
			enum VariationID : uint32_t
			{
				kNone = 0xFFFFFFFF,
				kOne = 0,
				kTwo,
				kThree,
				kTotal
			};
		};
		using VariationID = VariationIDs::VariationID;

		struct Variation
		{
			TESWordOfPower* word;
			SpellItem*      spell;
			float           recoveryTime;
			uint32_t		pad14;
		};
		static_assert(sizeof(Variation) == 0x18);
	public:
		~TESShout() override;

		// override (TESForm)
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
		bool GetKnown() const override;

		// override (BGSEquipType)
		BGSEquipSlot* GetEquipSlot() override;
		void          SetEquipSlot(BGSEquipSlot* a_slot) override;
	public:
		Variation words[VariationIDs::kTotal];
	};
	static_assert(sizeof(TESShout) == 0xA8);
}