#include "../Flora/PapyrusExtFlora.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESFlora.h"
#include "../../../../../../source/T/TESForm.h"
#include "../../../../../../source/B/BGSSoundDescriptorForm.h"

namespace PapyrusExtFlora
{
	// I really hate doing this...
	using namespace ConsoleRE;

	TESBoundObject*				GetIngredient(TESFlora* base)
	{
		if (base)
		{
			return base->produceItem;
		}

		return NULL;
	}

	void					SetIngredient(TESFlora* base, TESBoundObject* ingredient)
	{
		if (base)
		{
			base->produceItem = ingredient;
		}
	}

	BGSSoundDescriptorForm* GetHarvestSound(TESFlora* base)
	{
		if (base)
		{
			return base->harvestSound;
		}

		return NULL;
	}

	void					SetHarvestSound(TESFlora* base, BGSSoundDescriptorForm* sound)
	{
		if (base) 
		{
			base->harvestSound = sound;
		}
	}

	bool RegisterFlora(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetIngredient),   TESFlora, TESBoundObject*>			    ("GetIngredient",   "Flora", GetIngredient));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetIngredient),   TESFlora, void, TESBoundObject*>			("SetIngredient",   "Flora", SetIngredient));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetHarvestSound), TESFlora, BGSSoundDescriptorForm*>		("GetHarvestSound", "Flora", GetHarvestSound));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetHarvestSound), TESFlora, void, BGSSoundDescriptorForm*>	("SetHarvestSound", "Flora", SetHarvestSound));

		return true;
	}
}