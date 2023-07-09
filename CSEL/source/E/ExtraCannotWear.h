#pragma once

#include "../B/BSExtraData.h"

namespace ConsoleRE
{
	class ExtraCannotWear : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kCannotWear>;
	public:
		~ExtraCannotWear() override;

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
	};
	static_assert(sizeof(ExtraCannotWear) == 0x10);
}