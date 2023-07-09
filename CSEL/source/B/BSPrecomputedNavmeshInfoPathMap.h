#pragma once

#include "../B/BSTArray.h"
#include "../B/BSTHashMap.h"

namespace ConsoleRE
{
	struct BSNavmeshInfo;

	class BSPrecomputedNavmeshInfoPathMap
	{
	public:
		BSTArray<BSTArray<const BSNavmeshInfo*>*>       allPaths;
		BSTHashMap<UnkKey, UnkValue>					infoToIndexMap;
	};
	static_assert(sizeof(BSPrecomputedNavmeshInfoPathMap) == 0x30);
}