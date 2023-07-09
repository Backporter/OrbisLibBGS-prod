#pragma once
#include "../I/IMenu.h"

namespace ConsoleRE
{
	class StatsMenu : public IMenu
	{
	public:
		virtual ~StatsMenu();
		constexpr static inline const char* MENU_NAME = "StatsMenu";
	};
}