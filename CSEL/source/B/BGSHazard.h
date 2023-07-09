#pragma once
#include "../T/TESBoundObject.h"
#include "../T/TESFullName.h"
#include "../T/TESModel.h"
#include "../B/BGSPreloadable.h"
#include "../T/TESImageSpaceModifiableForm.h"

namespace ConsoleRE
{
	struct BGSHazardData
	{
	public:
		enum class BGSHazardFlags
		{
			kNone = 0,
			kPCOnly = 1 << 0,
			kInheritDuration = 1 << 1,
			kAlignToNormal = 1 << 2,
			kInheritRadius = 1 << 3,
			kDropToGround = 1 << 4
		};
	public:
		uint32_t				limit;             // 00
		float                   radius;            // 04
		float                   lifetime;          // 08
		float                   imageSpaceRadius;  // 0C
		float                   targetInterval;    // 10
		uint32_t				flags;             // 14
		SpellItem*              spell;             // 18
		TESObjectLIGH*          light;             // 20
		BGSImpactDataSet*       impactDataSet;     // 28
		BGSSoundDescriptorForm* sound;             // 30
	};
	static_assert(sizeof(BGSHazardData) == 0x38);

	// 0xB0
	class BGSHazard : public TESBoundObject, public TESFullName, public TESModel, public BGSPreloadable, public TESImageSpaceModifiableForm
	{
	public:
		static constexpr int TypeID = 51;
		
		~BGSHazard() override;
	public:
		BGSHazardData data;
	};
	static_assert(sizeof(BGSHazard) == 0xB0);
}