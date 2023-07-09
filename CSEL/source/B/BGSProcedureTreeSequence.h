#pragma once

#include "../B/BGSProcedureTreeBranch.h"
#include "../B/BGSTypedItem.h"

namespace ConsoleRE
{
	class BGSProcedureTreeSequence : public BGSTypedItem<BGSProcedureTreeSequence, BGSProcedureTreeBranch>
	{
	public:
		~BGSProcedureTreeSequence() override;
	};
	static_assert(sizeof(BGSProcedureTreeSequence) == 0x28);
}