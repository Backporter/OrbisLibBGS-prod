#include "../Perk/PapyrusExtPerk.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"

#include "../../../../../../source/B/BGSPerk.h"
#include "../../../../../../source/B/BGSPerkEntry.h"
#include "../../../../../../source/B/BGSQuestPerkEntry.h"
#include "../../../../../../source/B/BGSAbilityPerkEntry.h"
#include "../../../../../../source/B/BGSEntryPointPerkEntry.h"
#include "../../../../../../source/B/BGSQuestPerkEntry.h"
#include "../../../../../../source/B/BGSEntryPointFunctionDataSpellItem.h"
#include "../../../../../../source/B/BGSEntryPointFunctionDataActivateChoice.h"
#include "../../../../../../source/B/BGSEntryPointFunctionDataLeveledList.h"
#include "../../../../../../source/B/BGSEntryPointFunctionDataText.h"
#include "../../../../../../source/B/BGSEntryPointFunctionDataBooleanGraphVariable.h"
#include "../../../../../../source/B/BGSEntryPointFunctionDataOneValue.h"
#include "../../../../../../source/B/BGSEntryPointFunctionDataTwoValue.h"

#include "../../../../../../source/S/SpellItem.h"
#include "../../../../../../source/T/TESLevItem.h"

namespace PapyrusExtPerk
{
	// I really hate doing this...
	using namespace ConsoleRE;

	BGSPerk* GetNextPerk(BGSPerk* base)
	{
		if (base)
		{
			return base->nextPerk;
		}

		return NULL;
	}

	uint32_t GetNumEntries(BGSPerk* base)
	{
		if (base)
		{
			return base->perkEntries.size();
		}

		return 0;
	}

	uint32_t GetNthEntryRank(BGSPerk* base, uint32_t val)
	{
		if (base)
		{
			BGSPerkEntry* entry = NULL;
			if (base->perkEntries.Get(val, entry))
			{
				return entry->rank;
			}

			return 0;
		}

		return 0;
	}

	uint32_t GetNthEntryPriority(BGSPerk* base, uint32_t val)
	{
		if (base)
		{
			BGSPerkEntry* entry = NULL;
			if (base->perkEntries.Get(val, entry))
			{
				return entry->priority;
			}

			return 0;
		}

		return 0;
	}

	TESQuest * GetNthEntryQuest(BGSPerk * perk, uint32_t n)
	{
		if (!perk)
			return NULL;

		BGSPerkEntry * perkEntry = NULL;
		if (!perk->perkEntries.Get(n, perkEntry))
			return NULL;

		BGSQuestPerkEntry * questEntry = TES_RTTI(perkEntry, BGSPerkEntry, BGSQuestPerkEntry);
		if (!questEntry)
			return NULL;

		return questEntry->quest;
	}

	uint32_t GetNthEntryStage(BGSPerk * perk, uint32_t n)
	{
		if (!perk)
			return 0;

		BGSPerkEntry * perkEntry = NULL;
		if (!perk->perkEntries.Get(n, perkEntry))
			return 0;

		BGSQuestPerkEntry * questEntry = TES_RTTI(perkEntry, BGSPerkEntry, BGSQuestPerkEntry);
		if (!questEntry)
			return 0;

		return questEntry->Unk18;
	}

	SpellItem * GetNthEntrySpell(BGSPerk * perk, uint32_t n)
	{
		if (!perk)
			return NULL;
		
		BGSPerkEntry * perkEntry = NULL;
		if (!perk->perkEntries.Get(n, perkEntry))
			return NULL;
		
		BGSAbilityPerkEntry * abilityEntry = TES_RTTI(perkEntry, BGSPerkEntry, BGSAbilityPerkEntry);
		if (abilityEntry)
			return abilityEntry->Unk10;
		
		BGSEntryPointPerkEntry * entryPointEntry = TES_RTTI(perkEntry, BGSPerkEntry, BGSEntryPointPerkEntry);
		if (entryPointEntry) 
		{
			BGSEntryPointFunctionDataSpellItem* functionDataSpell = TES_RTTI(entryPointEntry->functionData, BGSEntryPointFunctionData, BGSEntryPointFunctionDataSpellItem);
			if (functionDataSpell)
				return functionDataSpell->Unk08;
		
			BGSEntryPointFunctionDataActivateChoice* functionDataActivation = TES_RTTI(entryPointEntry->functionData, BGSEntryPointFunctionData, BGSEntryPointFunctionDataActivateChoice);
			if (functionDataActivation)
				return functionDataActivation->Unk18;
		}
		
		return NULL;
	}

