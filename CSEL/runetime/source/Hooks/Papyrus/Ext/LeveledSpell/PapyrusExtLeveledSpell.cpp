#include "../LeveledSpell/PapyrusExtLeveledSpell.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESLevSpell.h"

namespace PapyrusExtLeveledSpell
{
	// I really hate doing this...
	using namespace ConsoleRE;

	uint32_t GetLevSpellChance(TESLevSpell* base)
	{
		if (base)
		{
			return base->chanceNone;
		}
		return 0;
	}

	void SetLevSpellChanceNone(TESLevSpell* base, uint32_t chanceNone)
	{
		if (base)
		{
			base->chanceNone = chanceNone;
		}
	}

	uint32_t GetLevSpellNumForms(TESLevSpell* base)
	{
		if (base)
		{
			return base->numEntries;
		}

		return 0;
	}

	TESForm * GetLevSpellNthForm(TESLevSpell* base, uint32_t n)
	{
		if (base && n < base->numEntries)
		{
			return base->entries[n].form;
		}

		return NULL;
	}

	uint32_t GetLevSpellNthLevel(TESLevSpell* base, uint32_t n)
	{
		if (base && n < base->numEntries)
		{
			return base->entries[n].level;
		}

		return 0;
	}

	void SetLevSpellNthLevel(TESLevSpell* base, uint32_t n, uint32_t level)
	{
		if (base && n < base->numEntries)
		{
			base->entries[n].level = level;
		}
	}

	bool RegisterLeveledSpell(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetLevSpellChance),     TESLevSpell, uint32_t>                 ("GetChanceNone", "LeveledSpell", GetLevSpellChance));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetLevSpellChanceNone), TESLevSpell, void, uint32_t>           ("SetChanceNone", "LeveledSpell", SetLevSpellChanceNone));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetLevSpellNumForms),   TESLevSpell, uint32_t>                 ("GetNumForms",   "LeveledSpell", GetLevSpellNumForms));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetLevSpellNthForm),    TESLevSpell, TESForm*, uint32_t>       ("GetNthForm",    "LeveledSpell", GetLevSpellNthForm));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetLevSpellNthLevel),   TESLevSpell, uint32_t, uint32_t>       ("GetNthLevel",   "LeveledSpell", GetLevSpellNthLevel));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetLevSpellNthLevel),   TESLevSpell, void, uint32_t, uint32_t> ("SetNthLevel",   "LeveledSpell", SetLevSpellNthLevel));

		VM->SetCallableFromTasklets("LeveledSpell", "GetChanceNone", true);
		VM->SetCallableFromTasklets("LeveledSpell", "SetChanceNone", true);
		VM->SetCallableFromTasklets("LeveledSpell", "GetNumForms",   true);
		VM->SetCallableFromTasklets("LeveledSpell", "GetNthForm",    true);
		VM->SetCallableFromTasklets("LeveledSpell", "GetNthLevel",   true);
		VM->SetCallableFromTasklets("LeveledSpell", "SetNthLevel",   true);


		return true;
	}
}