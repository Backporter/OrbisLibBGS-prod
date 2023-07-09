#pragma once

#include "../H/hkVector4.h"

namespace ConsoleRE
{
	class hkContactPoint
	{
	public:
		hkVector4 position;
		hkVector4 separatingNormal;
	};
	static_assert(sizeof(hkContactPoint) == 0x20);
}