	TESLevItem * GetNthEntryLeveledList(BGSPerk * perk, uint32_t n)
	{
		if (!perk)
			return NULL;

		BGSPerkEntry * perkEntry;
		if (!perk->perkEntries.Get(n, perkEntry))
			return NULL;

		BGSEntryPointPerkEntry * entryPointEntry = TES_RTTI(perkEntry, BGSPerkEntry, BGSEntryPointPerkEntry);
		if (entryPointEntry) 
		{
			BGSEntryPointFunctionDataLeveledList * functionDataLeveledList = TES_RTTI(entryPointEntry->functionData, BGSEntryPointFunctionData, BGSEntryPointFunctionDataLeveledList);
			if (functionDataLeveledList)
				return functionDataLeveledList->Unk08;
		}

		return NULL;
	}

	BSFixedString GetNthEntryText(BGSPerk * perk, uint32_t n)
	{
		if (!perk)
			return NULL;

		BGSPerkEntry* perkEntry = NULL;
		if (!perk->perkEntries.Get(n, perkEntry))
			return NULL;

		BGSEntryPointPerkEntry * entryPointEntry = TES_RTTI(perkEntry, BGSPerkEntry, BGSEntryPointPerkEntry);
		if (entryPointEntry) 
		{
			BGSEntryPointFunctionDataText* functionDataText = TES_RTTI(entryPointEntry->functionData, BGSEntryPointFunctionData, BGSEntryPointFunctionDataText);
			if (functionDataText)
				return functionDataText->Unk08;

			BGSEntryPointFunctionDataActivateChoice * functionDataActivation = TES_RTTI(entryPointEntry->functionData, BGSEntryPointFunctionData, BGSEntryPointFunctionDataActivateChoice);
			if (functionDataActivation)
				return functionDataActivation->Unk08;

			BGSEntryPointFunctionDataBooleanGraphVariable * functionDataGraphVar = TES_RTTI(entryPointEntry->functionData, BGSEntryPointFunctionData, BGSEntryPointFunctionDataBooleanGraphVariable);
			if (functionDataGraphVar)
				return functionDataGraphVar->Unk08;
		}

		return NULL;
	}

	float GetNthEntryValue(BGSPerk * perk, uint32_t n, uint32_t i)
	{
		if (!perk || i >= 2)
			return 0.0;

		BGSPerkEntry * perkEntry = NULL;
		if (!perk->perkEntries.Get(n, perkEntry))
			return 0.0f;

		BGSEntryPointPerkEntry * entryPointEntry = TES_RTTI(perkEntry, BGSPerkEntry, BGSEntryPointPerkEntry);
		if (entryPointEntry) 
		{
			BGSEntryPointFunctionDataOneValue * functionOne = TES_RTTI(entryPointEntry->functionData, BGSEntryPointFunctionData, BGSEntryPointFunctionDataOneValue);
			if (functionOne)
				return functionOne->Unk08;

			BGSEntryPointFunctionDataTwoValue * functionTwo = TES_RTTI(entryPointEntry->functionData, BGSEntryPointFunctionData, BGSEntryPointFunctionDataTwoValue);
			if (functionTwo)
				return functionTwo->Unk08[i];
		}

		return 0.0f;
	}

	bool SetNthEntryRank(BGSPerk * perk, uint32_t n, uint32_t value)
	{
		if (!perk)
			return false;

		BGSPerkEntry * perkEntry;
		if (perk->perkEntries.Get(n, perkEntry))
		{
			perkEntry->rank = value;
			return true;
		}

		return false;
	}

	bool SetNthEntryPriority(BGSPerk* base, uint32_t val, uint32_t val2)
	{
		if (base)
		{
			BGSPerkEntry* entry = NULL;
			if (base->perkEntries.Get(val, entry))
			{
				entry->priority = val2;
				return true;
			}

			return false;
		}

		return false;
	}

