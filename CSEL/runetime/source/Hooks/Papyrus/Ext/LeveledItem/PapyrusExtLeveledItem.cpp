#include "../LeveledItem/PapyrusExtLeveledItem.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESLevItem.h"
#include "../../../../../../source/T/TESGlobal.h"
#include "../../../../../../source/T/TESForm.h"

namespace PapyrusExtLeveledItem
{
	// I really hate doing this...
	using namespace ConsoleRE;

	uint32_t GetChanceNone(TESLevItem* base)
	{
		if (base)
		{
			return base->chanceNone;
		}

		return 0;
	}

	void SetChanceNone(TESLevItem* base, uint32_t chanceNone)
	{
		if (base)
		{
			base->chanceNone = chanceNone;
		}
	}

	TESGlobal * GetChanceGlobal(TESLevItem* base)
	{
		if (base)
		{
			return base->chanceGlobal;
		}

		return NULL;
	}

	void SetChanceGlobal(TESLevItem * base, TESGlobal * globalVar)
	{
		if (base && globalVar)
		{
			base->chanceGlobal = globalVar;
		}
	}

	uint32_t GetNumForms(TESLevItem* base)
	{
		if (base)
		{
			return base->numEntries;
		}
		return 0;
	}

	TESForm * GetNthForm(TESLevItem * base, uint32_t n)
	{
		if (base && n < base->numEntries)
		{
			return base->entries[n].form;
		}
		
		return NULL;
	}

	uint32_t GetNthLevel(TESLevItem * base, uint32_t n)
	{
		if (base && n < base->numEntries)
		{
			return base->entries[n].level;
		}

		return 0;
	}

	void SetNthLevel(TESLevItem * base, uint32_t n, uint32_t level)
	{
		if (base && n < base->numEntries)
		{
			if (level > UINT16_MAX)
				level = UINT16_MAX;

			base->entries[n].level = level;
		}
	}

	uint32_t GetNthCount(TESLevItem * base, uint32_t n)
	{
		if (base && n < base->numEntries)
		{
			return base->entries[n].count;
		}

		return 0;
	}

	void SetNthCount(TESLevItem* base, uint32_t n, uint32_t count)
	{
		if (base && n < base->numEntries)
		{
			if (count > UINT16_MAX)
				count = UINT16_MAX;

			base->entries[n].count = count;
		}
	}

	bool RegisterLeveledItem(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetChanceNone),   TESLevItem, uint32_t>                 ("GetChanceNone",   "LeveledItem", GetChanceNone));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetChanceNone),   TESLevItem, void, uint32_t>           ("SetChanceNone",   "LeveledItem", SetChanceNone));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetChanceGlobal), TESLevItem, TESGlobal*>               ("GetChanceGlobal", "LeveledItem", GetChanceGlobal));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetChanceGlobal), TESLevItem, void, TESGlobal*>         ("SetChanceGlobal", "LeveledItem", SetChanceGlobal));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNumForms),     TESLevItem, uint32_t>                 ("GetNumForms",     "LeveledItem", GetNumForms));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthForm),      TESLevItem, TESForm*, uint32_t>       ("GetNthForm",      "LeveledItem", GetNthForm));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthLevel),     TESLevItem, uint32_t, uint32_t>       ("GetNthLevel",     "LeveledItem", GetNthLevel));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetNthLevel),     TESLevItem, void, uint32_t, uint32_t> ("SetNthLevel",     "LeveledItem", SetNthLevel));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthCount),     TESLevItem, uint32_t, uint32_t>       ("GetNthCount",     "LeveledItem", GetNthCount));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetNthCount),     TESLevItem, void, uint32_t, uint32_t> ("SetNthCount",     "LeveledItem", SetNthCount));

		VM->SetCallableFromTasklets("LeveledItem", "GetChanceNone",   true);
		VM->SetCallableFromTasklets("LeveledItem", "SetChanceNone",   true);
		VM->SetCallableFromTasklets("LeveledItem", "GetChanceGlobal", true);
		VM->SetCallableFromTasklets("LeveledItem", "SetChanceGlobal", true);
		VM->SetCallableFromTasklets("LeveledItem", "GetNumForms",     true);
		VM->SetCallableFromTasklets("LeveledItem", "GetNthForm",      true);
		VM->SetCallableFromTasklets("LeveledItem", "GetNthLevel",     true);
		VM->SetCallableFromTasklets("LeveledItem", "SetNthLevel",     true);
		VM->SetCallableFromTasklets("LeveledItem", "GetNthCount",     true);
		VM->SetCallableFromTasklets("LeveledItem", "SetNthCount",     true);

		return true;
	}
}