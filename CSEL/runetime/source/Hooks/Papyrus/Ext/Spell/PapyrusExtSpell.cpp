#include "../Spell/PapyrusExtSpell.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/C/Character.h"
#include "../../../../../../source/E/EffectSetting.h"
#include "../../../../../../source/E/Effect.h"
#include "../../../../../../source/S/SpellItem.h"
#include "../../../../../../source/B/BGSEquipSlot.h"

#include "../../../../../../source/P/PackUnpackImpl.h"

#include <math.h>
#include <cmath>

namespace PapyrusExtSpell
{
	// I really hate doing this...
	using namespace ConsoleRE;

#pragma region 

	std::vector<float>          GetEffectMagnitudes(SpellItem* base)
	{
		std::vector<float> result;
		for (uint32_t i = 0; i < base->effects.size(); i++)
		{
			Effect* pEI = NULL;
			base->effects.Get(i, pEI);
			if (pEI)
				result.push_back(pEI->GetMagnitude());
			else
				result.push_back(0.0f);
		}
		return result;
	}

	std::vector<uint32_t>       GetEffectAreas(SpellItem* base)
	{
		std::vector<uint32_t> result;
		for (uint32_t i = 0; i < base->effects.size(); i++)
		{
			Effect* pEI = NULL;
			base->effects.Get(i, pEI);
			if (pEI)
				result.push_back(pEI->GetArea());
			else
				result.push_back(0);
		}
		return result;
	}

	std::vector<uint32_t>       GetEffectDurations(SpellItem* base)
	{
		std::vector<uint32_t> result;
		for (uint32_t i = 0; i < base->effects.size(); i++)
		{
			Effect* pEI = NULL;
			base->effects.Get(i, pEI);
			if (pEI)
				result.push_back(pEI->GetDuration());
			else
				result.push_back(0);
		}
		return result;
	}

	std::vector<EffectSetting*> GetMagicEffects(SpellItem* thisMagic)
	{
		std::vector<EffectSetting*> result;
		for (uint32_t i = 0; i < thisMagic->effects.size(); i++)
		{
			Effect* pEI = NULL;
			thisMagic->effects.Get(i, pEI);
			if (pEI)
				result.push_back(pEI->baseEffect);
			else
				result.push_back(NULL);
		}
		return result;
	}
#pragma endregion

	float	 GetSpellCastTime(SpellItem* base)
	{
		if (base)
		{
			return base->chargeTime;
		}

		return 0.0f;
	}

	BGSPerk* GetSpellPerk(SpellItem* base)
	{
		if (base)
		{
			return base->castingPerk;
		}

		return NULL;
	}

	uint32_t GetNumEffects(SpellItem* base)
	{
		if (base)
		{
			return base->effects.size();
		}

		return 0;
	}

	float GetNthEffectMagnitude(SpellItem* base, uint32_t index)
	{
		if (!base)
			return 0.0f;

		Effect* pEI = NULL;
		base->effects.Get(index, pEI);
		return (pEI) ? pEI->GetMagnitude() : 0.0;
	}

	uint32_t GetNthEffectArea(SpellItem* base, uint32_t index)
	{
		if (!base)
			return 0;

		Effect* pEI = NULL;
		base->effects.Get(index, pEI);
		return (pEI) ? pEI->GetArea() : 0.0;
	}

	uint32_t GetNthEffectDuration(SpellItem* base, uint32_t index)
	{
		if (!base)
			return 0;

		Effect* pEI = NULL;
		base->effects.Get(index, pEI);
		return (pEI) ? pEI->GetDuration() : 0.0;
	}

	EffectSetting* GetNthEffectMagicEffect(SpellItem* base, uint32_t index)
	{
		if (!base)
			return 0;

		Effect* pEI = NULL;
		base->effects.Get(index, pEI);
		return (pEI) ? pEI->baseEffect : NULL;
	}

	uint32_t GetCostliestEffectIndex(SpellItem* base)
	{
		if (!base)
			return 0;
	
		Effect * pEI = base->GetCostliestEffectItem(5, false);
		return pEI ? base->effects.Get(pEI) : 0;
	}

	uint32_t GetMagickaCost(SpellItem* base)
	{
		if (base)
		{
			return base->costOverride;
		}

		return 0;
	}

	uint32_t GetEffectiveMagickaCost(SpellItem* base, Character* caster)
	{
		if (base)
		{
			return base->GetEffectiveMagickaCost(caster);
		}

		return 0;
	}

	void SetNthEffectMagnitude(SpellItem* base, uint32_t index, float value)
	{
		if (base)
		{
			Effect* pEI = NULL;
			base->effects.Get(index, pEI);
			if (pEI)
				pEI->SetMagnitude(value);
		}
	}

	void SetNthEffectArea(SpellItem* base, uint32_t index, uint32_t value)
	{
		if (base)
		{
			Effect* pEI = NULL;
			base->effects.Get(index, pEI);
			if (pEI)
				pEI->SetArea(value);
		}
	}

