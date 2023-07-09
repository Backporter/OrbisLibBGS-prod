#include "../Ingredient/PapyrusExtIngredient.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/I/IngredientItem.h"
#include "../../../../../../source/E/Effect.h"
#include "../../../../../../source/E/EffectSetting.h"
#include "../../../../../../source/P/PackUnpackImpl.h"

namespace PapyrusExtIngredient
{
	// I really hate doing this...
	using namespace ConsoleRE;

#pragma region
	std::vector<float>          GetEffectMagnitudes(IngredientItem* thisMagic)
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

	std::vector<uint32_t>       GetEffectAreas(IngredientItem* thisMagic)
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

	std::vector<uint32_t>       GetEffectDurations(IngredientItem* thisMagic)
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

	std::vector<EffectSetting*> GetMagicEffects(IngredientItem* thisMagic)
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

	uint32_t GetNumEffects(IngredientItem* thisMagic)
	{
		if (thisMagic)
		{
			return thisMagic->effects.size();
		}

		return 0;
	}

	float GetNthEffectMagnitude(IngredientItem* thisMagic, uint32_t index)
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

	uint32_t GetNthEffectArea(IngredientItem* thisMagic, uint32_t index)
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

	uint32_t GetNthEffectDuration(IngredientItem* thisMagic, uint32_t index)
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

	EffectSetting* GetNthEffectMagicEffect(IngredientItem* thisMagic, uint32_t index)
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

	uint32_t GetCostliestEffectIndex(IngredientItem* thisMagic)
	{
		if (thisMagic)
		{
			Effect* pEI = thisMagic->GetCostliestEffectItem(5, false);
			if (pEI)
				return thisMagic->effects.Get(pEI);

		}

		return 0;
	}

	void SetNthEffectMagnitude(IngredientItem* thisMagic, uint32_t index, float value)
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

	void SetNthEffectArea(IngredientItem* thisMagic, uint32_t index, uint32_t value)
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

	void SetNthEffectDuration(IngredientItem* thisMagic, uint32_t index, uint32_t value)
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

	bool GetIsNthEffectKnown(IngredientItem* thisMagic, uint32_t index)
	{
		if (thisMagic)
		{
			bool isKnown = false;

			switch (index)
			{
			case 0:
				isKnown = ((thisMagic->gamedata.knownEffectFlags & 1) == 1);
				break;
			case 1:
				isKnown = ((thisMagic->gamedata.knownEffectFlags & 2) == 2);
				break;
			case 2:
				isKnown = ((thisMagic->gamedata.knownEffectFlags & 4) == 4);
				break;
			case 3:
				isKnown = ((thisMagic->gamedata.knownEffectFlags & 8) == 8);
				break;
			default:
				break;
			}
			return isKnown;
		}

		return false;

	}

	bool RegisterIngredient(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		//
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetEffectMagnitudes),		IngredientItem, std::vector<float>>				("GetEffectMagnitudes",		 "Ingredient", GetEffectMagnitudes));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetEffectAreas),			IngredientItem, std::vector<uint32_t>>			("GetEffectAreas",			 "Ingredient", GetEffectAreas));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetEffectDurations),		IngredientItem, std::vector<uint32_t>>			("GetEffectDurations",		 "Ingredient", GetEffectDurations));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetMagicEffects),			IngredientItem, std::vector<EffectSetting*>>	("GetMagicEffects",			 "Ingredient", GetMagicEffects));
		//

		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNumEffects),            IngredientItem, uint32_t>						("GetNumEffects",            "Ingredient", GetNumEffects));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthEffectMagnitude),    IngredientItem, float, uint32_t>				("GetNthEffectMagnitude",    "Ingredient", GetNthEffectMagnitude));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthEffectArea),         IngredientItem, uint32_t, uint32_t>				("GetNthEffectArea",         "Ingredient", GetNthEffectArea));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthEffectDuration),     IngredientItem, uint32_t, uint32_t>				("GetNthEffectDuration",     "Ingredient", GetNthEffectDuration));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthEffectMagicEffect),  IngredientItem, EffectSetting*, uint32_t>		("GetNthEffectMagicEffect",  "Ingredient", GetNthEffectMagicEffect));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetCostliestEffectIndex),  IngredientItem, uint32_t>						("GetCostliestEffectIndex",  "Ingredient", GetCostliestEffectIndex));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetIsNthEffectKnown),      IngredientItem, bool, uint32_t>					("GetIsNthEffectKnown",      "Ingredient", GetIsNthEffectKnown));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetNthEffectMagnitude),    IngredientItem, void, uint32_t, float>			("SetNthEffectMagnitude",    "Ingredient", SetNthEffectMagnitude));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetNthEffectArea),         IngredientItem, void, uint32_t, uint32_t>		("SetNthEffectArea",         "Ingredient", SetNthEffectArea));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetNthEffectDuration),     IngredientItem, void, uint32_t, uint32_t>		("SetNthEffectDuration",     "Ingredient", SetNthEffectDuration));
		
		VM->SetCallableFromTasklets("Ingredient", "GetNumEffects", true);
		VM->SetCallableFromTasklets("Ingredient", "GetNthEffectMagnitude", true);
		VM->SetCallableFromTasklets("Ingredient", "GetNthEffectArea", true);
		VM->SetCallableFromTasklets("Ingredient", "GetNthEffectDuration", true);
		VM->SetCallableFromTasklets("Ingredient", "GetNthEffectMagicEffect", true);
		VM->SetCallableFromTasklets("Ingredient", "GetCostliestEffectIndex", true);
		VM->SetCallableFromTasklets("Ingredient", "GetIsNthEffectKnown", true);
		VM->SetCallableFromTasklets("Ingredient", "SetNthEffectMagnitude", true);
		VM->SetCallableFromTasklets("Ingredient", "SetNthEffectArea", true);
		VM->SetCallableFromTasklets("Ingredient", "SetNthEffectDuration", true);
		VM->SetCallableFromTasklets("Ingredient", "GetEffectMagnitudes", true);
		VM->SetCallableFromTasklets("Ingredient", "GetEffectAreas", true);
		VM->SetCallableFromTasklets("Ingredient", "GetEffectDurations", true);
		VM->SetCallableFromTasklets("Ingredient", "GetMagicEffects", true);

		return true;
	}
}