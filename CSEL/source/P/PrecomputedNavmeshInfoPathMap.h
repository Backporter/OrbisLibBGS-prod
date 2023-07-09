#pragma once

#include "../B/BSPrecomputedNavmeshInfoPathMap.h"

namespace ConsoleRE
{
	class PrecomputedNavmeshInfoPathMap : public BSPrecomputedNavmeshInfoPathMap
	{
	public:
	};
	static_assert(sizeof(PrecomputedNavmeshInfoPathMap) == 0x30);
}