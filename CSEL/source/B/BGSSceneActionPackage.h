#pragma once

#include "../B/BGSSceneAction.h"
#include "../B/BSTArray.h"

namespace ConsoleRE
{
	class TESPackage;

	class BGSSceneActionPackage : public BGSSceneAction
	{
	public:
		uint64_t				unk18;
		BSTArray<TESPackage*>	packages;
	};
	static_assert(sizeof(BGSSceneActionPackage) == 0x30);
}