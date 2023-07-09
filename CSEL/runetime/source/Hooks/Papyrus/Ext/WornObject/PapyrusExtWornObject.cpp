#include "../WornObject/PapyrusExtWornObject.h"

#include "../../../../../../source/A/Actor.h"
#include "../../../../../../source/B/BGSRefAlias.h"
#include "../../../../../../source/E/ExtraAliasInstanceArray.h"
#include "../../../../../../source/E/ExtraContainerChanges.h"
#include "../../../../../../source/E/ExtraHealth.h"
#include "../../../../../../source/E/ExtraEnchantment.h"
#include "../../../../../../source/E/ExtraCharge.h"
#include "../../../../../../source/E/ExtraPoison.h"
#include "../../../../../../source/E/ExtraTextDisplayData.h"
#include "../../../../../../source/P/PersistentFormManager.h"
#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESObjectARMO.h"
#include "../../../../../../source/A/AlchemyItem.h"
#include "../../../../../../source/E/EffectSetting.h"
#include "../../../../../../source/P/PackUnpackImpl.h"

namespace PapyrusExtWornObject
{
	// I really hate doing this...
	using namespace ConsoleRE;

	// helper functions
	inline void GetEquipedObject(TESBoundObject*& a_dstForm, ExtraDataList*& a_dstList, Actor * actor, uint32_t weaponSlot, uint32_t slotMask)
	{
		Helper::MatchEquipmentSlot equipmentSlotMatcher(actor, weaponSlot, slotMask);
		ExtraContainerChanges* extraContainerChanges = actor->extraList.GetByType<ExtraContainerChanges>();
		if (extraContainerChanges)
		{
			extraContainerChanges->FindEquipped<Helper::MatchEquipmentSlot>(equipmentSlotMatcher, a_dstForm, a_dstList, weaponSlot == 1 || slotMask != 0, weaponSlot == 0);
		}
	}
	//
#pragma region
	void CreateEnchantment(StaticFunctionTag*, Actor * actor, uint32_t weaponSlot, uint32_t slotMask, float maxCharge, std::vector<EffectSetting*> effects, std::vector<float> magnitudes, std::vector<uint32_t> areas, std::vector<uint32_t> durations)
	{
		TESBoundObject*	s_form = nullptr;
		ExtraDataList*	s_list = nullptr;
		GetEquipedObject(s_form, s_list, actor, weaponSlot, slotMask);

		if (s_form && s_list)
		{
			if (s_form->FormType == TESObjectWEAP::TypeID || s_form->FormType == TESObjectARMO::TypeID)
			{
				EnchantmentItem * enchantment = NULL;
				if (effects.size() > 0 && magnitudes.size() == effects.size() && areas.size() == effects.size() && durations.size() == effects.size())
				{
					BSTArray<Effect> effectItems(effects.size());

					uint32_t j = 0;
					for (uint32_t i = 0; i < effects.size(); i++)
					{
						EffectSetting* magicEffect = NULL;
						magicEffect = effects[i];
						if (magicEffect)
						{
							effectItems[j].SetMagnitude(magnitudes[i]);
							effectItems[j].SetArea(areas[i]);
							effectItems[j].SetDuration(durations[i]);
							effectItems[j].baseEffect = magicEffect;
							j++;
						}
					}

					effectItems.m_size = j;

					if (s_form->FormType == TESObjectWEAP::TypeID)
						enchantment = PersistentFormManager::GetSingleton()->CreateOffensiveEnchantment(effectItems);
					else
						enchantment = PersistentFormManager::GetSingleton()->CreateDefensiveEnchantment(effectItems);
				}

				if (enchantment)
				{
					if (maxCharge > 0xFFFF)
						maxCharge = 0xFFFF;

					ExtraEnchantment* extraEnchant = static_cast<ExtraEnchantment*>(s_list->GetByType(ExtraEnchantment::TypeID));
					if (extraEnchant)
					{
						PersistentFormManager::GetSingleton()->DecrementEnchantmentReferenceCount(extraEnchant->enchantment);
						extraEnchant->enchantment = enchantment;
						PersistentFormManager::GetSingleton()->IncrementEnchantmentReferenceCount(extraEnchant->enchantment);
						extraEnchant->charge = (uint16_t)maxCharge;
					}
					else
					{
						ExtraEnchantment* extraEnchant = new ExtraEnchantment(enchantment, maxCharge);
						s_list->Add(ExtraEnchantment::TypeID, static_cast<BSExtraData*>(extraEnchant));
					}
				}
			}

			if (actor)
			{
				if (s_form->FormType == TESObjectWEAP::TypeID)
					actor->UpdateWeaponAbility(s_form, s_list, weaponSlot == 0);
				else if (s_form->FormType == TESObjectARMO::TypeID)
					actor->UpdateArmorAbility(s_form, s_list);
			}
		}

	}

