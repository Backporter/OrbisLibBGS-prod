#pragma once

#include "../C/Color.h"
#include "../D/DecalData.h"
#include "../T/TESForm.h"
#include "../T/TESModel.h"

namespace ConsoleRE
{
	class BGSImpactData : public TESForm, public TESModel
	{
	public:
		struct IMPACT_DATA_DATA
		{
		public:
			enum class Flag
			{
				kNone = 0,
				kNoDecalData = 1 << 0
			};
		public:
			float                                        effectDuration;
			uint32_t									 orient;
			float                                        angleThreshold;
			float                                        placementRadius;
			uint32_t                                     soundLevel;
			uint8_t										 flags;
			uint8_t										 resultOverride;
			uint16_t									 unk16;
		};
		static_assert(sizeof(IMPACT_DATA_DATA) == 0x18);
	public:
		static constexpr int TypeID = 100;
	public:
		IMPACT_DATA_DATA        data;
		BGSTextureSet*          decalTextureSet;
		BGSTextureSet*          decalTextureSet2;
		BGSSoundDescriptorForm* sound1;
		BGSSoundDescriptorForm* sound2;
		BGSHazard*              hazard;
		DecalData               dData;           
	};
}