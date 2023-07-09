#include "../ConstructibleObject/PapyrusExtConstructibleObject.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/B/BGSConstructibleObject.h"
#include "../../../../../../source/T/TESBoundObject.h"
#include "../../../../../../source/RTTI.h"
#include "../../../../../../source/B/BGSKeyword.h"

namespace PapyrusExtConstructibleObject
{
	// I really hate doing this...
	using namespace ConsoleRE;

	TESForm* GetResult(BGSConstructibleObject* recipe)
	{
		if (!recipe || !recipe->createdItem)
			return NULL;

		return recipe->createdItem;
	}

	void SetResult(BGSConstructibleObject* recipe, TESForm* form)
	{
		if (recipe && form) 
		{
			TESBoundObject* result = TES_RTTI(form, TESForm, TESBoundObject); // Only Base Objects allowed
			if (result) 
			{
				recipe->createdItem = result;
			}
		}
	}

	uint32_t GetResultQuantity(BGSConstructibleObject* recipe)
	{
		if (!recipe || !recipe->createdItem)
			return 0;

		return recipe->data.numConstructed;
	}

	void SetResultQuantity(BGSConstructibleObject* recipe, uint32_t quantity)
	{
		if (recipe && quantity < USHRT_MAX) {
			recipe->data.numConstructed = quantity;
		}
	}

	uint32_t GetNumIngredients(BGSConstructibleObject* recipe)
	{
		if (!recipe)
			return 0;

		return recipe->requiredItems.numContainerObjects;
	}


	TESForm* GetNthIngredient(BGSConstructibleObject* recipe, uint32_t n)
	{
		if (!recipe || n > recipe->requiredItems.numContainerObjects)
			return NULL;

		return recipe->requiredItems.containerObjects[n]->obj;
	}

	void SetNthIngredient(BGSConstructibleObject* recipe, TESForm* form, uint32_t n)
	{
		if (recipe && form && n <= recipe->requiredItems.numContainerObjects)
		{
			TESBoundObject* result = TES_RTTI(form, TESForm, TESBoundObject); // Only Base Objects allowed
			if (result) 
			{
				recipe->requiredItems.containerObjects[n]->obj = result;
			}
		}
	}

	uint32_t GetNthIngredientQuantity(BGSConstructibleObject* recipe, uint32_t n)
	{
		if (!recipe || n > recipe->requiredItems.numContainerObjects)
			return 0;

		return recipe->requiredItems.containerObjects[n]->count;
	}

	void SetNthIngredientQuantity(BGSConstructibleObject* recipe, uint32_t value, uint32_t n)
	{
		if (recipe && n <= recipe->requiredItems.numContainerObjects)
		{
			recipe->requiredItems.containerObjects[n]->count = value;
		}
	}

	BGSKeyword* GetWorkbenchKeyword(BGSConstructibleObject* recipe)
	{
		if (!recipe)
			return NULL;

		return recipe->benchKeyword;
	}

	void SetWorkbenchKeyword(BGSConstructibleObject* recipe, BGSKeyword* keyword)
	{
		if (recipe && keyword) 
		{
			recipe->benchKeyword = keyword;
		}
	}

	bool RegisterConstructibleObject(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetResult),                BGSConstructibleObject, TESForm*>                ("GetResult",                "ConstructibleObject", GetResult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetResult),                BGSConstructibleObject, void, TESForm*>          ("SetResult",                "ConstructibleObject", SetResult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetResultQuantity),        BGSConstructibleObject, uint32_t>                ("GetResultQuantity",        "ConstructibleObject", GetResultQuantity));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetResultQuantity),        BGSConstructibleObject, void, uint32_t>          ("SetResultQuantity",        "ConstructibleObject", SetResultQuantity));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNumIngredients),        BGSConstructibleObject, uint32_t>                ("GetNumIngredients",        "ConstructibleObject", GetNumIngredients));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthIngredient),         BGSConstructibleObject, TESForm*, uint32_t>      ("GetNthIngredient",         "ConstructibleObject", GetNthIngredient));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetNthIngredient),         BGSConstructibleObject, void, TESForm*, uint32_t>("SetNthIngredient",         "ConstructibleObject", SetNthIngredient));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthIngredientQuantity), BGSConstructibleObject, uint32_t, uint32_t>      ("GetNthIngredientQuantity", "ConstructibleObject", GetNthIngredientQuantity));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetNthIngredientQuantity), BGSConstructibleObject, void, uint32_t, uint32_t>("SetNthIngredientQuantity", "ConstructibleObject", SetNthIngredientQuantity));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetWorkbenchKeyword),      BGSConstructibleObject, BGSKeyword*>             ("GetWorkbenchKeyword",      "ConstructibleObject", GetWorkbenchKeyword));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetWorkbenchKeyword),      BGSConstructibleObject, void, BGSKeyword*>       ("SetWorkbenchKeyword",      "ConstructibleObject", SetWorkbenchKeyword));

		return true;
	}
}