	std::vector<BGSRefAlias*>	GetReferenceAliases(StaticFunctionTag*, Actor * actor, uint32_t weaponSlot, uint32_t slotMask)
	{
		std::vector<BGSRefAlias*> result;
		TESBoundObject*	s_form = nullptr;
		ExtraDataList*	s_list = nullptr;
		GetEquipedObject(s_form, s_list, actor, weaponSlot, slotMask);

		if (s_form && s_list)
		{
			ExtraAliasInstanceArray* xAliases = static_cast<ExtraAliasInstanceArray*>(s_list->GetByType(ExtraAliasInstanceArray::TypeID));
			if (!xAliases)
				return result;

			BGSRefAliasInstanceData* info = NULL;
			for (uint32_t n = 0; n < xAliases->aliases.size(); n++)
			{
				BGSRefAlias * alias = NULL;
				if (xAliases->aliases.Get(n, info))
				{
					alias = TES_RTTI(info->alias, BGSBaseAlias, BGSRefAlias);
				}

				result.push_back(alias);
			}

			return result;
		}

		return result;
	}
#pragma endregion

	EnchantmentItem*			GetEnchantment(StaticFunctionTag*, Actor * actor, uint32_t weaponSlot, uint32_t slotMask)
	{
		TESBoundObject*		s_form = nullptr;
		ExtraDataList*		s_list = nullptr;
		GetEquipedObject(s_form, s_list, actor, weaponSlot, slotMask);

		if (s_form && s_list)
		{
			ExtraEnchantment* extraEnchant = s_list->GetByType<ExtraEnchantment>();
			if (extraEnchant)
			{
				return extraEnchant->enchantment;
			}

			return nullptr;
		}

		return nullptr;
	}

	AlchemyItem*				GetPoison(StaticFunctionTag*, Actor * actor, uint32_t weaponSlot, uint32_t slotMask)
	{
		TESBoundObject*		s_form = nullptr;
		ExtraDataList*		s_list = nullptr;
		GetEquipedObject(s_form, s_list, actor, weaponSlot, slotMask);

		if (s_form && s_list)
		{
			ExtraPoison* extraPoison = s_list->GetByType<ExtraPoison>();
			if (extraPoison)
				return extraPoison->poison;
			else
				return nullptr;
		}

		return NULL;
	}

	BSFixedString				GetDisplayName(StaticFunctionTag*, Actor * actor, uint32_t weaponSlot, uint32_t slotMask)
	{
		TESBoundObject*		s_form = nullptr;
		ExtraDataList*		s_list = nullptr;
		GetEquipedObject(s_form, s_list, actor, weaponSlot, slotMask);

		if (s_form && s_list)
		{
			const char * displayName = NULL;
			displayName = s_list->GetDisplayName(s_form);
			if (!displayName)
			{
				TESFullName* pFullName = TES_RTTI(s_form, TESForm, TESFullName);
				if (pFullName)
					displayName = pFullName->name.m_data;
			}

			return displayName;
		}

		return "";
	}

