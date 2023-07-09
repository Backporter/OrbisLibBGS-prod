#pragma once

#include "../I/InventoryChanges.h"

namespace ConsoleRE
{
	class Actor;

	class ArmorRatingVisitorBase : public InventoryChanges::IItemChangeVisitor
	{
	public:
		bool Visit(InventoryEntryData*) override;
		
		// add
		virtual bool HaveNotVisitedArmor(TESObjectARMO* a_armor);
		virtual void VisitArmor(TESObjectARMO* a_armor);
	public:
		Actor* actor;
		float  armorSum;
		float  armorPerks;
		float  lightArmorRating;
		float  heavyArmorRating;
	};
	static_assert(sizeof(ArmorRatingVisitorBase) == 0x20);
}