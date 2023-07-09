#include "../../../OrbisUtil/include/Relocation.h"

#include "../M/MagicItem.h"

namespace ConsoleRE
{
	Effect* MagicItem::GetCostliestEffectItem(int a_unk1, bool a_unk2)
	{
		using func_t = decltype(&MagicItem::GetCostliestEffectItem);
		Relocation<func_t> func("", 0xF980);
		return func(this, a_unk1, a_unk2);
	}

	float MagicItem::GetEffectiveMagickaCost(Actor* a_actor)
	{
		using func_t = decltype(&MagicItem::GetEffectiveMagickaCost);
		Relocation<func_t> func("", 0xF6F0);
		return func(this, a_actor);
	}
}