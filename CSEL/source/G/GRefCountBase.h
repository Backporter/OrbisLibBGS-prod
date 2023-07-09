#pragma once

#include "../G/GRefCountBaseStatImpl.h"
#include "../G/GRefCountImpl.h"

#include <stdint.h>

namespace ConsoleRE
{
	template <class T, uint32_t STAT>
	class GRefCountBase : public GRefCountBaseStatImpl<GRefCountImpl, STAT>
	{
	public:
		enum
		{
			kStatType = STAT
		};
	};
}