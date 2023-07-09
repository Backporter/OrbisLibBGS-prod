#pragma once

#include "../G/GMemory.h"
#include <stdint.h>

namespace ConsoleRE
{
	template <uint32_t N>
	class GNewOverrideBase
	{
	public:
		enum
		{
			kStatType = N
		};

		GFC_MEMORY_REDEFINE_NEW(GNewOverrideBase, N);
	};
}