#pragma once

#include "../F/FormTypes.h"
#include "../M/MagicItem.h"
#include "../M/MagicSystem.h"

namespace ConsoleRE
{
	class EnchantmentItem : public MagicItem
	{
	public:
		static constexpr int TypeID = 21;

		class Data
		{
		public:
			int32_t											 costOverride;
			uint32_t										 flags;
			MagicSystem::CastingType                         castingType;
			int32_t											 chargeOverride;
			MagicSystem::Delivery                            delivery;
			MagicSystem::SpellType                           spellType;
			float                                            chargeTime;
			uint32_t										 pad1C;
			EnchantmentItem*                                 baseEnchantment;
			BGSListForm*                                     wornRestrictions;
		};
		static_assert(sizeof(Data) == 0x30);
	public:
		~EnchantmentItem() override;

		// override (MagicItem)
		void									InitializeData() override;
		void									ClearData() override;
		void									InitItemImpl() override;
		MagicSystem::SpellType					GetSpellType() const override;
		void									SetCastingType(MagicSystem::CastingType a_type) override;
		MagicSystem::CastingType				GetCastingType() const override;
		void									SetDelivery(MagicSystem::Delivery a_type) override;
		MagicSystem::Delivery					GetDelivery() const override;
		float									GetChargeTime() const override;
		uint32_t								GetAssociatedSkill() const override;
		uint32_t								GetChunkID() override;
		void									CopyMagicItemData(MagicItem* a_src) override;
		const MagicItem::Data*					GetData1() const override;
		MagicItem::Data*						GetData2() override;
		uint32_t								GetDataSize() const override;
		void									InitFromChunk(TESFile* a_mod) override;
		void									InitChunk() override;
	public:
		Data data;
	};
	static_assert(sizeof(EnchantmentItem) == 0xB0);
}