	void SetNthEffectDuration(SpellItem* base, uint32_t index, uint32_t value)
	{
		if (base) 
		{
			Effect* pEI = NULL;
			base->effects.Get(index, pEI);
			if (pEI)
				pEI->SetDuration(value);
		}
	}

	BGSEquipSlot * GetEquipType(SpellItem* base)
	{
		if (base)
		{
			return base->equipSlot;
		}

		return NULL;
	}

	void SetEquipType(SpellItem* base, BGSEquipSlot * slot)
	{
		if (base && slot)
		{
			base->equipSlot = slot;
		}
	}

	bool RegisterSpell(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		//
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetEffectMagnitudes),		SpellItem, std::vector<float>>			   ("GetEffectMagnitudes",     "Spell", GetEffectMagnitudes));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetEffectAreas),			SpellItem, std::vector<uint32_t>>		   ("GetEffectAreas",          "Spell", GetEffectAreas));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetEffectDurations),		SpellItem, std::vector<uint32_t>>		   ("GetEffectDurations",      "Spell", GetEffectDurations));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetMagicEffects),			SpellItem, std::vector<EffectSetting*>>	   ("GetMagicEffects",         "Spell", GetMagicEffects));
		//

		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetSpellCastTime),          SpellItem, float>						   ("GetCastTime",             "Spell", GetSpellCastTime));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetSpellPerk),              SpellItem, BGSPerk*>					   ("GetPerk",                 "Spell", GetSpellPerk));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNumEffects),             SpellItem, uint32_t>					   ("GetNumEffects",           "Spell", GetNumEffects));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNthEffectMagnitude),     SpellItem, float, uint32_t>				   ("GetNthEffectMagnitude",   "Spell", GetNthEffectMagnitude));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNthEffectArea),          SpellItem, uint32_t, uint32_t>			   ("GetNthEffectArea",        "Spell", GetNthEffectArea));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNthEffectDuration),      SpellItem, uint32_t, uint32_t>			   ("GetNthEffectDuration",    "Spell", GetNthEffectDuration));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNthEffectMagicEffect),   SpellItem, EffectSetting*, uint32_t>	   ("GetNthEffectMagicEffect", "Spell", GetNthEffectMagicEffect));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetCostliestEffectIndex),   SpellItem, uint32_t>					   ("GetCostliestEffectIndex", "Spell", GetCostliestEffectIndex));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetMagickaCost),            SpellItem, uint32_t>					   ("GetMagickaCost",          "Spell", GetMagickaCost));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetEffectiveMagickaCost),   SpellItem, uint32_t, Character*>		   ("GetEffectiveMagickaCost", "Spell", GetEffectiveMagickaCost));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetNthEffectMagnitude),     SpellItem, void, uint32_t, float>		   ("SetNthEffectMagnitude",   "Spell", SetNthEffectMagnitude));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetNthEffectArea),          SpellItem, void, uint32_t, uint32_t>	   ("SetNthEffectArea",        "Spell", SetNthEffectArea));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetNthEffectDuration),      SpellItem, void, uint32_t, uint32_t>	   ("SetNthEffectDuration",    "Spell", SetNthEffectDuration));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetEquipType),              SpellItem, BGSEquipSlot*>				   ("GetEquipType",            "Spell", GetEquipType));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetEquipType),              SpellItem, void, BGSEquipSlot*>			   ("SetEquipType",            "Spell", SetEquipType));

		VM->SetCallableFromTasklets("Spell", "GetCastTime",             true);
		VM->SetCallableFromTasklets("Spell", "GetPerk",                 true);
		VM->SetCallableFromTasklets("Spell", "GetNumEffects",           true);
		VM->SetCallableFromTasklets("Spell", "GetNthEffectMagnitude",   true);
		VM->SetCallableFromTasklets("Spell", "GetNthEffectArea",        true);
		VM->SetCallableFromTasklets("Spell", "GetNthEffectDuration",    true);
		VM->SetCallableFromTasklets("Spell", "GetNthEffectMagicEffect", true);
		VM->SetCallableFromTasklets("Spell", "GetCostliestEffectIndex", true);
		VM->SetCallableFromTasklets("Spell", "GetMagickaCost",          true);
		VM->SetCallableFromTasklets("Spell", "GetEffectiveMagickaCost", true);
		VM->SetCallableFromTasklets("Spell", "SetNthEffectMagnitude",   true);
		VM->SetCallableFromTasklets("Spell", "SetNthEffectArea",        true);
		VM->SetCallableFromTasklets("Spell", "SetNthEffectDuration",    true);
		VM->SetCallableFromTasklets("Spell", "GetEquipType",            true);
		VM->SetCallableFromTasklets("Spell", "SetEquipType",            true);
		VM->SetCallableFromTasklets("Spell", "GetEffectMagnitudes",     true);
		VM->SetCallableFromTasklets("Spell", "GetEffectAreas",          true);
		VM->SetCallableFromTasklets("Spell", "GetEffectDurations",      true);
		VM->SetCallableFromTasklets("Spell", "GetMagicEffects",         true);

		return true;
	}
}