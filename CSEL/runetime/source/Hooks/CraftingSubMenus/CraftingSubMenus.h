#pragma once

#include "../ItemData/ItemData.h"
#include "../../../../source/C/ConstructibleObjectMenu.h"

#include "../../../../source/S/SmithingMenu.h"
#include "../../../../source/A/AlchemyMenu.h"
#include "../../../../source/S/SmithingMenu.h"
#include "../../../../source/E/EnchantConstructMenu.h"

namespace CraftingSubMenusE
{
	extern Relocation<void(*)(void*, void**, void*)>									SmithingMenuSetR;
	extern Relocation<void(*)(void*, void*, void*)>										CraftingSubMenuSetR;
	extern Relocation<void(*)(void*, void*, void*)>										AlchemyMenuSetR;
	
	// functions
	void SmithingMenuSet(ConsoleRE::GFxValue* gfxv,		ConsoleRE::InventoryEntryData** dptr,												ConsoleRE::CraftingSubMenus::SmithingMenu* ptr);
	void CraftingSubMenuSet(ConsoleRE::GFxValue* gfxv,	ConsoleRE::CraftingSubMenus::ConstructibleObjectMenu::ItemEntry* ptr,					ConsoleRE::CraftingSubMenus::ConstructibleObjectMenu* ptr2);
	void AlchemyMenuSet(ConsoleRE::GFxValue* gfxv,		ConsoleRE::CraftingSubMenus::AlchemyMenu::MenuIngredientEntry* ptr,					ConsoleRE::CraftingSubMenus::AlchemyMenu* ptr2);

	void CraftingSubMenusEnchantConstructMenuItemChangeEntrySet(ConsoleRE::CraftingSubMenus::EnchantConstructMenu::ItemChangeEntry* rdi,	ConsoleRE::GFxValue* rsi, ConsoleRE::GFxMovieRoot* rdx);
	
	struct DUMMY
	{
		uint32_t FormID;
		uint32_t FormIndex;
	};

	void AlchemyMenuIndexFixUp(void* a_this, void* a_obj, DUMMY* a_formID, const char* a_name, ConsoleRE::GFxValue* a_args, uint32_t a_argc, bool IsDisplayOBJ);
}