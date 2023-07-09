#pragma once

#include "hkVector4.h"
#include <stdint.h>

namespace ConsoleRE
{
	struct hkpWorldRayCastInput
	{
	public:
		hkVector4     from;
		hkVector4     to;
		bool          enableShapeCollectionFilter{ false };
		uint32_t	  filterInfo{ 0 };
	};
	static_assert(sizeof(hkpWorldRayCastInput) == 0x30);
}