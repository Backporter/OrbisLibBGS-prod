#pragma once

#include "../B/BSExtraData.h"
#include "../B/BSPointerHandle.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class TESLevItem;

	class ExtraLeveledItemBase : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kLeveledItemBase>;
	public:
		~ExtraLeveledItemBase();

		// override (BSExtraData)
		uint32_t GetType() const override;
		bool     IsNotEqual(const BSExtraData* a_rhs) const override;
	public:
		TESLevItem* levItem;
	};
	static_assert(sizeof(ExtraLeveledItemBase) == 0x18);
}