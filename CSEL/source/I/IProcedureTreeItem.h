#pragma once

namespace ConsoleRE
{
	class IProcedureTreeItem
	{
	public:
		virtual ~IProcedureTreeItem();
	};
	static_assert(sizeof(IProcedureTreeItem) == 0x8);
}