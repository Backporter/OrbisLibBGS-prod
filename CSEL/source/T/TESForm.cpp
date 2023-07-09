#include "../T/TESForm.h"

#include "../B/BGSDefaultObjectManager.h"
#include "../F/FormTraits.h"
#include "../I/IObjectHandlePolicy.h"
#include "../I/InventoryEntryData.h"
#include "../T/TESFullName.h"
#include "../T/TESGlobal.h"
#include "../T/TESModel.h"
#include "../T/TESObjectREFR.h"
#include "../V/VirtualMachine.h"

namespace ConsoleRE
{
	int32_t TESForm::GetGoldValue()
	{
		const auto obj = As<TESBoundObject>();
		if (obj)
		{
			const InventoryEntryData entry { const_cast<TESBoundObject*>(obj), 1 };
			return entry.GetValue();
		}
		else
		{
			return -1;
		}
	}

	const char* TESForm::GetName()
	{
		const auto fullName = As<TESFullName>();
		if (fullName) 
		{
			const auto str = fullName->GetFullName();
			return str ? str : "";
		}
		else 
		{
			return "";
		}
	}

	float TESForm::GetWeight()
	{
		const auto survival = []()
		{
			const auto dobj = BGSDefaultObjectManager::GetSingleton();
			const auto survival = dobj ? dobj->GetObject<TESGlobal>(323) : nullptr;
			return survival ? survival->value == 1.0F : false;
		};

		const auto ref = As<TESObjectREFR>();
		const auto baseObj = ref ? ref->GetBaseObject() : nullptr;
		const auto form = baseObj ? baseObj : this;

		if (!survival() && (form->IsAmmo() || form->IsLockpick())) 
		{
			return 0.0F;
		}
		else if (const auto weightForm = form->As<TESWeightForm>(); weightForm) 
		{
			return weightForm->weight;
		}
		else if (form->GetFormType() == 43)
		{
			const auto npc = static_cast<const TESNPC*>(form);
			return npc->weight;
		}
		else 
		{
			return -1.0F;
		}
	}
}