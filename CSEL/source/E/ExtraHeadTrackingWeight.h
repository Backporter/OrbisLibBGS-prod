#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraHeadTrackingWeight : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kHeadTrackingWeight>;
	public:
		~ExtraHeadTrackingWeight();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		float    weight;
		uint32_t pad14;
	};
	static_assert(sizeof(ExtraHeadTrackingWeight) == 0x18);
}