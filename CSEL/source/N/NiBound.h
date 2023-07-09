#pragma once

#include "NiPoint3.h"
#include <stdint.h>

namespace ConsoleRE
{
	class NiBound
	{
	public:
		NiPoint3 center;  // 00
		float    radius;  // 0C
	};
}