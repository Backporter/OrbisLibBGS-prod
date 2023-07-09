#pragma once

#include "../A/ArmorRatingVisitorBase.h"

namespace ConsoleRE
{
	class ArmorRatingVisitor : public ArmorRatingVisitorBase
	{
	public:
		~ArmorRatingVisitor() override;

		// override (ArmorRatingVisitorBase)
		bool HaveNotVisitedArmor(TESObjectARMO* a_armor) override;
		void VisitArmor(TESObjectARMO* a_armor) override;
	public:
		BSScrapArray<TESObjectARMO*> armors;
	};
	static_assert(sizeof(ArmorRatingVisitor) == 0x38);
}