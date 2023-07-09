#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class BGSAcousticSpace;

	class ExtraCellAcousticSpace : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kCellAcousticSpace>;
	public:
		~ExtraCellAcousticSpace() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		BGSAcousticSpace* space;
	};
	static_assert(sizeof(ExtraCellAcousticSpace) == 0x18);
}