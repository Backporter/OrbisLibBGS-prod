#pragma once

#include "../B/BGSEquipType.h"
#include "../B/BGSDestructibleObjectForm.h"
#include "../B/BGSPickupPutdownSounds.h"
#include "../M/MagicItem.h"
#include "../T/TESWeightForm.h"
#include "../T/TESModelTextureSwap.h"
#include "../B/BGSSoundDescriptorForm.h"

namespace ConsoleRE
{
	class AlchemyItem : public MagicItem, public TESModelTextureSwap, public TESWeightForm, public BGSEquipType, public BGSDestructibleObjectForm, public BGSPickupPutdownSounds
	{
	public:
		static constexpr int TypeID = 46;
		
		enum class AlchemyFlag
		{
			kNone = 0,
			kCostOverride = 1 << 0,
			kFoodItem = 1 << 1,
			kExtendDuration = 1 << 3,
			kMedicine = 1 << 16,
			kPoison = 1 << 17
		};

		struct Data
		{
		public:
			int32_t                                 costOverride;
			uint32_t								flags;
			SpellItem*                              addictionItem;
			float                                   addictionChance;
			uint32_t                                pad14;
			BGSSoundDescriptorForm*                 consumptionSound;
		};
	public:
		~AlchemyItem() override;
	
		// override (MagicItem)
		virtual void                     InitializeData() override;
		virtual void                     ClearData() override;
		virtual void                     InitItemImpl() override;
		virtual MagicSystem::SpellType   GetSpellType() const override;
		virtual MagicSystem::CastingType GetCastingType() const override;
		virtual MagicSystem::Delivery    GetDelivery() const override;
		virtual bool                     IsFood() const override;
		virtual bool                     IsPoison() const override;
		virtual bool                     IsMedicine() const override;
		virtual uint32_t				 GetAssociatedSkill() const override;
		virtual uint32_t				 GetChunkID() override;
		virtual void                     CopyMagicItemData(MagicItem* a_src) override;
		virtual void                     LoadMagicItemChunk(TESFile* a_mod, uint32_t a_chunkID) override;
		virtual const MagicItem::Data*   GetData1() const override;
		virtual MagicItem::Data*         GetData2() override;
		virtual uint32_t				 GetDataSize() const override;
		virtual void                     InitFromChunk(TESFile* a_mod) override;
		virtual void                     InitChunk() override;

		// override (BGSKeywordForm)
		virtual BGSKeyword* GetDefaultKeyword() const override;
	public:
		Data data;
	};
	static_assert(sizeof(AlchemyItem) == 0x120);
}