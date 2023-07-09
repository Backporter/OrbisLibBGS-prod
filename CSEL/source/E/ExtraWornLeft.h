#pragma once

#include "../B/BSExtraData.h"

namespace ConsoleRE
{
	class ExtraWornLeft : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kWornLeft>;
	public:
		~ExtraWornLeft() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
	};
	static_assert(sizeof(ExtraWornLeft) == 0x10);
}
