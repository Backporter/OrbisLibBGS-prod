#include "../Scroll/PapyrusExtScroll.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/S/ScrollItem.h"
#include "../../../../../../source/E/EffectSetting.h"
#include "../../../../../../source/B/BGSEquipSlot.h"
#include "../../../../../../source/E/Effect.h"
#include "../../../../../../source/P/PackUnpackImpl.h"

namespace PapyrusExtScroll
{
	// I really hate doing this...
	using namespace ConsoleRE;

#pragma region
	std::vector<float> GetEffectMagnitudes(ScrollItem* thisMagic)
	{
		std::vector<float> result;
		for (uint32_t i = 0; i < thisMagic->effects.size(); i++)
		{
			Effect* pEI = NULL;
			thisMagic->effects.Get(i, pEI);

			if (pEI)
				result.push_back(pEI->GetMagnitude());
			else
				result.push_back(0.0f);
		}
		return result;
	}

	std::vector<uint32_t> GetEffectAreas(ScrollItem* thisMagic)
	{
		std::vector<uint32_t> result;
		for (uint32_t i = 0; i < thisMagic->effects.size(); i++)
		{
			Effect* pEI = NULL;
			thisMagic->effects.Get(i, pEI);

			if (pEI)
				result.push_back(pEI->GetArea());
			else
				result.push_back(0);
		}
		return result;
	}

	std::vector<uint32_t> GetEffectDurations(ScrollItem* thisMagic)
	{
		std::vector<uint32_t> result;
		for (uint32_t i = 0; i < thisMagic->effects.size(); i++)
		{
			Effect* pEI = NULL;
			thisMagic->effects.Get(i, pEI);

			if (pEI)
				result.push_back(pEI->GetDuration());
			else
				result.push_back(0);
		}
		return result;
	}

	std::vector<EffectSetting*> GetMagicEffects(ScrollItem* thisMagic)
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

	float GetCastTime(ScrollItem* thisSpell)
	{
		return (thisSpell) ? thisSpell->chargeTime : 0.0;
	}

	BGSPerk* GetPerk(ScrollItem* thisSpell)
	{
		return (thisSpell) ? thisSpell->castingPerk : NULL;
	}

	//
	uint32_t GetNumEffects(ScrollItem* thisMagic)
	{
		if (thisMagic)
		{
			return thisMagic->effects.size();
		}

		return 0;
	}

	float GetNthEffectMagnitude(ScrollItem* thisMagic, uint32_t index)
	{
		if (!thisMagic)
			return 0.0;

		Effect* pEI = NULL;
		thisMagic->effects.Get(index, pEI);
		return (pEI) ? pEI->GetMagnitude() : 0.0f;
	}

	uint32_t GetNthEffectArea(ScrollItem* thisMagic, uint32_t index)
	{
		if (!thisMagic)
			return 0;

		Effect* pEI = NULL;
		thisMagic->effects.Get(index, pEI);
		return (pEI) ? pEI->GetArea() : 0;
	}

	uint32_t GetNthEffectDuration(ScrollItem* thisMagic, uint32_t index)
	{
		if (!thisMagic)
			return 0;

		Effect* pEI = NULL;
		thisMagic->effects.Get(index, pEI);
		return (pEI) ? pEI->GetDuration() : 0;
	}

	EffectSetting* GetNthEffectMagicEffect(ScrollItem* thisMagic, uint32_t index)
	{
		if (!thisMagic)
			return NULL;

		Effect* pEI = NULL;
		thisMagic->effects.Get(index, pEI);
		return (pEI) ? pEI->baseEffect : NULL;
	}

	uint32_t GetCostliestEffectIndex(ScrollItem* thisMagic)
	{
		if (!thisMagic)
			return 0;
	
		Effect * pEI = thisMagic->GetCostliestEffectItem(5, false);
		return pEI ? thisMagic->effects.Get(pEI) : 0;
	}

	void SetNthEffectMagnitude(ScrollItem* thisMagic, uint32_t index, float value)
	{
		if (thisMagic)
		{
			Effect* pEI = NULL;
			thisMagic->effects.Get(index, pEI);
			if (pEI)
				pEI->SetMagnitude(value);
		}
	}

	void SetNthEffectArea(ScrollItem* thisMagic, uint32_t index, uint32_t value)
	{
		if (thisMagic) 
		{
			Effect* pEI = NULL;
			thisMagic->effects.Get(index, pEI);
			if (pEI)
				pEI->SetArea(value);
		}
	}

