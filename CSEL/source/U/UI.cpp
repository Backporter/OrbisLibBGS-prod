#include "../../../OrbisUtil/include//Relocation.h"

#include "../U/UI.h"
#include "../I/IMenu.h"

namespace ConsoleRE
{
	UI* UI::GetSingleton()
	{
		Relocation<UI**> Singleton("", 0x20C00B8);
		return *Singleton;
	}


	bool UI::GameIsPaused()
	{
		return numPausesGame > 0;
	}

	GPtr<IMenu> UI::GetMenu(const BSFixedString& name)
	{
		auto it = menuMap.find(name);
		return it != menuMap.end() ? it->m_item.second.menu : nullptr;
	}

	GPtr<GFxMovieView> UI::GetMovieView(const BSFixedString& a_name)
	{
		auto ret = GetMenu(a_name);
		return ret ? ret->uiMovie : nullptr;
	}

	bool UI::IsApplicationMenuOpen()
	{
		return numApplicationMenus > 0;
	}

	bool UI::IsCursorHiddenWhenTopmost()
	{
		return numDontHideCursorWhenTopmost == 0;
	}

	bool UI::IsItemMenuOpen()
	{
		return numItemMenus > 0;
	}

	bool UI::IsMenuOpen(const BSFixedString& a_menuName)
	{
		auto menu = GetMenu(a_menuName);
		return menu && menu->OnStack();
	}

	bool UI::IsModalMenuOpen()
	{
		return modal;
	}

	bool UI::IsPauseMenuDisabled()
	{
		return numDisablePauseMenu > 0;
	}

	bool UI::IsSavingAllowed()
	{
		return numAllowSaving > 0;
	}

	bool UI::IsShowingMenus()
	{
		return menuSystemVisible;
	}

	bool UI::IsUsingCustomRendering()
	{
		return numCustomRendering > 0;
	}

	void UI::Register(const char* a_menuName, Create_t* a_creator)
	{
		using func_t = void(UI* const, const char*, Create_t*);
		Relocation<func_t*> func("", 0x111F140);
		func(this, a_menuName, a_creator);
	}

	void UI::ShowMenus(bool a_show)
	{
		menuSystemVisible = a_show;
	}
}