	bool SetNthEntryQuest(BGSPerk * perk, uint32_t n, TESQuest * quest)
	{
		if (!perk)
			return false;

		BGSPerkEntry * perkEntry = NULL;
		if (perk->perkEntries.Get(n, perkEntry))
		{
			BGSQuestPerkEntry * questEntry = TES_RTTI(perkEntry, BGSPerkEntry, BGSQuestPerkEntry);
			if (questEntry) 
			{
				questEntry->quest = quest;
				return true;
			}
		}

		return false;
	}
	
	bool SetNthEntryStage(BGSPerk * perk, uint32_t n, uint32_t stage)
	{
		if (!perk)
			return false;

		BGSPerkEntry * perkEntry = NULL;
		if (perk->perkEntries.Get(n, perkEntry))
		{
			BGSQuestPerkEntry * questEntry = TES_RTTI(perkEntry, BGSPerkEntry, BGSQuestPerkEntry);
			if (questEntry) 
			{
				questEntry->Unk18 = stage;
				return true;
			}
		}

		return false;
	}

	bool SetNthEntrySpell(BGSPerk * perk, uint32_t n, SpellItem * spell)
	{
		if (!perk)
			return false;

		BGSPerkEntry * perkEntry = NULL;
		if (perk->perkEntries.Get(n, perkEntry))
		{
			BGSAbilityPerkEntry * abilityEntry = TES_RTTI(perkEntry, BGSPerkEntry, BGSAbilityPerkEntry);
			if (abilityEntry) 
			{
				abilityEntry->Unk10 = spell;
				return true;
			}

			BGSEntryPointPerkEntry * entryPointEntry = TES_RTTI(perkEntry, BGSPerkEntry, BGSEntryPointPerkEntry);
			if (entryPointEntry) 
			{
				BGSEntryPointFunctionDataSpellItem * functionDataSpell = TES_RTTI(entryPointEntry->functionData, BGSEntryPointFunctionData, BGSEntryPointFunctionDataSpellItem);
				if (functionDataSpell) 
				{
					functionDataSpell->Unk08 = spell;
					return true;
				}

				BGSEntryPointFunctionDataActivateChoice * functionDataActivation = TES_RTTI(entryPointEntry->functionData, BGSEntryPointFunctionData, BGSEntryPointFunctionDataActivateChoice);
				if (functionDataActivation) 
				{
					functionDataActivation->Unk18 = spell;
					return true;
				}
			}
		}

		return false;
	}

	bool SetNthEntryLeveledList(BGSPerk * perk, uint32_t n, TESLevItem * leveledList)
	{
		if (!perk)
			return false;

		BGSPerkEntry * perkEntry = NULL;
		if (perk->perkEntries.Get(n, perkEntry))
		{
			BGSEntryPointPerkEntry * entryPointEntry = TES_RTTI(perkEntry, BGSPerkEntry, BGSEntryPointPerkEntry);
			if (entryPointEntry) 
			{
				BGSEntryPointFunctionDataLeveledList * functionDataLeveledList = TES_RTTI(entryPointEntry->functionData, BGSEntryPointFunctionData, BGSEntryPointFunctionDataLeveledList);
				if (functionDataLeveledList) 
				{
					functionDataLeveledList->Unk08 = leveledList;
					return true;
				}
			}
		}

		return false;
	}

	bool SetNthEntryText(BGSPerk * perk, uint32_t n, BSFixedString str)
	{
		if (!perk)
			return false;

		BGSPerkEntry * perkEntry = NULL;
		if (perk->perkEntries.Get(n, perkEntry))
		{
			BGSEntryPointPerkEntry * entryPointEntry = TES_RTTI(perkEntry, BGSPerkEntry, BGSEntryPointPerkEntry);
			if (entryPointEntry) 
			{
				BGSEntryPointFunctionDataText * functionDataText = TES_RTTI(entryPointEntry->functionData, BGSEntryPointFunctionData, BGSEntryPointFunctionDataText);
				if (functionDataText) 
				{
					functionDataText->Unk08 = str;
					return true;
				}

				BGSEntryPointFunctionDataActivateChoice * functionDataActivation = TES_RTTI(entryPointEntry->functionData, BGSEntryPointFunctionData, BGSEntryPointFunctionDataActivateChoice);
				if (functionDataActivation) 
				{
					functionDataActivation->Unk08 = str;
					return true;
				}

				BGSEntryPointFunctionDataBooleanGraphVariable * functionDataGraphVar = TES_RTTI(entryPointEntry->functionData, BGSEntryPointFunctionData, BGSEntryPointFunctionDataBooleanGraphVariable);
				if (functionDataGraphVar) 
				{
					functionDataGraphVar->Unk08 = str;
					return true;
				}
			}
		}

		return false;
	}

