#pragma once

#include "../H/hkMatrix3.h"

namespace ConsoleRE
{
	class alignas(0x10) hkRotation : public hkMatrix3
	{
	public:
	};
	static_assert(sizeof(hkRotation) == 0x30);
}