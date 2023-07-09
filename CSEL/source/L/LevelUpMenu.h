#pragma once

#include "../I/IMenu.h"

namespace ConsoleRE
{
	class LevelUpMenu : public IMenu
	{
	public:
		constexpr static inline const char* MENU_NAME = "StatsMenu";
	public:
		~LevelUpMenu() override;
		
		// override (IMenu)
		void Accept(CallbackProcessor* a_cbReg) override;
	public:
		bool	 Unk30;
		uint8_t  pad31;
		uint16_t pad32;
		uint32_t pad34;
	};
	static_assert(sizeof(LevelUpMenu) == 0x38);
}