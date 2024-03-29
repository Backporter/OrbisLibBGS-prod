#pragma once

#include "hkVector4.h"
#include <stdint.h>

namespace ConsoleRE
{
	struct hkpLinearCastInput
	{
	public:
		// members
		hkVector4     to;                   // 00
		float         maxExtraPenetration;  // 10
		float         startPointTolerance;  // 14
		uint64_t	  pad18;                // 18
	};
	static_assert(sizeof(hkpLinearCastInput) == 0x20, "hkpLinearCastInput");
}