#include "../LeveledActor/PapyrusExtLeveledActor.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESLevCharacter.h"

namespace PapyrusExtLeveledActor
{
	// I really hate doing this...
	using namespace ConsoleRE;

	uint32_t GetLevFormCount(TESLevCharacter* base)
	{
		if (base)
		{
			return base->numEntries;
		}

		return 0;
	}

	TESForm* GetLevForm(TESLevCharacter* base, uint32_t val)
	{
		if (base && val < base->numEntries)
		{
			return base->entries[val].form;
		}

		return NULL;
	}

	uint32_t GetLev(TESLevCharacter* base, uint32_t val)
	{
		if (base && val < base->numEntries)
		{
			return base->entries[val].level;
		}

		return 0;
	}

	void SetLev(TESLevCharacter* base, uint32_t val, uint32_t val2)
	{
		if (base && val < base->numEntries)
		{
			if (val2 > UINT16_MAX)
				val2 = UINT16_MAX;

			base->entries[val].level = val2;
		}

	}

	uint32_t GetLevCount(TESLevCharacter* base, uint32_t val)
	{
		if (base && val < base->numEntries)
		{
			return base->entries[val].count;
		}

		return 0;
	}

	void SetLevCount(TESLevCharacter* base, uint32_t val, uint32_t val2)
	{
		if (base && val < base->numEntries)
		{
			if (val2 > UINT16_MAX)
				val2 = UINT16_MAX;

			base->entries[val].count = val2;
		}
	}

	bool RegisterLeveledActor(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetLevFormCount), TESLevCharacter, uint32_t>                 ("GetNumForms", "LeveledActor", GetLevFormCount));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetLevForm),      TESLevCharacter, TESForm*, uint32_t>       ("GetNthForm",  "LeveledActor", GetLevForm));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetLev),          TESLevCharacter, uint32_t, uint32_t>       ("GetNthLevel", "LeveledActor", GetLev));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetLev),          TESLevCharacter, void, uint32_t, uint32_t> ("SetNthLevel", "LeveledActor", SetLev));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetLevCount),     TESLevCharacter, uint32_t, uint32_t>       ("GetNthCount", "LeveledActor", GetLevCount));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetLevCount),     TESLevCharacter, void, uint32_t, uint32_t> ("SetNthCount", "LeveledActor", SetLevCount));

		VM->SetCallableFromTasklets("LeveledActor", "GetNumForms", true);
		VM->SetCallableFromTasklets("LeveledActor", "GetNthForm",  true);
		VM->SetCallableFromTasklets("LeveledActor", "GetNthLevel", true);
		VM->SetCallableFromTasklets("LeveledActor", "SetNthLevel", true);
		VM->SetCallableFromTasklets("LeveledActor", "GetNthCount", true);
		VM->SetCallableFromTasklets("LeveledActor", "SetNthCount", true);
		
		return true;
	}
}