	void SetNthEffectDuration(ScrollItem* thisMagic, uint32_t index, uint32_t value)
	{
		if (thisMagic) {
			Effect* pEI = NULL;
			thisMagic->effects.Get(index, pEI);
			if (pEI)
				pEI->SetDuration(value);
		}
	}

	BGSEquipSlot * GetEquipType(ScrollItem* thisMagic)
	{
		if (thisMagic) 
		{
			return thisMagic->equipSlot;
		}

		// Invalid EquipSlot
		return NULL;
	}

	void SetEquipType(ScrollItem* thisMagic, BGSEquipSlot * slot)
	{
		if (thisMagic && slot) 
		{
			thisMagic->equipSlot = slot;
		}
	}

	bool RegisterScroll(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		//
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetEffectMagnitudes),			ScrollItem, std::vector<float>>				("GetEffectMagnitudes",		"Scroll", GetEffectMagnitudes));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetEffectAreas),				ScrollItem, std::vector<uint32_t>>			("GetEffectAreas",			"Scroll", GetEffectAreas));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetEffectDurations),			ScrollItem, std::vector<uint32_t>>			("GetEffectDurations",		"Scroll", GetEffectDurations));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetMagicEffects),				ScrollItem, std::vector<EffectSetting*>>	("GetMagicEffects",			"Scroll", GetMagicEffects));
		//

		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetCastTime),                ScrollItem, float>							("GetCastTime",             "Scroll", GetCastTime));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetNumEffects),              ScrollItem, uint32_t>						("GetNumEffects",           "Scroll", GetNumEffects));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetNthEffectMagnitude),      ScrollItem, float, uint32_t>					("GetNthEffectMagnitude",   "Scroll", GetNthEffectMagnitude));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetNthEffectArea),           ScrollItem, uint32_t, uint32_t>				("GetNthEffectArea",        "Scroll", GetNthEffectArea));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetNthEffectDuration),       ScrollItem, uint32_t, uint32_t>				("GetNthEffectDuration",    "Scroll", GetNthEffectDuration));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetNthEffectMagicEffect),    ScrollItem, EffectSetting*, uint32_t>		("GetNthEffectMagicEffect", "Scroll", GetNthEffectMagicEffect));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetCostliestEffectIndex),	   ScrollItem, uint32_t>						("GetCostliestEffectIndex", "Scroll", GetCostliestEffectIndex));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(SetNthEffectMagnitude),      ScrollItem, void, uint32_t, float>			("SetNthEffectMagnitude",   "Scroll", SetNthEffectMagnitude));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(SetNthEffectArea),           ScrollItem, void, uint32_t, uint32_t>		("SetNthEffectArea",        "Scroll", SetNthEffectArea));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(SetNthEffectDuration),       ScrollItem, void, uint32_t, uint32_t>		("SetNthEffectDuration",    "Scroll", SetNthEffectDuration));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetEquipType),               ScrollItem, BGSEquipSlot*>					("GetEquipType",            "Scroll", GetEquipType));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(SetEquipType),               ScrollItem, void, BGSEquipSlot*>				("SetEquipType",            "Scroll", SetEquipType));

		VM->SetCallableFromTasklets("Scroll", "GetCastTime", true);
		VM->SetCallableFromTasklets("Scroll", "GetNumEffects", true);
		VM->SetCallableFromTasklets("Scroll", "GetNthEffectMagnitude", true);
		VM->SetCallableFromTasklets("Scroll", "GetNthEffectArea", true);
		VM->SetCallableFromTasklets("Scroll", "GetNthEffectDuration", true);
		VM->SetCallableFromTasklets("Scroll", "GetNthEffectMagicEffect", true);
		VM->SetCallableFromTasklets("Scroll", "GetCostliestEffectIndex", true);
		VM->SetCallableFromTasklets("Scroll", "GetEquipType", true);
		VM->SetCallableFromTasklets("Scroll", "SetNthEffectMagnitude", true);
		VM->SetCallableFromTasklets("Scroll", "SetNthEffectArea", true);
		VM->SetCallableFromTasklets("Scroll", "SetNthEffectDuration", true);
		VM->SetCallableFromTasklets("Scroll", "SetEquipType", true);
		VM->SetCallableFromTasklets("Scroll", "GetEffectMagnitudes", true);
		VM->SetCallableFromTasklets("Scroll", "GetEffectAreas", true);
		VM->SetCallableFromTasklets("Scroll", "GetEffectDurations", true);
		VM->SetCallableFromTasklets("Scroll", "GetMagicEffects", true);

		return true;
	}
}