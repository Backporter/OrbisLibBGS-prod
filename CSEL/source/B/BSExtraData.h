#pragma once

#include "../E/ExtraDataTypes.h"

#include <stdint.h>

namespace ConsoleRE
{
	class BSExtraData
	{
	public:
		static constexpr int TypeID = ExtraDataType<ExtraDataTypes::kNone>;
	public:
		BSExtraData() = default;
		virtual ~BSExtraData() = default;

		// add
		virtual uint32_t	GetType() const = 0;
		virtual bool		IsNotEqual(const BSExtraData* a_rhs) const { return false; }
	public:
		BSExtraData* next { nullptr };
	};
	static_assert(sizeof(BSExtraData) == 0x10);
}