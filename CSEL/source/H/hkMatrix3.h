#pragma once

#include "../H/hkVector4.h"

namespace ConsoleRE
{
	class hkMatrix3
	{
	public:
		hkVector4 col0;
		hkVector4 col1;
		hkVector4 col2;
	};
	static_assert(sizeof(hkMatrix3) == 0x30);
}