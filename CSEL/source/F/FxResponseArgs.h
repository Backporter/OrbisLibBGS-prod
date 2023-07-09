#pragma once

#include "../F/FxResponseArgsBase.h"
#include "../G/GFxValue.h"

namespace ConsoleRE
{
	template <uint32_t N>
	class FxResponseArgs : public FxResponseArgsBase
	{
	public:
		FxResponseArgs() : FxResponseArgsBase(), _values(), _index(1)
		{}

		~FxResponseArgs() override = default;

		uint32_t GetValues(GFxValue** a_params) override
		{
			*a_params = _values;
			return _index;
		}
	public:
		GFxValue _values[N + 1];
		uint32_t _index;
		uint32_t _pad;
	};
	static_assert(sizeof(FxResponseArgs<1>) == 0x40);
}