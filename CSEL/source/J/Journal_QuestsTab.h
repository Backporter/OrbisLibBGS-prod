#pragma once

#include "../G/GFxValue.h"
#include "../J/JournalTab.h"

namespace ConsoleRE
{
	class Journal_QuestsTab : public JournalTab
	{
	public:
		~Journal_QuestsTab() override;

		// override (JournalTab)
		void Accept(CallbackProcessor* a_cbReg) override;
	public:
		GFxValue unk18;
		bool     unk30;
		uint8_t	 unk31;
		uint16_t unk32;
		uint32_t unk34;
	};
	static_assert(sizeof(Journal_QuestsTab) == 0x38);
}