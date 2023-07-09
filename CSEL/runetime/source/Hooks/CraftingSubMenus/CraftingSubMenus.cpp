#include "../CraftingSubMenus/CraftingSubMenus.h"

#include "../../../../source/B/BGSConstructibleObject.h"
#include "../../../../source/E/EnchantConstructMenu.h"
#include "../../../../source/G/GFxValue.h"
#include "../../../../source/E/EffectSetting.h"
#include "../../../../source/T/TESBoundObject.h"
#include "../../../../source/F/FormTraits.h"

#include "InventoryPlugin.h"

namespace CraftingSubMenusE
{
	Relocation<void(*)(void*, void**, void*)>									 SmithingMenuSetR;											// ("", 0x9F4200);
	Relocation<void(*)(void*, void*, void*)>									 CraftingSubMenuSetR;										// ("", 0x9F0C10);
	Relocation<void(*)(void*, void*, void*)>									 AlchemyMenuSetR;											// ("", 0x9FC400);

	//
	Relocation<void(*)(void*, void*)>											 CraftingSubMenusEnchantConstructMenuCategoryListEntrySetR("", 0x9F7520);
	Relocation<void(*)(void*, void*, void*, const char*, void*, uint32_t, bool)> AlchemyMenuIndexFixUpHookedFN("", 0x11E0480);

	void SmithingMenuSet(ConsoleRE::GFxValue* gfxv, ConsoleRE::InventoryEntryData** dptr, ConsoleRE::CraftingSubMenus::SmithingMenu* ptr)
	{
		SmithingMenuSetR((void*)gfxv, (void**)dptr, (void*)ptr);
		
		if (ItemData::Extend && dptr && ptr && ptr->movie)
		{
			ConsoleRE::InventoryEntryData* f = *dptr;

			ItemData::common(gfxv, ptr->movie, f->form);
			ItemData::iteminfo(gfxv, f);
			ItemData::Standard(gfxv, ptr->movie, f->form, f);
			ItemData::inv(gfxv, ptr->movie, f->form, f);
			ItemData::magic(gfxv, ptr->movie, f->form);

			auto pluginList = InventoryPlugin::getPluginList();
			for (auto iter = pluginList.begin(); iter != pluginList.end(); ++iter)
			{
				if (*iter)
				{
					(*iter)(ptr->movie, gfxv, f);
				}
			}
		}
	}

	void CraftingSubMenuSet(ConsoleRE::GFxValue* gfxv, ConsoleRE::CraftingSubMenus::ConstructibleObjectMenu::ItemEntry* a_entries, ConsoleRE::CraftingSubMenus::ConstructibleObjectMenu* ptr2)
	{
		CraftingSubMenuSetR(gfxv, a_entries, ptr2);

		if (ItemData::Extend && a_entries && a_entries->constructibleObject && ptr2 && ptr2->movie)
		{
			ConsoleRE::BGSConstructibleObject* object = a_entries->constructibleObject;
			ConsoleRE::TESForm* form = object->createdItem;
			ConsoleRE::InventoryEntryData entryData(form->As<ConsoleRE::TESBoundObject>(), 0);

			ItemData::common(gfxv,   ptr2->movie, form);
			ItemData::iteminfo(gfxv, &entryData);
			ItemData::Standard(gfxv, ptr2->movie, form, &entryData);
			ItemData::inv(gfxv,		 ptr2->movie, form, &entryData);
			ItemData::magic(gfxv,	 ptr2->movie, form);

			auto pluginList = InventoryPlugin::getPluginList();
			for (auto iter = pluginList.begin(); iter != pluginList.end(); ++iter)
			{
				if (*iter)
				{
					(*iter)(ptr2->movie, gfxv, &entryData);
				}
			}
		}

	}

	void AlchemyMenuSet(ConsoleRE::GFxValue* gfxv, ConsoleRE::CraftingSubMenus::AlchemyMenu::MenuIngredientEntry* a_entries, ConsoleRE::CraftingSubMenus::AlchemyMenu* AlchemyMenu)
	{
		AlchemyMenuSetR(gfxv, a_entries, AlchemyMenu);
		
		if (ItemData::Extend && a_entries && a_entries->ingredient && AlchemyMenu && AlchemyMenu->movie)
		{
			ConsoleRE::InventoryEntryData* s_entryData = a_entries->ingredient;

			ItemData::common(gfxv, AlchemyMenu->movie, s_entryData->form);
			ItemData::iteminfo(gfxv, s_entryData);
			ItemData::magic(gfxv, AlchemyMenu->movie, s_entryData->form);

			auto pluginList = InventoryPlugin::getPluginList();
			for (auto iter = pluginList.begin(); iter != pluginList.end(); ++iter)
			{
				if (*iter)
				{
					(*iter)(AlchemyMenu->movie, gfxv, s_entryData);
				}
			}
		}
	}

