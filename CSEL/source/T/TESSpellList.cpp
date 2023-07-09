#include "../T/TESSpellList.h"

namespace ConsoleRE
{
	uint32_t	TESSpellList::GetSpellCount()
	{
		if (actorEffects)
		{
			return actorEffects->numSpells;
		}

		return 0;
	}

	uint32_t	TESSpellList::GetShoutCount()
	{
		if (actorEffects)
		{
			return actorEffects->numShouts;
		}

		return 0;
	}

	bool		TESSpellList::GetSpell(uint32_t val, SpellItem*& out)
	{
		if (actorEffects && val < actorEffects->numSpells)
		{
			out = actorEffects->spells[val];
			return true;
		}

		return false;
	}

	bool		TESSpellList::GetShout(uint32_t val, TESShout*& out)
	{
		if (actorEffects && val < actorEffects->numShouts)
		{
			out = actorEffects->shouts[val];
			return true;
		}

		return false;
	}

	SpellItem*	TESSpellList::GetSpell(uint32_t val)
	{
		if (actorEffects && val < actorEffects->numSpells)
		{
			return actorEffects->spells[val];
		}

		return nullptr;
	}

	TESShout*	TESSpellList::GetShout(uint32_t val)
	{
		if (actorEffects && val < actorEffects->numShouts)
		{
			return actorEffects->shouts[val];
		}

		return nullptr;
	}
}