	BGSRefAlias*				GetNthReferenceAlias(StaticFunctionTag*, Actor * actor, uint32_t weaponSlot, uint32_t slotMask, uint32_t n)
	{
		TESBoundObject*		s_form = nullptr;
		ExtraDataList*		s_list = nullptr;
		GetEquipedObject(s_form, s_list, actor, weaponSlot, slotMask);

		if (s_form && s_list)
		{
			ExtraAliasInstanceArray* xAliases = s_list->GetByType<ExtraAliasInstanceArray>();
			if (!xAliases)
				return NULL;

			BGSRefAliasInstanceData * info = NULL;
			xAliases->aliases.Get(n, info);
			if (!info)
				return NULL;

			return (BGSRefAlias*)info->alias;
		}

		return NULL;
	}

	float						GetItemHealthPercent(StaticFunctionTag*, Actor * actor, uint32_t weaponSlot, uint32_t slotMask)
	{
		if (!actor)
			return 1.0f;

		TESBoundObject*		s_form = nullptr;
		ExtraDataList*		s_list = nullptr;
		GetEquipedObject(s_form, s_list, actor, weaponSlot, slotMask);

		if (s_form && s_list)
		{
			if (s_form->FormType == TESObjectWEAP::TypeID || s_form->FormType == TESObjectARMO::TypeID)
			{
				ExtraHealth* extraHealth = s_list->GetByType<ExtraHealth>();
				if (extraHealth)
					return extraHealth->health;
			}
		}


		return 1.0f;
	}

	void						SetItemHealthPercent(StaticFunctionTag*, Actor * actor, uint32_t weaponSlot, uint32_t slotMask, float value)
	{
		TESBoundObject*		s_form = nullptr;
		ExtraDataList*		s_list = nullptr;
		GetEquipedObject(s_form, s_list, actor, weaponSlot, slotMask);

		if (s_form && s_list)
		{
			if (s_form->FormType == TESObjectWEAP::TypeID || s_form->FormType == TESObjectARMO::TypeID)
			{
				ExtraHealth* extraHealth = s_list->GetByType<ExtraHealth>();
				if (extraHealth)
				{
					extraHealth->health = value;
				}
				else
				{
					extraHealth = new ExtraHealth();
					extraHealth->health = value;
					s_list->Add(ExtraHealth::TypeID, static_cast<BSExtraData*>(extraHealth));
				}
			}
		}
	}

	float						GetItemMaxCharge(StaticFunctionTag*, Actor * actor, uint32_t weaponSlot, uint32_t slotMask)
	{
		TESBoundObject*		s_form = nullptr;
		ExtraDataList*		s_list = nullptr;
		GetEquipedObject(s_form, s_list, actor, weaponSlot, slotMask);

		if (s_form && s_list)
		{
			TESObjectWEAP * weapon = TES_RTTI(s_form, TESForm, TESObjectWEAP);
			if (!weapon)
				return 0.0f;

			if (static_cast<TESEnchantableForm*>(weapon)->formEnchanting != NULL)
				return (float)static_cast<TESEnchantableForm*>(weapon)->amountofEnchantment;
			else if (ExtraEnchantment* extraEnchant = s_list->GetByType<ExtraEnchantment>())
				return (float)extraEnchant->charge;

			return 0.0f;
		}

		return 0.0f;
	}

	void						SetItemMaxCharge(StaticFunctionTag*, Actor * actor, uint32_t weaponSlot, uint32_t slotMask, float maxCharge)
	{
		TESBoundObject*		s_form = nullptr;
		ExtraDataList*		s_list = nullptr;
		GetEquipedObject(s_form, s_list, actor, weaponSlot, slotMask);

		if (s_form && s_list)
		{
			TESObjectWEAP * weapon = TES_RTTI(s_form, TESForm, TESObjectWEAP);
			if (weapon)
			{
				if (maxCharge > USHRT_MAX)
					maxCharge = USHRT_MAX;

				if (ExtraEnchantment* extraEnchant = s_list->GetByType<ExtraEnchantment>())
					extraEnchant->charge = (uint16_t)maxCharge;
			}
		}
	}

