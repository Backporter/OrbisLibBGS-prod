#pragma once

#include "../B/BaseFormComponent.h"
#include "../B/BSTList.h"

namespace ConsoleRE
{
	struct ACTOR_AGGRO_RADIUS
	{
		enum
		{
			kWarn,
			kWarnAndAttack,
			kAttack,
			kTotal
		};
	};

	struct AIDATA_GAME
	{
	public:
		bool          aggression1 : 1;
		bool          aggression2 : 1;
		bool          confidence1 : 1;
		bool          confidence2 : 1;
		bool          confidence3 : 1;
		bool          energyLevel1 : 1;
		bool          energyLevel2 : 1;
		bool          energyLevel3 : 1;
		bool          energyLevel4 : 1;
		bool          energyLevel5 : 1;
		bool          energyLevel6 : 1;
		bool          energyLevel7 : 1;
		bool          energyLevel8 : 1;
		bool          morality1 : 1;
		bool          morality2 : 1;
		bool          mood1 : 1;
		bool          mood2 : 1;
		bool          mood3 : 1;
		bool          assistance1 : 1;
		bool          assistance2 : 1;
		bool          aggroRadiusBehaviour : 1;
		bool          pad2_5 : 1;
		bool          pad2_6 : 1;
		bool          pad2_7 : 1;
		uint8_t		  pad3;
		uint16_t	  aggroRadius[ACTOR_AGGRO_RADIUS::kTotal];
		bool          noSlowApproach : 1;
		bool          padA_1 : 1;
		bool          padA_2 : 1;
		bool          padA_3 : 1;
		bool          padA_4 : 1;
		bool          padA_5 : 1;
		bool          padA_6 : 1;
		bool          padA_7 : 1;
		uint8_t  padB;
	};
	static_assert(sizeof(AIDATA_GAME) == 0xC);

	struct PackageList
	{
	public:
		BSSimpleList<TESPackage*> packages;
	};
	static_assert(sizeof(PackageList) == 0x10);

	class TESAIForm : public BaseFormComponent
	{
	public:
		~TESAIForm() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;
	public:
		AIDATA_GAME aiData;
		PackageList aiPackages;
	};
	static_assert(sizeof(TESAIForm) == 0x28);
}