	// CraftingSubMenus::EnchantConstructMenu::ItemChangeEntry
	void CraftingSubMenusEnchantConstructMenuItemChangeEntrySet(ConsoleRE::CraftingSubMenus::EnchantConstructMenu::ItemChangeEntry* rdi, ConsoleRE::GFxValue* rsi, ConsoleRE::GFxMovieRoot* rdx)
	{
		CraftingSubMenusEnchantConstructMenuCategoryListEntrySetR(rdi, rsi);

		if (rdx && ItemData::Extend)
		{
			switch (rdi->Flag)
			{
				case ConsoleRE::CraftingSubMenus::EnchantConstructMenu::EnchantMenuCallback::kEnchantWeapon:
				case ConsoleRE::CraftingSubMenus::EnchantConstructMenu::EnchantMenuCallback::kDisenchantWeapon:
				case ConsoleRE::CraftingSubMenus::EnchantConstructMenu::EnchantMenuCallback::kEnchantArmor:
				case ConsoleRE::CraftingSubMenus::EnchantConstructMenu::EnchantMenuCallback::kDisenchantArmor:
				case ConsoleRE::CraftingSubMenus::EnchantConstructMenu::EnchantMenuCallback::kSoulGem:
				{
					if (rdi && rdi->inventoryEntryData && rdi->inventoryEntryData->form)
					{
						ConsoleRE::InventoryEntryData* data = rdi->inventoryEntryData;

						ItemData::common(rsi, rdx, rdi->inventoryEntryData->form);
						ItemData::iteminfo(rsi, rdi->inventoryEntryData);
						ItemData::Standard(rsi, rdx, rdi->inventoryEntryData->form, rdi->inventoryEntryData);
						ItemData::inv(rsi, rdx, rdi->inventoryEntryData->form, rdi->inventoryEntryData);
						ItemData::magic(rsi, rdx, rdi->inventoryEntryData->form);
						
						auto pluginList = InventoryPlugin::getPluginList();
						for (auto iter = pluginList.begin(); iter != pluginList.end(); ++iter)
						{
							if (*iter)
							{
								(*iter)(rdx, rsi, data);
							}
						}
					}
				}
				break;
				case ConsoleRE::CraftingSubMenus::EnchantConstructMenu::EnchantMenuCallback::kEffectWeapon:
				case ConsoleRE::CraftingSubMenus::EnchantConstructMenu::EnchantMenuCallback::kEffectArmor:
				{
					if (rdi && rdi->inventoryEntryData && rdi->inventoryEntryData->form)
					{
						ItemData::common(rsi, rdx, rdi->inventoryEntryData->form);
						ItemData::magic(rsi, rdx, rdi->inventoryEntryData->form);
					}
				}
				break;
				default:
				break;
			}
		}
	}
	
	void AlchemyMenuIndexFixUp(void* a_this, void* a_obj, DUMMY* a_dummy, const char* a_name, ConsoleRE::GFxValue* a_args, uint32_t a_argc, bool IsDisplayOBJ)
	{
		using namespace ConsoleRE;

		if (ItemData::ExtendAlchemyCategories)
		{
			DUMMY* m_dummy = a_dummy;

			for (uint32_t i = 4; i < a_argc; i += 3)
			{				
				ConsoleRE::TESForm* form = ConsoleRE::TESForm::GetFormFromID(m_dummy->FormID);
				uint32_t flag = 0;

				ConsoleRE::EffectSetting* formeffect = TES_RTTI(form, TESForm, EffectSetting);
				if (formeffect)
				{
					uint32_t Type = formeffect->data.archetype;

					if (Type == 0 || Type == 5 || Type == 34)
					{
						if ((formeffect->data.flags & 4) != 0)
							flag = 4;
						else
							flag = 2;
					}
					else if (Type == 4 || Type == 3 || Type == 11 || Type == 27 || Type == 28 || Type == 29 || Type == 2)
					{
						flag = 2;
					}
					else if (Type == 8 || Type == 6 || Type == 7 || Type == 21)
					{
						flag = 4;
					}
					else
					{
						flag = 8;
					}
				}

				a_args[i].SetNumber(flag);
				m_dummy++;
			}
		}
		
		return AlchemyMenuIndexFixUpHookedFN(a_this, a_obj, nullptr, a_name, a_args, a_argc, IsDisplayOBJ);
	}
}