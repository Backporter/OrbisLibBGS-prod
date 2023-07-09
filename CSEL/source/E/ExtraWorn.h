#pragma once

#include "../B/BSExtraData.h"

namespace ConsoleRE
{
	class ExtraWorn : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kWorn>;
	public:
		~ExtraWorn() override;
		
		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
	};
	static_assert(sizeof(ExtraWorn) == 0x10);
}