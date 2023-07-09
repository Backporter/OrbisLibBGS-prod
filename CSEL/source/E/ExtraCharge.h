#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	// 0x18
	class ExtraCharge : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kCharge>;
	public:
		ExtraCharge();
		explicit ExtraCharge(float a_charge);
		~ExtraCharge() override = default;

		// override(BSExtraData)
		uint32_t	GetType() const override;
		bool		IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		float			charge;
		uint32_t		pad14;
	};
	static_assert(sizeof(ExtraCharge) == 0x18);
}