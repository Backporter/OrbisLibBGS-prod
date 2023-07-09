#include "../Potion/PapyrusExtPotion.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/A/AlchemyItem.h"
#include "../../../../../../source/E/Effect.h"
#include "../../../../../../source/E/EffectSetting.h"
#include "../../../../../../source/P/PackUnpackImpl.h"

namespace PapyrusExtPotion
{
	// I really hate doing this...
	using namespace ConsoleRE;

#pragma region
	std::vector<float> GetEffectMagnitudes(AlchemyItem* thisMagic)
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

	std::vector<uint32_t> GetEffectAreas(AlchemyItem* thisMagic)
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

	std::vector<uint32_t> GetEffectDurations(AlchemyItem* thisMagic)
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

	std::vector<EffectSetting*> GetMagicEffects(AlchemyItem* thisMagic)
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

	bool IsFood(AlchemyItem* thisPotion)
	{
		return (thisPotion) ? thisPotion->Is(2) : false;
	}

	bool IsPoison(AlchemyItem* thisPotion)
	{
		return (thisPotion) ? thisPotion->Is(0x00020000) : false;
	}

	BGSSoundDescriptorForm* GetUseSound(AlchemyItem* thisPotion)
	{
		return (thisPotion) ? thisPotion->data.consumptionSound : NULL;
	}

	uint32_t GetNumEffects(AlchemyItem* thisMagic)
	{
		if (thisMagic)
		{
			return thisMagic->effects.size();
		}

		return 0;
	}

	float GetNthEffectMagnitude(AlchemyItem* thisMagic, uint32_t index)
	{
		if (thisMagic)
		{
			Effect* pEI = NULL;
			thisMagic->effects.Get(index, pEI);
			if (pEI)
			{
				return pEI->GetMagnitude();
			}
		}

		return 0;
	}

	uint32_t GetNthEffectArea(AlchemyItem* thisMagic, uint32_t index)
	{
		if (thisMagic)
		{
			Effect* pEI = NULL;
			thisMagic->effects.Get(index, pEI);
			if (pEI)
			{
				return pEI->GetArea();
			}
		}

		return 0;
	}

	uint32_t GetNthEffectDuration(AlchemyItem* thisMagic, uint32_t index)
	{
		if (thisMagic)
		{
			Effect* pEI = NULL;
			thisMagic->effects.Get(index, pEI);
			if (pEI)
			{
				return pEI->GetDuration();
			}
		}

		return 0;
	}

	EffectSetting* GetNthEffectMagicEffect(AlchemyItem* thisMagic, uint32_t index)
	{
		if (thisMagic)
		{
			Effect* pEI = NULL;
			thisMagic->effects.Get(index, pEI);
			if (pEI)
			{
				return pEI->baseEffect;
			}
		}

		return 0;
	}

	uint32_t GetCostliestEffectIndex(AlchemyItem* thisMagic)
	{
		if (thisMagic)
		{
			Effect * pEI = thisMagic->GetCostliestEffectItem(5, false);
			if (pEI)
			{
				return thisMagic->effects.Get(pEI);
			}
		}

		return 0;
	}

	void SetNthEffectMagnitude(AlchemyItem* thisMagic, uint32_t index, float value)
	{
		if (thisMagic)
		{
			Effect* pEI = NULL;
			thisMagic->effects.Get(index, pEI);
			if (pEI)
			{
				pEI->SetMagnitude(value);
			}
		}
	}

	void SetNthEffectArea(AlchemyItem* thisMagic, uint32_t index, uint32_t value)
	{
		if (thisMagic)
		{
			Effect* pEI = NULL;
			thisMagic->effects.Get(index, pEI);
			if (pEI)
			{
				pEI->SetArea(value);
			}
		}
	}

	void SetNthEffectDuration(AlchemyItem* thisMagic, uint32_t index, uint32_t value)
	{
		if (thisMagic)
		{
			Effect* pEI = NULL;
			thisMagic->effects.Get(index, pEI);
			if (pEI)
			{
				pEI->SetDuration(value);
			}
		}
	}

	bool RegisterPotion(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		//
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetEffectMagnitudes),	   AlchemyItem, std::vector<float>>				("GetEffectMagnitudes",		"Potion", GetEffectMagnitudes));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetEffectAreas),		   AlchemyItem, std::vector<uint32_t>>			("GetEffectAreas",			"Potion", GetEffectAreas));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetEffectDurations),	   AlchemyItem, std::vector<uint32_t>>			("GetEffectDurations",		"Potion", GetEffectDurations));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetMagicEffects),		   AlchemyItem, std::vector<EffectSetting*>>	("GetMagicEffects",			"Potion", GetMagicEffects));
		//

		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(IsFood),                  AlchemyItem, bool>							("IsFood",                  "Potion", IsFood));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(IsPoison),                AlchemyItem, bool>							("IsPoison",                "Potion", IsPoison));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNumEffects),           AlchemyItem, uint32_t>						("GetNumEffects",           "Potion", GetNumEffects));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthEffectMagnitude),   AlchemyItem, float, uint32_t>				("GetNthEffectMagnitude",   "Potion", GetNthEffectMagnitude));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthEffectArea),        AlchemyItem, uint32_t, uint32_t>				("GetNthEffectArea",        "Potion", GetNthEffectArea));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthEffectDuration),    AlchemyItem, uint32_t, uint32_t>				("GetNthEffectDuration",    "Potion", GetNthEffectDuration));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthEffectMagicEffect), AlchemyItem, EffectSetting*, uint32_t>		("GetNthEffectMagicEffect", "Potion", GetNthEffectMagicEffect));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetCostliestEffectIndex), AlchemyItem, uint32_t>						("GetCostliestEffectIndex", "Potion", GetCostliestEffectIndex));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetUseSound),             AlchemyItem, BGSSoundDescriptorForm*>		("GetUseSound",             "Potion", GetUseSound));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetNthEffectMagnitude),   AlchemyItem, void, uint32_t, float>			("SetNthEffectMagnitude",   "Potion", SetNthEffectMagnitude));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetNthEffectArea),        AlchemyItem, void, uint32_t, uint32_t>		("SetNthEffectArea",        "Potion", SetNthEffectArea));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetNthEffectDuration),    AlchemyItem, void, uint32_t, uint32_t>		("SetNthEffectDuration",    "Potion", SetNthEffectDuration));
		
		VM->SetCallableFromTasklets("Potion", "IsFood", true);
		VM->SetCallableFromTasklets("Potion", "GetNumEffects", true);
		VM->SetCallableFromTasklets("Potion", "GetNthEffectMagnitude", true);
		VM->SetCallableFromTasklets("Potion", "GetNthEffectArea", true);
		VM->SetCallableFromTasklets("Potion", "GetNthEffectDuration", true);
		VM->SetCallableFromTasklets("Potion", "GetNthEffectMagicEffect", true);
		VM->SetCallableFromTasklets("Potion", "GetCostliestEffectIndex", true);
		VM->SetCallableFromTasklets("Potion", "SetNthEffectMagnitude", true);
		VM->SetCallableFromTasklets("Potion", "SetNthEffectArea", true);
		VM->SetCallableFromTasklets("Potion", "SetNthEffectDuration", true);
		VM->SetCallableFromTasklets("Potion", "GetEffectMagnitudes", true);
		VM->SetCallableFromTasklets("Potion", "GetEffectAreas", true);
		VM->SetCallableFromTasklets("Potion", "GetEffectDurations", true);
		VM->SetCallableFromTasklets("Potion", "GetMagicEffects", true);

		return true;
	}
}