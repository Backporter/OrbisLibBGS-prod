#pragma once

#include "../I/IMenu.h"

namespace ConsoleRE
{
	class ConsoleNativeUIMenu : public IMenu
	{
	public:
		constexpr static const char* MENU_NAME = "Console Native UI Menu";
	public:
		~ConsoleNativeUIMenu() override;

		// override (IMenu)
		uint32_t ProcessMessage(UIMessage& a_message) override;
	public:
		uint8_t  unk30;
		uint8_t  pad31;
		uint16_t pad32;
		uint32_t pad34;
	};
	static_assert(sizeof(ConsoleNativeUIMenu) == 0x38);
}