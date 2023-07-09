#pragma once

#include "../I/IMenu.h"

namespace ConsoleRE
{
	class MessageBoxMenu : public IMenu
	{
	public:
		constexpr static inline const char* MENU_NAME = "MessageBoxMenu";
	public:
		~MessageBoxMenu() override;

		// override (IMenu)
		void     Accept(CallbackProcessor* a_processor) override;
		uint32_t ProcessMessage(UIMessage& a_message) override;
	public:
		uint8_t  unk30;
		uint8_t  pad31;
		uint16_t pad32;
		uint32_t pad34;
	};
	static_assert(sizeof(MessageBoxMenu) == 0x38);
}