	float						GetItemCharge(StaticFunctionTag*, Actor * actor, uint32_t weaponSlot, uint32_t slotMask)
	{
		TESBoundObject*		s_form = nullptr;
		ExtraDataList*		s_list = nullptr;
		GetEquipedObject(s_form, s_list, actor, weaponSlot, slotMask);

		if (s_form && s_list)
		{
			if (s_form->FormType != TESObjectWEAP::TypeID)
				return 0.0f;

			ExtraCharge* extraCharge = s_list->GetByType<ExtraCharge>();
			if (extraCharge)
				return extraCharge->charge;
			else
			{
				TESObjectWEAP * weapon = TES_RTTI(s_form, TESForm, TESObjectWEAP);
				if (!weapon)
					return 0.0f;

				if (static_cast<TESEnchantableForm*>(weapon)->formEnchanting != NULL)
					return (float)static_cast<TESEnchantableForm*>(weapon)->amountofEnchantment;

				else if (ExtraEnchantment* extraEnchant = s_list->GetByType<ExtraEnchantment>())
					return (float)static_cast<TESEnchantableForm*>(weapon)->amountofEnchantment;

				return 0.0f;
			}

		}

		return 0.0;
	}

	void						SetEnchantment(StaticFunctionTag*, Actor * actor, uint32_t weaponSlot, uint32_t slotMask, EnchantmentItem * enchantment, float maxCharge)
	{
		TESBoundObject*		s_form = nullptr;
		ExtraDataList*		s_list = nullptr;
		GetEquipedObject(s_form, s_list, actor, weaponSlot, slotMask);

		if (s_form && s_list)
		{
			if (s_form->FormType == TESObjectWEAP::TypeID || s_form->FormType == TESObjectARMO::TypeID)
			{
				if (!enchantment)
				{
					ExtraEnchantment* extraEnchant = s_list->GetByType<ExtraEnchantment>();
					if (extraEnchant)
						s_list->Remove(ExtraEnchantment::TypeID, extraEnchant);

					PersistentFormManager::GetSingleton()->DecrementEnchantmentReferenceCount(extraEnchant->enchantment);
					operator delete(extraEnchant);
				}
				else
				{
					if (maxCharge > 0xFFFF)
						maxCharge = 0xFFFF;

					ExtraEnchantment* extraEnchant = s_list->GetByType<ExtraEnchantment>();
					if (extraEnchant)
					{
						PersistentFormManager::GetSingleton()->DecrementEnchantmentReferenceCount(extraEnchant->enchantment);
						extraEnchant->enchantment = enchantment;
						PersistentFormManager::GetSingleton()->IncrementEnchantmentReferenceCount(extraEnchant->enchantment);
						extraEnchant->charge = (uint16_t)maxCharge;
					}
					else
					{
						ExtraEnchantment* extraEnchant = new ExtraEnchantment(enchantment, maxCharge);
						s_list->Add(ExtraEnchantment::TypeID, extraEnchant);
					}
				}
			}

			if (actor)
			{
				if (s_form->FormType == TESObjectWEAP::TypeID)
					actor->UpdateWeaponAbility(s_form, s_list, weaponSlot == 0);
				else if (s_form->FormType == TESObjectARMO::TypeID)
					actor->UpdateArmorAbility(s_form, s_list);

			}
		}
	}

	bool						SetDisplayName(StaticFunctionTag*, Actor * actor, uint32_t weaponSlot, uint32_t slotMask, BSFixedString value, bool force)
	{
		bool			s_ret  = false;
		TESBoundObject*	s_form = nullptr;
		ExtraDataList*	s_list = nullptr;
		GetEquipedObject(s_form, s_list, actor, weaponSlot, slotMask);
		
		if (s_form && s_list)
		{
			ExtraTextDisplayData* extraTextDisplayData = s_list->GetByType<ExtraTextDisplayData>();
			if (extraTextDisplayData)
			{
				if ((extraTextDisplayData->displayNameText || extraTextDisplayData->ownerQuest) && force)
				{
					extraTextDisplayData->displayNameText = nullptr;
					extraTextDisplayData->ownerQuest = nullptr;
				}

				s_ret = (!(extraTextDisplayData->displayNameText || extraTextDisplayData->ownerQuest) || force);
				extraTextDisplayData->SetName(value.m_data);
			}
			else
			{
				extraTextDisplayData = new ExtraTextDisplayData(value.m_data);
				s_list->Add(ExtraTextDisplayData::TypeID, extraTextDisplayData);
			}

			return s_ret;
		}

		return false;
	}

