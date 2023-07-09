#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraShouldWear : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kShouldWear>;
	public:
		~ExtraShouldWear();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		uint64_t unk10;
	};
	static_assert(sizeof(ExtraShouldWear) == 0x18);
}