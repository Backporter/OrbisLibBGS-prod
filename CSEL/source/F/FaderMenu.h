#pragma once

#include "../I/IMenu.h"

namespace ConsoleRE
{
	class FaderMenu : public IMenu
	{
	public:
		constexpr static const char* MENU_NAME = "Fader Menu";
	public:
		~FaderMenu();

		// override (IMenu)
		uint32_t ProcessMessage(UIMessage& a_message) override;
	public:
		void*    unk30;
		uint8_t	 unk38;
		uint8_t	 unk39;
		uint16_t pad3A;
		uint32_t pad3C;
	};
	static_assert(sizeof(FaderMenu) == 0x40);
}