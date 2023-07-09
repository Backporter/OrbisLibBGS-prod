#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraLeveledItem : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kLeveledItem>;
	public:
		~ExtraLeveledItem() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		uint32_t  levItem;
	};
	static_assert(sizeof(ExtraLeveledItem) == 0x18);
}
