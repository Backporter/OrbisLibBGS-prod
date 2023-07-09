#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSTList.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class TESObjectREFR;

	class ExtraWaterLightRefs : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kWaterLightRefs>;
	public:
		~ExtraWaterLightRefs();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		BSSimpleList<TESObjectREFR*> refs;
	};
	static_assert(sizeof(ExtraWaterLightRefs) == 0x20);
}