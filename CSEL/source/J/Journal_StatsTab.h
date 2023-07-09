#pragma once

#include "../J/JournalTab.h"

namespace ConsoleRE
{
	class Journal_StatsTab : public JournalTab
	{
	public:
		~Journal_StatsTab() override;

		// override (JournalTab)
		void Accept(CallbackProcessor* a_cbReg) override;
	};
	static_assert(sizeof(Journal_StatsTab) == 0x18);
}