#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraGIDBuffer : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kGIDBuffer>;
	public:
		~ExtraGIDBuffer();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		int8_t* buffer;
	};
	static_assert(sizeof(ExtraGIDBuffer) == 0x18);
}