#pragma once

#include "../H/hkRotation.h"
#include "../H/hkVector4.h"

namespace ConsoleRE
{
	class hkTransform
	{
	public:
		hkRotation rotation;
		hkVector4  translation;
	};
	static_assert(sizeof(hkTransform) == 0x40);
}