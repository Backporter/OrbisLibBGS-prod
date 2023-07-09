#pragma once
#include "../I/IMenu.h"
#include "../M/MenuEventHandler.h"

namespace ConsoleRE
{
	class FavoritesMenu : 
		public IMenu,
		public MenuEventHandler
	{
	public:
		struct Entry
		{
			TESForm*            item;       // 00
			InventoryEntryData* entryData;  // 08
		};
	public:
		constexpr static inline const char* MENU_NAME = "FavoritesMenu";
		virtual ~FavoritesMenu();
	public:
		GFxValue		root;
		BSTArray<Entry> favorites;
		uint32_t		Unk68;					// 0x68
		bool			pcControlsReady;		// 0x6C
		bool			isVampire;				// 0x6D
		uint8_t			Unk6E;					// 0x6E
		uint8_t			Unk6F;					// 0x6F
	};
	static_assert(offsetof(FavoritesMenu, root)            == 0x40, "FavoritesMenu::root");
	static_assert(offsetof(FavoritesMenu, favorites)       == 0x58, "FavoritesMenu::favorites");
	static_assert(offsetof(FavoritesMenu, Unk68)           == 0x68, "FavoritesMenu::Unk68");
	static_assert(offsetof(FavoritesMenu, pcControlsReady) == 0x6C, "FavoritesMenu::pcControlsReady");
	static_assert(offsetof(FavoritesMenu, isVampire)       == 0x6D, "FavoritesMenu::isVampire");
	static_assert(offsetof(FavoritesMenu, Unk6E)           == 0x6E, "FavoritesMenu::Unk6C");
	static_assert(offsetof(FavoritesMenu, Unk6F)           == 0x6F, "FavoritesMenu::Unk6D");
	static_assert(sizeof(FavoritesMenu)                    == 0x70, "FavoritesMenu");
}