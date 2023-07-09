#pragma once

#include "../../../../../OrbisUtil/include/Relocation.h"

#include "../../../../source/M/MagicItemData.h"
#include "../../../../source/S/StandardItemData.h"
#include "../../../../source/G/GFxMovieView.h"
#include "../../../../source/T/TESForm.h"
#include "../../../../source/A/Actor.h"
#include "../../../../source/P/PlayerCharacter.h"
#include "../../../../source/I/InventoryEntryData.h"

#include <stdint.h>
#include <math.h>

namespace ItemData
{
	extern bool Extend;
	extern bool ExtendAlchemyCategories;

	struct unkstruct2
	{
	public:
		void*				 f;
		uint32_t			 c;
	};

	void   common(ConsoleRE::GFxValue* gfxv, ConsoleRE::GFxMovieView* movie, ConsoleRE::TESForm* form);
	void iteminfo(ConsoleRE::GFxValue* gfxv, ConsoleRE::InventoryEntryData* ptr);
	void Standard(ConsoleRE::GFxValue* gfxv, ConsoleRE::GFxMovieView* movie, ConsoleRE::TESForm* form, ConsoleRE::InventoryEntryData* Unk3);
	void      inv(ConsoleRE::GFxValue* gfxv, ConsoleRE::GFxMovieView* movie, ConsoleRE::TESForm* form, void* Unk3);
	void    magic(ConsoleRE::GFxValue* gfxv, ConsoleRE::GFxMovieView* movie, ConsoleRE::TESForm* form);
	
	void ListForm(ConsoleRE::GFxValue* gfxv, ConsoleRE::GFxMovieView* movie, ConsoleRE::TESForm* form);
	void    actor(ConsoleRE::GFxValue* gfxv, ConsoleRE::GFxMovieView* movie, ConsoleRE::TESForm* form);
	void form(ConsoleRE::GFxValue* a_gfxv, ConsoleRE::GFxMovieView* a_movie, ConsoleRE::TESForm* a_form);

	void StandardItemDataHook(ConsoleRE::StandardItemData* a_this, ConsoleRE::GFxMovieView** movie, void* Unk3, void* Unk4);
	void MagicItemDataHook(ConsoleRE::MagicItemData* a_this, ConsoleRE::GFxMovieView** movie, ConsoleRE::TESForm* Unk3, int Unk4);
}