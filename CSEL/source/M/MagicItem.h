#pragma once

#include "../B/BGSKeywordForm.h"
#include "../B/BSTArray.h"
#include "../B/BSTSmartPointer.h"
#include "../M/MagicSystem.h"
#include "../T/TESBoundObject.h"
#include "../T/TESFullName.h"

namespace ConsoleRE
{
	class Actor;
	class ActorValueInfo;
	class Character;
	class EffectItem;
	class EffectSetting;
	class QueuedFile;
	class TESModel;
	class TESObjectWEAP;
	struct Effect;

	class MagicItem : public TESBoundObject, public TESFullName, public BGSKeywordForm
	{
	public:
		class PreloadableVisitor
		{
		public:

			// add
			virtual void VisitModel(TESModel* a_model) = 0;
			virtual void VisitWeapon(TESObjectWEAP* a_weapon) = 0;
		};
		static_assert(sizeof(PreloadableVisitor) == 0x8);

		struct SkillUsageData
		{
		public:
			EffectItem*		effect;
			uint32_t		skill;
			float			magnitude;
			bool			custom;
			uint8_t			pad11;
			uint16_t		pad12;
			uint32_t		pad14;
		};
		static_assert(sizeof(SkillUsageData) == 0x18);

		class Data
		{
		public:
			int32_t  costOverride;
			uint32_t flags;
		};
		static_assert(sizeof(Data) == 0x8);
	public:
		~MagicItem() override;
		
		// override (TESBoundObject)
		void InitializeData() override;
		bool Load(TESFile* a_mod) override;
		void InitItemImpl() override;
		bool IsMagicItem() const override;
		void Copy(TESForm* a_srcForm) override;
		bool IsAutoCalc() const override;

		// add
		virtual MagicSystem::SpellType   GetSpellType() const = 0;
		virtual void                     SetCastingType(MagicSystem::CastingType a_type);
		virtual MagicSystem::CastingType GetCastingType() const = 0;
		virtual void                     SetDelivery(MagicSystem::Delivery a_delivery);
		virtual MagicSystem::Delivery    GetDelivery() const = 0;
		virtual bool                     IsValidDelivery(MagicSystem::Delivery a_delivery);
		virtual float                    GetFixedCastDuration() const;
		virtual float                    GetRange() const;
		virtual bool                     IgnoresResistance() const;
		virtual bool                     IgnoreLOS() const;
		virtual bool                     IsFood() const;
		virtual bool                     GetNoAbsorb() const;
		virtual bool                     GetNoDualCastModifications() const;
		virtual bool                     GetSkillUsageData(SkillUsageData& a_data) const;
		virtual bool                     IsPoison() const;
		virtual bool                     IsMedicine() const;
		virtual void                     AdjustCost(float& a_cost, Actor* a_actor) const;
		virtual float                    GetChargeTime() const;
		virtual uint32_t				 GetMaxEffectCount() const;
		virtual uint32_t				 GetAssociatedSkill() const;

		// override (BGSKeywordForm)
		bool HasKeyword(const BGSKeyword* a_keyword) const override;

		// add
		virtual bool                     IsTwoHanded() const;
		virtual uint32_t				 GetChunkID() = 0;
		virtual void                     CopyMagicItemData(MagicItem* a_src) = 0;
		virtual void                     LoadMagicItemChunk(TESFile* a_mod, uint32_t a_chunkID);
		virtual void                     LoadChunkDataPostProcess(TESFile* a_mod);
		virtual const Data*              GetData1() const = 0;
		virtual Data*                    GetData2() = 0;
		virtual uint32_t				 GetDataSize() const = 0;
		virtual void                     InitFromChunk(TESFile* a_mod) = 0;
		virtual void                     InitChunk() = 0;

		//
		Effect* GetCostliestEffectItem(int a_unk1, bool a_unk2 = false);
		float	GetEffectiveMagickaCost(Actor* a_actor);
	public:
		BSTArray<Effect*>				  effects;
		uint32_t						  hostileCount;
		uint32_t						  Unk64;
		EffectSetting*					  avEffectSetting;
		uint32_t						  preloadCount;
		uint32_t						  Unk74;
		BSTSmartPointer<QueuedFile>		  preloadedItem;
	};
	static_assert(sizeof(MagicItem) == 0x80);
}