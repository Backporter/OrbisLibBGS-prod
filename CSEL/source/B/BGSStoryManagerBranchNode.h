#pragma once

#include "../B/BGSStoryManagerNodeBase.h"
#include "../B/BSTArray.h"

namespace ConsoleRE
{
	class BGSStoryManagerBranchNode : public BGSStoryManagerNodeBase
	{
	public:
		static constexpr int TypeID = 112;
	public:
		BSTArray<BGSStoryManagerNodeBase*> children;
	};
	static_assert(sizeof(BGSStoryManagerBranchNode) == 0x50);
}