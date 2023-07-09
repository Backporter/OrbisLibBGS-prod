#include "../Tree/PapyrusExtTree.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESObjectTREE.h"
#include "../../../../../../source/T/TESForm.h"
#include "../../../../../../source/B/BGSSoundDescriptorForm.h"
#include "../../../../../../source/T/TESProduceForm.h"

namespace PapyrusExtTree
{
	// I really hate doing this...
	using namespace ConsoleRE;

	TESForm*				 GetIngredient(TESObjectTREE* base)
	{
		if (base)
		{
			return base->produceItem;
		}

		return NULL;
	}

	void					 SetIngredient(TESObjectTREE* base, TESBoundObject* ingredient)
	{
		if (base) 
		{
			base->produceItem = ingredient;
		}
	}

	BGSSoundDescriptorForm*  GetHarvestSound(TESObjectTREE* base)
	{
		if (base)
		{
			return base->harvestSound;
		}

		return NULL;	
	}

	void					 SetHarvestSound(TESObjectTREE* base, BGSSoundDescriptorForm * sound)
	{
		if (base)
		{
			base->harvestSound = sound;
		}
	}

	bool RegisterTree(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetIngredient),   TESObjectTREE, TESForm*>							("GetIngredient",   "TreeObject", GetIngredient));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetIngredient),   TESObjectTREE, void, TESBoundObject*>				("SetIngredient",   "TreeObject", SetIngredient));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetHarvestSound), TESObjectTREE, BGSSoundDescriptorForm*>			("GetHarvestSound", "TreeObject", GetHarvestSound));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetHarvestSound), TESObjectTREE, void, BGSSoundDescriptorForm*>		("SetHarvestSound", "TreeObject", SetHarvestSound));
		return true;
	}
}