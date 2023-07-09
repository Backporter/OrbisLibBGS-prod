#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class TESWaterForm;

	class ExtraCellWaterType : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kCellWaterType>;
	public:
		~ExtraCellWaterType();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		TESWaterForm* water;
	};
	static_assert(sizeof(ExtraCellWaterType) == 0x18);
}