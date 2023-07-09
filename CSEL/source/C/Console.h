#pragma once
#include "../I/IMenu.h"

namespace ConsoleRE
{
	class Console : public IMenu
	{
	public:
		virtual ~Console();
		constexpr static inline const char* MENU_NAME = "Console";
	};
}