#pragma once

#include "../B/BGSBipedObjectForm.h"
#include "../B/BGSBlockBashData.h"
#include "../B/BGSDestructibleObjectForm.h"
#include "../B/BGSEquipType.h"
#include "../B/BGSKeywordForm.h"
#include "../B/BGSPickupPutdownSounds.h"
#include "../B/BSTArray.h"
#include "../F/FormTypes.h"
#include "../T/TESBipedModelForm.h"
#include "../T/TESBoundObject.h"
#include "../T/TESDescription.h"
#include "../T/TESEnchantableForm.h"
#include "../T/TESFullName.h"
#include "../T/TESRaceForm.h"
#include "../T/TESValueForm.h"
#include "../T/TESWeightForm.h"

namespace ConsoleRE
{
	class TESObjectARMO : 
		public TESBoundObject, 
		public TESFullName,
		public TESRaceForm, 
		public TESEnchantableForm, 
		public TESValueForm, 
		public TESWeightForm, 
		public BGSDestructibleObjectForm, 
		public BGSPickupPutdownSounds, 
		public TESBipedModelForm, 
		public BGSEquipType, 
		public BGSBipedObjectForm, 
		public BGSBlockBashData, 
		public BGSKeywordForm, 
		public TESDescription
	{
	public:
		static constexpr int TypeID = 26;
	public:
		~TESObjectARMO() override;

		// override (TESBoundObject)
		void     InitializeData() override;
		bool     Load(TESFile* a_mod) override;
		void     SaveGame(BGSSaveFormBuffer* a_buf) override;
		void     LoadGame(BGSLoadFormBuffer* a_buf) override;
		void     InitItemImpl() override;
		TESFile* GetDescriptionOwnerFile() const override;
		void     Copy(TESForm* a_srcForm) override;

		// override (BGSKeywordForm)
		BGSKeyword* GetDefaultKeyword() const override;
	public:
		uint32_t				 armorRating;
		uint32_t				 Unk1AC;
		BSTArray<TESObjectARMA*> armorAddons;
		TESObjectARMO*			 templateArmor;
	};
	static_assert(sizeof(TESObjectARMO) == 0x1C8);
}