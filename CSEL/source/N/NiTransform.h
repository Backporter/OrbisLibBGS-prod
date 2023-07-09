#pragma once

#include "../N/NiMatrix3.h"
#include "../N/NiPoint3.h"

#include <stdint.h>

namespace ConsoleRE
{
	class NiTransform
	{
	public:
		NiMatrix3 rotate;
		NiPoint3  translate;
		float     scale;
	};
	static_assert(sizeof(NiTransform) == 0x34);
}