	bool SetNthEntryValue(BGSPerk * perk, uint32_t n, uint32_t i, float value)
	{
		if (perk && i < 2) 
		{
			BGSPerkEntry * perkEntry = NULL;
			if (perk->perkEntries.Get(n, perkEntry))
			{
				BGSEntryPointPerkEntry * entryPointEntry = TES_RTTI(perkEntry, BGSPerkEntry, BGSEntryPointPerkEntry);
				if (entryPointEntry) 
				{
					BGSEntryPointFunctionDataOneValue * functionOne = TES_RTTI(entryPointEntry->functionData, BGSEntryPointFunctionData, BGSEntryPointFunctionDataOneValue);
					if (functionOne) {
						functionOne->Unk08 = value;
						return true;
					}

					BGSEntryPointFunctionDataTwoValue * functionTwo = TES_RTTI(entryPointEntry->functionData, BGSEntryPointFunctionData, BGSEntryPointFunctionDataTwoValue);
					if (functionTwo) 
					{
						functionTwo->Unk08[i] = value;
						return true;
					}
				}
			}
		}

		return false;
	}

	bool RegisterPerk(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNextPerk),				BGSPerk, BGSPerk*>						 ("GetNextPerk",			"Perk", GetNextPerk));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNumEntries),				BGSPerk, uint32_t>						 ("GetNumEntries",			"Perk", GetNumEntries));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNthEntryRank),			BGSPerk, uint32_t, uint32_t>			 ("GetNthEntryRank",		"Perk", GetNthEntryRank));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNthEntryPriority),		BGSPerk, uint32_t, uint32_t>			 ("GetNthEntryPriority",	"Perk", GetNthEntryPriority));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNthEntryQuest),			BGSPerk, TESQuest*, uint32_t>			 ("GetNthEntryQuest",		"Perk", GetNthEntryQuest));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNthEntryStage),			BGSPerk, uint32_t, uint32_t>			 ("GetNthEntryStage",		"Perk", GetNthEntryStage));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNthEntrySpell),			BGSPerk, SpellItem*, uint32_t>			 ("GetNthEntrySpell",		"Perk", GetNthEntrySpell));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNthEntryLeveledList),	BGSPerk, TESLevItem*, uint32_t>			 ("GetNthEntryLeveledList", "Perk", GetNthEntryLeveledList));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNthEntryText),			BGSPerk, BSFixedString, uint32_t>		 ("GetNthEntryText",		"Perk", GetNthEntryText));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNthEntryValue),			BGSPerk, float, uint32_t, uint32_t>		 ("GetNthEntryValue",		"Perk", GetNthEntryValue));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetNthEntryRank),			BGSPerk, bool, uint32_t, uint32_t>		 ("SetNthEntryRank",		"Perk", SetNthEntryRank));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetNthEntryPriority),		BGSPerk, bool, uint32_t, uint32_t>		 ("SetNthEntryPriority",	"Perk", SetNthEntryPriority));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetNthEntryQuest),			BGSPerk, bool, uint32_t, TESQuest*>		 ("SetNthEntryQuest",		"Perk", SetNthEntryQuest));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetNthEntryStage),			BGSPerk, bool, uint32_t, uint32_t>		 ("SetNthEntryStage",		"Perk", SetNthEntryStage));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetNthEntrySpell),			BGSPerk, bool, uint32_t, SpellItem*>	 ("SetNthEntrySpell",		"Perk", SetNthEntrySpell));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetNthEntryLeveledList),	BGSPerk, bool, uint32_t, TESLevItem*>	 ("SetNthEntryLeveledList", "Perk", SetNthEntryLeveledList));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetNthEntryText),			BGSPerk, bool, uint32_t, BSFixedString>	 ("SetNthEntryText",		"Perk", SetNthEntryText));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetNthEntryValue),			BGSPerk, bool, uint32_t, uint32_t, float>("SetNthEntryValue",		"Perk", SetNthEntryValue));

		return true;
	}
}