	uint32_t					GetNumReferenceAliases(StaticFunctionTag*, Actor * actor, uint32_t weaponSlot, uint32_t slotMask)
	{
		TESBoundObject*		s_form = nullptr;
		ExtraDataList*	s_list = nullptr;
		GetEquipedObject(s_form, s_list, actor, weaponSlot, slotMask);

		if (s_form && s_list)
		{
			ExtraAliasInstanceArray* xAliases = s_list->GetByType<ExtraAliasInstanceArray>();
			if (!xAliases)
				return NULL;

			return xAliases->aliases.m_size;
		}

		return 0;
	}

	bool RegisterWornObject(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		//
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(CreateEnchantment),		StaticFunctionTag, void, Actor*, uint32_t, uint32_t, float, std::vector<EffectSetting*>, std::vector<float>, std::vector<uint32_t>, std::vector<uint32_t>>	("CreateEnchantment",		"WornObject", CreateEnchantment));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetReferenceAliases),		StaticFunctionTag, std::vector<BGSRefAlias*>, Actor*, uint32_t, uint32_t>																					("GetReferenceAliases",		"WornObject", GetReferenceAliases));
		//

		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(GetItemHealthPercent),	StaticFunctionTag, float, Actor*, uint32_t, uint32_t>																										("GetItemHealthPercent",	"WornObject", GetItemHealthPercent));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(SetItemHealthPercent),	StaticFunctionTag, void, Actor*, uint32_t, uint32_t, float>																									("SetItemHealthPercent",	"WornObject", SetItemHealthPercent));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(GetItemMaxCharge),		StaticFunctionTag, float, Actor*, uint32_t, uint32_t>																										("GetItemMaxCharge",		"WornObject", GetItemMaxCharge));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(SetItemMaxCharge),		StaticFunctionTag, void, Actor*, uint32_t, uint32_t, float>																									("SetItemMaxCharge",		"WornObject", SetItemMaxCharge));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(GetItemCharge),			StaticFunctionTag, float, Actor*, uint32_t, uint32_t>																										("GetItemCharge",			"WornObject", GetItemCharge));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(GetEnchantment),			StaticFunctionTag, EnchantmentItem*, Actor*, uint32_t, uint32_t>																							("GetEnchantment",			"WornObject", GetEnchantment));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(SetEnchantment),			StaticFunctionTag, void, Actor*, uint32_t, uint32_t, EnchantmentItem*, float>																				("SetEnchantment",			"WornObject", SetEnchantment));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(GetPoison),				StaticFunctionTag, AlchemyItem*, Actor*, uint32_t, uint32_t>																								("GetPoison",				"WornObject", GetPoison));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(GetDisplayName),			StaticFunctionTag, BSFixedString, Actor*, uint32_t, uint32_t>																								("GetDisplayName",			"WornObject", GetDisplayName));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(SetDisplayName),			StaticFunctionTag, bool, Actor*, uint32_t, uint32_t, BSFixedString, bool>																					("SetDisplayName",			"WornObject", SetDisplayName));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(GetNumReferenceAliases),	StaticFunctionTag, uint32_t, Actor*, uint32_t, uint32_t>																									("GetNumReferenceAliases",	"WornObject", GetNumReferenceAliases));
		VM->RegisterFunction(new BSScript::NativeFunction <false,  NFDLSE(GetNthReferenceAlias),	StaticFunctionTag, BGSRefAlias*, Actor*, uint32_t, uint32_t, uint32_t>																						("GetNthReferenceAlias",	"WornObject", GetNthReferenceAlias));

		return true;
	}
}