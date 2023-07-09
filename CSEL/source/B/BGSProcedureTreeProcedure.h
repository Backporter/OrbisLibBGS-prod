#pragma once

#include "../B/BGSProcedureTreeConditionalItem.h"
#include "../B/BGSTypedItem.h"

namespace ConsoleRE
{
	class BGSProcedureBase;

	class BGSProcedureTreeProcedure : public BGSTypedItem<BGSProcedureTreeProcedure, BGSProcedureTreeConditionalItem>
	{
	public:
		BGSProcedureBase* procedure;
	};
	static_assert(sizeof(BGSProcedureTreeProcedure) == 0x18);
}