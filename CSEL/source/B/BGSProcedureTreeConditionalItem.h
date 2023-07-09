#pragma once

#include "../I/IProcedureTreeItem.h"
#include "../T/TESCondition.h"

namespace ConsoleRE
{
	class BGSProcedureTreeConditionalItem : public IProcedureTreeItem
	{
	public:
		~BGSProcedureTreeConditionalItem() override;
	public:
		TESCondition conditions;
	};
	static_assert(sizeof(BGSProcedureTreeConditionalItem) == 0x10);
}