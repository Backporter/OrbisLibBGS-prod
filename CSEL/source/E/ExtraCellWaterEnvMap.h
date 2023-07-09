#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"
#include "../T/TESTexture.h"

namespace ConsoleRE
{
	class ExtraCellWaterEnvMap : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kCellWaterEnvMap>;
	public:
		~ExtraCellWaterEnvMap();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		TESTexture waterEnvMap;
	};
	static_assert(sizeof(ExtraCellWaterEnvMap) == 0x20);
}