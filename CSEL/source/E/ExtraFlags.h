#pragma once

#include "../B/BSExtraData.h"
#include "../E/ExtraDataTypes.h"

namespace ConsoleRE
{
	class ExtraFlags : public BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kFlags>;
	public:
		~ExtraFlags();

		// override (BSExtraData)
		uint32_t GetType() const override;
	public:
		uint32_t flags;
		uint32_t pad14;
	};
	static_assert(sizeof(ExtraFlags) == 0x18);
}