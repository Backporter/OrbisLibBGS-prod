#pragma once

#include "../../../../../OrbisUtil/include/CryptoHandler.h"
#include "../../../../../OrbisUtil/include/SystemWrapper.h"

#include "../ItemData/ItemData.h"

#include "../../../../source/G/GFxMovieRoot.h"
#include "../../../../source/G/GFxValue.h"
#include "../../../../source/T/TESForm.h"
#include "../../../../source/T/TESFullName.h"

#include "../../../../source/F/FavoritesMenu.h"
#include "../../../../source/I/InventoryEntryData.h"
#include "../../../../source/T/TESFullName.h"
#include "../../../../source/RTTI.h"

namespace Favorites
{
	void ItemFavoritesSet(ConsoleRE::FavoritesMenu* a_this, ConsoleRE::GFxValue* datacontainer, ConsoleRE::InventoryEntryData* obj);
	void MagicFavoritesSet(ConsoleRE::GFxMovieRoot* a_this, ConsoleRE::GFxValue* datacontainer, ConsoleRE::TESForm* a_form);
}