#pragma once

#include "../B/BGSBodyPartDefs.h"
#include "../B/BSExtraData.h"
#include "../B/BSFixedString.h"
#include "../B/BSTArray.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class TESForm;

	struct DismemberedLimb
	{
		BSTArray<TESForm*>                                         objects;
		uint8_t													   limb;
		bool                                                       unk19;
		bool                                                       unk1A;
		uint8_t													   pad1B;
		uint32_t												   pad1C;
	};
	static_assert(sizeof(DismemberedLimb) == 0x18);

	class ExtraDismemberedLimbs : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kDismemberedLimbs>;
	public:
		~ExtraDismemberedLimbs();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		uint16_t                                                limbs;
		bool                                                    eaten;
		uint8_t                                                 unk13;
		uint32_t                                                unk14;
		TESForm*                                                deathObject;
		BSTArray<DismemberedLimb*>                              dismemberedLimbs;
		uint32_t												lastHitLimb;
		uint32_t												pad3C;
	};
	static_assert(sizeof(ExtraDismemberedLimbs) == 0x38);
}