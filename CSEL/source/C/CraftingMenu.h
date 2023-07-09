#pragma once

#include "../I/IMenu.h"

namespace ConsoleRE
{
	namespace CraftingSubMenus
	{
		class CraftingSubMenu;
	}

	class CraftingMenu : public IMenu
	{
	public:
		constexpr static const char* MENU_NAME = "Crafting Menu";
	public:
		~CraftingMenu() override;

		// override (IMenu)
		uint32_t		   ProcessMessage(UIMessage& a_message) override;
		void               AdvanceMovie(float a_interval, uint32_t a_currentTime) override;
		void               PostDisplay() override;
	public:
		CraftingSubMenus::CraftingSubMenu* subMenu;
	};
	static_assert(sizeof(CraftingMenu) == 0x38);
}