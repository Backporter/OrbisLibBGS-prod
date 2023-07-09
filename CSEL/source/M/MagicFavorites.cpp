#include "../../../OrbisUtil/include/Relocation.h"

#include "../M/MagicFavorites.h"

namespace ConsoleRE
{
	MagicFavorites* MagicFavorites::GetSingleton()
	{
		Relocation<MagicFavorites**> singleton("", 0x313CF08);
		return *singleton;
	}

	void MagicFavorites::ClearHHotkey(int8_t idx)
	{
		if (idx < 0 || idx >= hotkeys.m_size)
			return;

		hotkeys[idx] = NULL;
	}

	TESForm* MagicFavorites::GetSpell(int8_t idx)
	{
		return hotkeys[idx];
	}

	bool MagicFavorites::IsFavorited(TESForm* a_form)
	{
		int32_t indexOut = -1;
		if (spells.GetSortIndex(a_form, indexOut) && indexOut != -1)
			return true;
		else
			return false;
	}

	void MagicFavorites::SetHotkey(TESForm* a_form, int8_t a_idx)
	{
		if (a_idx < 0 || a_idx >= hotkeys.m_size)
			return;

		auto s_idx = hotkeys.Get(a_form);

		if (a_idx == s_idx)
			return;


		if (IsFavorited(a_form))
		{
			hotkeys[s_idx] = NULL;
			hotkeys[a_idx] = a_form;
		}
	}
}