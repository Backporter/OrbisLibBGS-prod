#pragma once

#include "../B/BGSProcedureTreeConditionalItem.h"
#include "../B/BSTArray.h"

namespace ConsoleRE
{
	class BGSProcedureTreeBranch : public BGSProcedureTreeConditionalItem
	{
	public:
		~BGSProcedureTreeBranch() override;
	public:
		BSTArray<BGSProcedureTreeConditionalItem*> conditions;
		uint64_t								   unk28;
	};
	static_assert(sizeof(BGSProcedureTreeBranch) == 0x28);
}