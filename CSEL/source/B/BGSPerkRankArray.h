#pragma once

#include "../B/BaseFormComponent.h"

namespace ConsoleRE
{
	class BGSPerk;

	struct PerkRankData
	{
	public:

	public:
		BGSPerk*      perk;
		int8_t		  currentRank;
		uint8_t		  pad09;
		uint16_t	  pad0A;
		uint32_t	  pad0C;
	};
	static_assert(sizeof(PerkRankData) == 0x10);
	class BGSPerkRankArray : public BaseFormComponent
	{
	public:
		~BGSPerkRankArray() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
	public:
		PerkRankData*		perks;
		uint32_t			perkCount;
	};
	static_assert(sizeof(BGSPerkRankArray) == 0x18);
}