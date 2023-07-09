#include "../I/InventoryEntryData.h"

#include "../E/ExtraCharge.h"
#include "../E/ExtraDataList.h"
#include "../E/ExtraEnchantment.h"
#include "../E/ExtraLeveledItem.h"
#include "../E/ExtraTextDisplayData.h"
#include "../E/ExtraWorn.h"
#include "../E/ExtraWornLeft.h"
#include "../F/FormTraits.h"
#include "../G/GameSettingCollection.h"
#include "../T/TESBoundObject.h"
#include "../T/TESEnchantableForm.h"
#include "../T/TESSoulGem.h"

namespace ConsoleRE
{
	double			InventoryEntryData::GetEnchantmentCharge()
	{
		auto obj = GetObject();
		auto ench = obj ? obj->As<TESEnchantableForm>() : nullptr;
		if (ench && ench->formEnchanting && ench->amountofEnchantment != 0) 
		{
			return 100.0;
		}

		if (extraLists) 
		{
			for (auto& xList : *extraLists) 
			{
				if (xList) 
				{
					auto xCharge = xList->GetByType<ExtraCharge>();
					auto xEnch = xList->GetByType<ExtraEnchantment>();
					if (xEnch && xEnch->enchantment && xEnch->charge != 0) 
					{
						if (xCharge) 
						{
							return (static_cast<double>(xCharge->charge) / static_cast<double>(xEnch->charge)) * 100.0;
						}
						else 
						{
							return 100.0;
						}

						break;
					}
					else if (xCharge && ench && ench->formEnchanting && ench->amountofEnchantment != 0) 
					{
						return (static_cast<double>(xCharge->charge) / static_cast<double>(ench->amountofEnchantment)) * 100.0;
						break;
					}
				}
			}
		}

		return 0.0;
	}

	const char*		InventoryEntryData::GetDisplayName()
	{
		const char* name = nullptr;
		if (extraLists) 
		{
			for (auto& xList : *extraLists) 
			{
				if (xList) 
				{
					name = xList->GetDisplayName(form);
				}
			}
		}

		if ((!name || name[0] == '\0') && form) 
		{
			name = form->GetName();
		}

		if (!name || name[0] == '\0') 
		{
			auto gmst = GameSettingCollection::GetSingleton();
			auto sMissingName = gmst ? gmst->GetSetting("sMissingName") : nullptr;
			name = sMissingName ? sMissingName->GetString() : "";
		}

		return name;
	}

	TESForm*		InventoryEntryData::GetOwner()
	{
		if (extraLists) 
		{
			for (auto& xList : *extraLists) 
			{
				auto owner = xList ? xList->GetOwner() : nullptr;
				if (owner)
				{
					return owner;
				}
			}
		}

		return nullptr;
	}

	uint32_t		InventoryEntryData::GetSoulLevel()
	{
		if (extraLists) 
		{
			for (auto& xList : *extraLists) 
			{
				if (xList) 
				{
					auto lvl = xList->GetSoulLevel();
					if (lvl > 0)
					{
						return lvl;
					}
				}
			}
		}

		if (form && form->GetFormType() == TESSoulGem::TypeID) 
		{
			auto soulGem = static_cast<TESSoulGem*>(form);
			return soulGem->GetContainedSoul();
		}

		return 0;
	}

	float			InventoryEntryData::GetWeight()
	{
		return form ? form->GetWeight() : -1.0F;
	}

	bool			InventoryEntryData::IsEnchanted()
	{
		if (form)
		{
			auto ench = form->As<TESEnchantableForm>();
			if (ench && ench->formEnchanting)
			{
				return true;
			}
		}

		if (extraLists) 
		{
			for (const auto& xList : *extraLists) 
			{
				const auto xEnch = xList->GetByType<ExtraEnchantment>();
				if (xEnch && xEnch->enchantment) 
				{
					return true;
				}
			}
		}

		return false;
	}

	bool			InventoryEntryData::IsLeveled()
	{
		if (extraLists) 
		{
			for (const auto& xList : *extraLists) 
			{
				if (xList && xList->HasType<ExtraLeveledItem>()) 
				{
					return true;
				}
			}
		}

		return false;
	}

	bool			InventoryEntryData::IsWorn()
	{
		if (extraLists) 
		{
			for (const auto& xList : *extraLists) 
			{
				if (xList && (xList->HasType<ExtraWorn>() || xList->HasType<ExtraWornLeft>())) 
				{
					return true;
				}
			}
		}

		return false;
	}
}