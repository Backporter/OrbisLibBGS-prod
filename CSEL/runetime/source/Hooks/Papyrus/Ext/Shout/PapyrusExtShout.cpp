#include "../Shout/PapyrusExtShout.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"

#include "../../../../../../source/T/TESWordOfPower.h"
#include "../../../../../../source/T/TESShout.h"
#include "../../../../../../source/S/SpellItem.h"

namespace PapyrusExtShout
{
	using namespace ConsoleRE;

	TESWordOfPower* GetWordOfPowerFromInded(TESShout* base, uint32_t val)
	{
		if (base && val < 3)
		{
			return base->words[val].word;
		}

		return NULL;
	}
	
	SpellItem* GetSpell(TESShout* base, uint32_t val)
	{
		if (base && val < 3)
		{
			return base->words[val].spell;
		}

		return NULL;
	}

	float GetRecoveryTime(TESShout* base, uint32_t val)
	{
		if (base && val < 3)
		{
			return base->words[val].recoveryTime;
		}

		return 0.0f;
	}

	void SetWordOfPower(TESShout* base, uint32_t val, TESWordOfPower* word)
	{
		if (base && val < 3)
		{
			base->words[val].word = word;
		}
	}

	void SetSpell(TESShout* base, uint32_t val, SpellItem* spell)
	{
		if (base && val < 3)
		{
			base->words[val].spell = spell;
		}
	}

	void SetRecoveryTime(TESShout* base, uint32_t val, float time)
	{
		if (base && val < 3)
		{
			base->words[val].recoveryTime = time;
		}
	}
	
	bool RegisterShout(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetWordOfPowerFromInded),	TESShout, TESWordOfPower*, uint32_t>		 ("GetNthWordOfPower",       "Shout", GetWordOfPowerFromInded));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetSpell),					TESShout, SpellItem*, uint32_t>			     ("GetNthSpell",			 "Shout", GetSpell));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetRecoveryTime),			TESShout, float, uint32_t>					 ("GetNthRecoveryTime",		 "Shout", GetRecoveryTime));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetWordOfPower),			TESShout, void, uint32_t, TESWordOfPower*>   ("SetNthWordOfPower",		 "Shout", SetWordOfPower));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetSpell),					TESShout, void, uint32_t, SpellItem*>	     ("SetNthSpell",		     "Shout", SetSpell));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetRecoveryTime),			TESShout, void, uint32_t, float>			 ("SetNthRecoveryTime",      "Shout", SetRecoveryTime));

		VM->SetCallableFromTasklets("Shout", "GetNthWordOfPower",  true);
		VM->SetCallableFromTasklets("Shout", "GetNthSpell",		true);
		VM->SetCallableFromTasklets("Shout", "GetNthRecoveryTime", true);
		VM->SetCallableFromTasklets("Shout", "SetNthWordOfPower",  true);
		VM->SetCallableFromTasklets("Shout", "SetNthSpell",		true);
		VM->SetCallableFromTasklets("Shout", "SetNthRecoveryTime", true);
		return true;
	}
}