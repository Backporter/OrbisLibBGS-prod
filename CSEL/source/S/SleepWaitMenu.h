#pragma once
#include "../I/IMenu.h"

namespace ConsoleRE
{
	class SleepWaitMenu : public IMenu
	{
	public:
		virtual ~SleepWaitMenu();
		constexpr static inline const char* MENU_NAME = "Sleep/Wait Menu";
	public:
	};
}
