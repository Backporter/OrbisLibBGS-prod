#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class GFxValue;

	class FxResponseArgsBase
	{
	public:
		FxResponseArgsBase() = default;
		virtual ~FxResponseArgsBase() = default;

		// add
		virtual uint32_t GetValues(GFxValue** a_params) = 0;
	};
	static_assert(sizeof(FxResponseArgsBase) == 0x8);
}