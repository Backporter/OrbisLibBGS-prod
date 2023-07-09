#pragma once

#include "../B/BSTArray.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class MagicFavorites 
	{
	public:
		virtual ~MagicFavorites();

		static MagicFavorites* GetSingleton();

		void	 ClearHHotkey(int8_t idx);
		TESForm* GetSpell(int8_t idx);
		bool	 IsFavorited(TESForm* a_form);
		void	 SetHotkey(TESForm* a_form, int8_t a_idx);
	public:
		BSTArray<TESForm*> spells;
		BSTArray<TESForm*> hotkeys;
	};
	static_assert(sizeof(MagicFavorites) == 0x28);
}