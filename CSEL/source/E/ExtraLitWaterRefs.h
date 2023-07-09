#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSTList.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class TESObjectREFR;

	class ExtraLitWaterRefs : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kLitWaterRefs>;
	public:
		~ExtraLitWaterRefs();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		BSSimpleList<TESObjectREFR*> refs;
	};
	static_assert(sizeof(ExtraLitWaterRefs) == 0x20);
}