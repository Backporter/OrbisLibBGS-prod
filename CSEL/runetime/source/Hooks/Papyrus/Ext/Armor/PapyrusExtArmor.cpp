#include "../Armor/PapyrusExtArmor.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESObjectARMA.h"
#include "../../../../../../source/T/TESObjectARMO.h"

namespace PapyrusExtArmor
{
	// I really hate doing this...
	using namespace ConsoleRE;

	uint32_t GetArmorRating(TESObjectARMO* form)
	{
		if (form)
		{
			return (form->armorRating / 100);
		}

		return 0;
	}

	void SetArmorRating(TESObjectARMO* form, uint32_t val)
	{
		if (form)
		{
			form->armorRating = (val * 100);
		}
	}

	void ModArmorRating(TESObjectARMO* form, int32_t val)
	{
		if (form)
		{
			int32_t val2 = form->armorRating + (val * 100);
			if (val2 < 0)
				val2 = 0;

			form->armorRating = val2;
		}
	}

	uint32_t GetSlotMask(TESObjectARMO* form)
	{
		if (form)
		{
			return form->GetSlotMask();
		}

		return 0;
	}

	void SetSlotMask(TESObjectARMO* form, uint32_t val)
	{
		if (form)
		{
			form->SetSlotMask(val);
		}
	}

	uint32_t AddSlotToMask(TESObjectARMO* form, uint32_t val)
	{
		if (form)
		{
			return form->AddSlotToMask(val);
		}

		return 0;
	}

	uint32_t RemoveSlotFromMask(TESObjectARMO* form, uint32_t val)
	{
		if (form)
		{
			return form->RemoveSlotFromMask(val);
		}

		return 0;
	}

	uint32_t GetMaskForSlot(StaticFunctionTag* tag, uint32_t slot)
	{
		if (slot < 29 || slot > 61)
			return 0;

		return (1 << (slot - 30));
	}

	BSFixedString GetModelPath(TESObjectARMO* form, bool bFemale)
	{
		if (form)
		{
			int index;

			if (bFemale)
				index = 1;
			else
				index = 0;


			return form->worldModels[index].GetModel();
		}

		return NULL;
	}

	void SetModelPath(TESObjectARMO* form, BSFixedString path, bool bFemale)
	{
		if (form)
		{
			int index;
			if (bFemale)
				index = 1;
			else
				index = 0;

			form->worldModels[index].SetModel(path.m_data);
		}
	}

	uint32_t GetWeightClass(TESObjectARMO* form)
	{
		if (form)
		{
			return form->GetArmorType();
		}

		return 2;
	}

	void SetWeightClass(TESObjectARMO* form, uint32_t val)
	{
		if (form)
		{
			if (val <= 2)
			{
				form->SetArmorType(val);
			}
		}
	}

	EnchantmentItem* GetEnchantment(TESObjectARMO* form)
	{
		if (form)
		{
			return form->formEnchanting;
		}

		return NULL;
	}

	void SetEnchantment(TESObjectARMO* form, EnchantmentItem* enc)
	{
		if (form) 
		{
			form->formEnchanting = enc;
		}
	}

	uint32_t GetNumArmorAddons(TESObjectARMO* form)
	{
		if (form)
		{
			return form->armorAddons.size();
		}

		return 0;
	}

	TESObjectARMA* GetArmorAddonFromIndex(TESObjectARMO* form, uint32_t n)
	{
		if (form)
		{
			return form->armorAddons[n];
			
		}
		
		return NULL;
	}

	bool	RegisterArmor(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetArmorRating),         TESObjectARMO, uint32_t>                                     ("GetArmorRating",     "Armor",  GetArmorRating));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetArmorRating),         TESObjectARMO, void, uint32_t>                               ("SetArmorRating",     "Armor",  SetArmorRating));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(ModArmorRating),         TESObjectARMO, void, int32_t>                                ("ModArmorRating",     "Armor",  ModArmorRating));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetSlotMask),            TESObjectARMO, uint32_t>                                     ("GetSlotMask",        "Armor",  GetSlotMask));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetSlotMask),            TESObjectARMO, void, uint32_t>                               ("SetSlotMask",        "Armor",  SetSlotMask));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(AddSlotToMask),          TESObjectARMO, uint32_t, uint32_t>                           ("AddSlotToMask",      "Armor",  AddSlotToMask));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(RemoveSlotFromMask),     TESObjectARMO, uint32_t, uint32_t>                           ("RemoveSlotFromMask", "Armor",  RemoveSlotFromMask));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetMaskForSlot),         StaticFunctionTag, uint32_t, uint32_t>                       ("GetMaskForSlot",     "Armor",  GetMaskForSlot));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetModelPath),           TESObjectARMO, BSFixedString, bool>                          ("GetModelPath",       "Armor",  GetModelPath));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetModelPath),           TESObjectARMO, void, BSFixedString, bool>                    ("SetModelPath",       "Armor",  SetModelPath));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetWeightClass),         TESObjectARMO, uint32_t>                                     ("GetWeightClass",     "Armor",  GetWeightClass));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetWeightClass),         TESObjectARMO, void, uint32_t>                               ("SetWeightClass",     "Armor",  SetWeightClass));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetEnchantment),         TESObjectARMO, EnchantmentItem*>                             ("GetEnchantment",     "Armor",  GetEnchantment));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetEnchantment),         TESObjectARMO, void, EnchantmentItem*>                       ("SetEnchantment",     "Armor",  SetEnchantment));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNumArmorAddons),      TESObjectARMO, uint32_t>                                     ("GetNumArmorAddons",  "Armor",  GetNumArmorAddons));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetArmorAddonFromIndex), TESObjectARMO, TESObjectARMA*, uint32_t>                     ("GetNthArmorAddon",   "Armor",  GetArmorAddonFromIndex));
		
		return true;
	}
}