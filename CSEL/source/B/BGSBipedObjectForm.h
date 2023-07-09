#pragma once

#include "../B/BaseFormComponent.h"

namespace ConsoleRE
{
	struct BIPED_MODEL
	{
	public:
		enum BipedObjectSlot
		{
			kNone = 0,
			kHead = 1 << 0,
			kHair = 1 << 1,
			kBody = 1 << 2,
			kHands = 1 << 3,
			kForearms = 1 << 4,
			kAmulet = 1 << 5,
			kRing = 1 << 6,
			kFeet = 1 << 7,
			kCalves = 1 << 8,
			kShield = 1 << 9,
			kTail = 1 << 10,
			kLongHair = 1 << 11,
			kCirclet = 1 << 12,
			kEars = 1 << 13,
			kDecapitateHead = 1 << 20,
			kDecapitate = 1 << 21,
			kFX01 = 1 << 31
		};

		enum ArmorType
		{
			kLightArmor,
			kHeavyArmor,
			kClothing
		};
	public:
		uint32_t bipedObjectSlots;
		uint32_t armorType;
	};
	static_assert(sizeof(BIPED_MODEL) == 0x8);

	class BGSBipedObjectForm : public BaseFormComponent
	{
	public:
		using ArmorType = BIPED_MODEL::ArmorType;
		using BipedObjectSlot = BIPED_MODEL::BipedObjectSlot;
		using FirstPersonFlag = BIPED_MODEL::BipedObjectSlot;

		~BGSBipedObjectForm() override;
		
		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;

		uint32_t	AddSlotToMask(uint32_t a_slot)
		{
			bipedModelData.bipedObjectSlots |= a_slot;
			return bipedModelData.bipedObjectSlots;
		}

		uint32_t	GetArmorType()
		{
			return bipedModelData.armorType;
		}

		uint32_t	GetSlotMask()
		{
			return bipedModelData.bipedObjectSlots;
		}

		bool		HasPartOf(uint32_t a_flag)
		{
			return (bipedModelData.bipedObjectSlots & a_flag) == a_flag;
		}

		bool		IsClothing()
		{
			return bipedModelData.armorType == ArmorType::kClothing;
		}

		bool		IsHeavyArmor()
		{
			return bipedModelData.armorType == ArmorType::kHeavyArmor;
		}

		bool		IsLightArmor()
		{
			return bipedModelData.armorType == ArmorType::kLightArmor;
		}

		bool		IsShield()
		{
			return (bipedModelData.bipedObjectSlots & BipedObjectSlot::kShield) == BipedObjectSlot::kShield;
		}

		uint32_t	RemoveSlotFromMask(uint32_t a_slot)
		{
			if (a_slot != BipedObjectSlot::kNone) 
			{
				bipedModelData.bipedObjectSlots &= ~a_slot;
			}
			
			return bipedModelData.bipedObjectSlots;
		}

		void		SetSlotMask(uint32_t a_mash)
		{
			bipedModelData.bipedObjectSlots = a_mash;
		}

		void		SetArmorType(uint32_t a_val)
		{
			bipedModelData.armorType = a_val;
		}
	public:
		BIPED_MODEL bipedModelData;
	};
	static_assert(sizeof(BGSBipedObjectForm) == 0x10);
}