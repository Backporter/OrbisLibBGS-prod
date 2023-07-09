#include "..//ObjectReference/PapyrusExtObjectReference.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESObjectREFR.h"
#include "../../../../../../source/T/TESObjectTREE.h"
#include "../../../../../../source/T/TESObjectWEAP.h"
#include "../../../../../../source/B/BGSRefAlias.h"
#include "../../../../../../source/T/TESFlora.h"
#include "../../../../../../source/T/TESContainer.h"
#include "../../../../../../source/E/ExtraContainerChanges.h"
#include "../../../../../../source/E/ExtraPoison.h"
#include "../../../../../../source/E/ExtraCharge.h"
#include "../../../../../../source/E/ExtraEnchantment.h"
#include "../../../../../../source/E/ExtraAliasInstanceArray.h"
#include "../../../../../../source/E/ExtraEnableStateParent.h"
#include "../../../../../../source/P/PersistentFormManager.h"
#include "../../../../../../source/P/PlayerCharacter.h"
#include "../../../../../../source/T/TESObjectARMO.h"
#include "../../../../../../source/A/AlchemyItem.h"
#include "../../../../../../source/E/EffectSetting.h"
#include "../../../../../../source/P/PackUnpackImpl.h"

//
#include "../../../../../../source/E/ExtraHealth.h"
#include "../../../../../../source/E/ExtraTextDisplayData.h"

#include "../../../TaskPool/TaskPool.h"
#include "../../../../../Internal/Tasks/Tasks/TaskUpdateHarvestModel.h"

namespace PapyrusExtObjectReference
{
	using namespace ConsoleRE;
	
#pragma region 
	void						CreateEnchantment(TESObjectREFR* object, float maxCharge, std::vector<EffectSetting*> effects, std::vector<float> magnitudes, std::vector<uint32_t> areas, std::vector<uint32_t> durations)
	{
		if (object)
		{
			if (object->GetBaseObject() && (object->GetBaseObject()->FormType == TESObjectWEAP::TypeID || object->GetBaseObject()->FormType == TESObjectARMO::TypeID))
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

					if (object->GetObjectReference()->FormType == TESObjectWEAP::TypeID)
						enchantment = PersistentFormManager::GetSingleton()->CreateOffensiveEnchantment(effectItems);
					else
						enchantment = PersistentFormManager::GetSingleton()->CreateDefensiveEnchantment(effectItems);
				}

				if (enchantment)
				{
					if (maxCharge > 0xFFFF)
						maxCharge = 0xFFFF;

					ExtraEnchantment* extraEnchant = static_cast<ExtraEnchantment*>(object->extraList.GetByType(ExtraEnchantment::TypeID));
					if (extraEnchant)
					{
						PersistentFormManager::GetSingleton()->DecrementEnchantmentReferenceCount(extraEnchant->enchantment);
						extraEnchant->enchantment = enchantment;

						PersistentFormManager::GetSingleton()->IncrementEnchantmentReferenceCount(extraEnchant->enchantment);
						extraEnchant->charge = (uint16_t)maxCharge;
					}
					else
					{
						ExtraEnchantment* extraEnchant = new ExtraEnchantment(enchantment, (uint16_t)maxCharge);
						object->extraList.Add(ExtraEnchantment::TypeID, extraEnchant);
					}
				}
			}
		}
	}

	std::vector<BGSRefAlias*>	GetReferenceAliases(TESObjectREFR* object)
	{
		std::vector<BGSRefAlias*> result;

		if (!object)
			return result;

		ExtraAliasInstanceArray* xAliases = static_cast<ExtraAliasInstanceArray*>(object->extraList.GetByType(ExtraAliasInstanceArray::TypeID));
		if (!xAliases)
			return result;

		BGSRefAliasInstanceData* info = NULL;
		for (uint32_t n = 0; n < xAliases->aliases.size(); n++)
		{
			BGSRefAlias * alias = NULL;
			if (xAliases->aliases.Get(n, info))
				alias = TES_RTTI(info->alias, BGSBaseAlias, BGSRefAlias);

			result.push_back(alias);
		}

		return result;
	}

	std::vector<TESForm*>		GetContainerForms(TESObjectREFR* pContainerRef)
	{
		TESContainer*					pContainer = NULL;
		std::vector<TESForm*>			result;

		if (pContainerRef)
		{
			ExtraContainerChanges* pXContainerChanges = static_cast<ExtraContainerChanges*>(pContainerRef->extraList.GetByType(ExtraContainerChanges::TypeID));
			if (pXContainerChanges)
			{
				Helper::ExtraContainerInfo		helperInfo(pXContainerChanges->changes->entryList);
				Helper::ExtraContainerMerger	helperMerger(helperInfo, &result);
				auto*							pBaseForm = pContainerRef->GetObjectReference();

				if (pBaseForm)
				{
					pContainer = TES_RTTI(pBaseForm, TESForm, TESContainer);
				}

				if (pContainer)
				{
					pContainer->Visit(helperMerger);
				}

				helperInfo.ExportForms(result);
			}
		}

		return result;
	}
#pragma endregion

	bool				IsHarvested(TESObjectREFR* base)
	{
		if (base)
		{
			uint8_t FormType = base->data.objectReference->FormType;
			if (FormType == TESObjectTREE::TypeID || FormType == TESFlora::TypeID)
				return (base->formFlags & 8192) != 0;
		}

		return false;
	}

	void				SetHarvested(TESObjectREFR * base, bool isHarvested)
	{
		if (base)
		{
			uint8_t FormType = base->data.objectReference->FormType;
			if (FormType == TESObjectTREE::TypeID || FormType == TESFlora::TypeID)
			{
				if (isHarvested)
					base->formFlags |= 8192;
				else
					base->formFlags &= ~8192;
			}
		}
	}

	BSFixedString		GetDisplayName(TESObjectREFR* object)
	{
		return (object) ? object->GetDisplayFullName() : "";
	}

	bool				IsOffLimits(TESObjectREFR* obj)
	{
		return obj->IsOffLimits();
	}

	void				ResetInventory(TESObjectREFR * obj)
	{
		obj->ResetInventory(false);
	}

	BGSRefAlias*		GetNthReferenceAlias(TESObjectREFR* object, uint32_t n)
	{
		if (!object)
			return 0;

		ExtraAliasInstanceArray* xAliases = object->extraList.GetByType<ExtraAliasInstanceArray>();
		if (!xAliases)
			return NULL;

		BGSRefAliasInstanceData* info = NULL;
		xAliases->aliases.Get(n, info);
		if (!info)
			return NULL;

		return (BGSRefAlias*)info->alias;
	}

	uint32_t			GetNumReferenceAliases(TESObjectREFR* object)
	{
		if (!object)
			return 0;

		ExtraAliasInstanceArray* xAliases = object->extraList.GetByType<ExtraAliasInstanceArray>();
		if (!xAliases)
			return NULL;

		return xAliases->aliases.m_size;
	}
	
	void				SetItemMaxCharge(TESObjectREFR* object, float maxCharge)
	{
		if (object) 
		{
			if (object->data.objectReference)
			{
				TESObjectWEAP * weapon = TES_RTTI(object->data.objectReference, TESForm, TESObjectWEAP);
				if (weapon) 
				{
					if (maxCharge > USHRT_MAX)
						maxCharge = USHRT_MAX;

					if (ExtraEnchantment* extraEnchant = object->extraList.GetByType<ExtraEnchantment>())
						extraEnchant->charge = (uint16_t)maxCharge;
				}
			}
		}
	}

	float				GetItemMaxCharge(TESObjectREFR* object)
	{
		if (!object)
			return 0.0;

		if (!object->data.objectReference)
			return 0.0;

		TESObjectWEAP * weapon = TES_RTTI(object->data.objectReference, TESForm, TESObjectWEAP);
		
		if (!weapon)
			return 0.0;
		
		float maxCharge = 0;
		
		if (static_cast<TESEnchantableForm*>(weapon)->formEnchanting != NULL)
			maxCharge = (float)static_cast<TESEnchantableForm*>(weapon)->amountofEnchantment;

		else if (ExtraEnchantment* extraEnchant = object->extraList.GetByType<ExtraEnchantment>())
			maxCharge = (float)extraEnchant->charge;
		
		return maxCharge;

	}

	float				GetItemCharge(TESObjectREFR* object)
	{
		if (!object)
			return 0.0;

		if (!object->data.objectReference)
			return 0.0;

		if (object->data.objectReference->FormType != TESObjectWEAP::TypeID)
			return 0.0;

		ExtraCharge* xCharge = object->extraList.GetByType<ExtraCharge>();
		return (xCharge) ? xCharge->charge : GetItemMaxCharge(object);

	}

	AlchemyItem*		GetPoison(TESObjectREFR* object)
	{
		if (!object)
			return NULL;

		ExtraPoison* extraPoison = object->extraList.GetByType<ExtraPoison>();
		return extraPoison ? extraPoison->poison : NULL;
	}

	EnchantmentItem*	GetEnchantment(TESObjectREFR* object)
	{
		if (!object)
			return NULL;

		ExtraEnchantment* extraEnchant = object->extraList.GetByType<ExtraEnchantment>();
		return extraEnchant ? extraEnchant->enchantment : NULL;
	}

	// works?... no idea
	TESObjectREFR*		GetEnableParent(TESObjectREFR* object)
	{
		if (!object)
			return NULL;
	
		ExtraEnableStateParent* xEnableParent = object->extraList.GetByType<ExtraEnableStateParent>();
		if (!xEnableParent)
			return NULL;

		// =========================================

		// 
		Relocation<void(*)(uint32_t&, NiPointer<TESObjectREFR>&)> func("", 0x5DB210);
		Relocation<uint32_t*> invailedHandle("", 0x20BD820);
		NiPointer<TESObjectREFR> ref;
		//


		if (xEnableParent->parent == *invailedHandle || xEnableParent->parent == 0)
			return nullptr;
		
		func(xEnableParent->parent, ref);
		return ref.get();
	}

	void				SetItemHealthPercent(TESObjectREFR* object, float value)
	{
		if (object) 
		{
			if (object->data.objectReference)
			{
				if (object->data.objectReference->FormType == TESObjectWEAP::TypeID || object->data.objectReference->FormType == TESObjectARMO::TypeID)
				{
					ExtraHealth* xHealth = object->extraList.GetByType<ExtraHealth>();
					if (xHealth)
					{
						xHealth->health = value;
					}
					else
					{
						ExtraHealth* newHealth = new ExtraHealth(value);
						object->extraList.Add(ExtraHealth::TypeID, newHealth);
					}
				}
			}
		}
	}

	float				GetTotalArmorWeight(TESObjectREFR* pContainerRef)
	{
		if (!pContainerRef)
			return 0;

		ExtraContainerChanges* pXContainerChanges = pContainerRef->extraList.GetByType<ExtraContainerChanges>();
		return (pXContainerChanges) ? pXContainerChanges->changes->armorWeight : 0.0;
	}

	bool				SetDisplayName(TESObjectREFR* object, BSFixedString value, bool force)
	{
		bool renamed = false;
		ExtraTextDisplayData* xTextData = object->extraList.GetByType<ExtraTextDisplayData>();
		if (xTextData)
		{
			bool inUse = xTextData->displayNameText || xTextData->ownerQuest;
			if (inUse && force) 
			{
				xTextData->displayNameText = NULL;
				xTextData->ownerQuest = NULL;
			}

			renamed = (inUse == false || force);
			xTextData->SetName(value.m_data);
		}
		else
		{
			ExtraTextDisplayData* newTextData = new ExtraTextDisplayData(value.m_data);
			object->extraList.Add(ExtraTextDisplayData::TypeID, newTextData);
			renamed = true;
		}

		return renamed;
	}

	void				SetEnchantment(TESObjectREFR* object, EnchantmentItem * enchantment, float maxCharge)
	{
		if (object) 
		{
			if (object->data.objectReference->FormType == TESObjectWEAP::TypeID || object->data.objectReference->FormType == TESObjectARMO::TypeID)
			{
				if (!enchantment)
				{
					ExtraEnchantment* extraEnchant = object->extraList.GetByType<ExtraEnchantment>();
					if (extraEnchant)
						object->extraList.Remove(ExtraEnchantment::TypeID, extraEnchant);

					PersistentFormManager::GetSingleton()->DecrementEnchantmentReferenceCount(extraEnchant->enchantment);
					operator delete (extraEnchant);
				}
				else
				{
					if (maxCharge > 0xFFFF)
						maxCharge = 0xFFFF;

					ExtraEnchantment* extraEnchant = object->extraList.GetByType<ExtraEnchantment>();
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
						object->extraList.Add(ExtraEnchantment::TypeID, extraEnchant);
					}
				}
			}
		}
	}

	void				SetItemCharge(TESObjectREFR* object, float value)
	{
		if (object) 
		{
			TESObjectWEAP * weapon = TES_RTTI(object->data.objectReference, TESForm, TESObjectWEAP);
			if (weapon && ((object->extraList.GetByType<ExtraEnchantment>() || static_cast<TESEnchantableForm*>(weapon)->formEnchanting != NULL)))
			{
				ExtraCharge* xCharge = object->extraList.GetByType<ExtraCharge>();
				if (xCharge)
				{
					xCharge->charge = value;
				}
				else
				{
					ExtraCharge* newCharge = new ExtraCharge(value);
					object->extraList.Add(ExtraCharge::TypeID, newCharge);
				}
			}
		}
	}

	// should be considered experimental.
	void						GetAllForms(TESObjectREFR* pContainerRef, BGSListForm* list)
	{
		TESContainer* pContainer = NULL;

		if (pContainerRef && list) 
		{
			ExtraContainerChanges* pXContainerChanges = pContainerRef->extraList.GetByType<ExtraContainerChanges>();
			if (pXContainerChanges) 
			{
				TESForm* pBaseForm = pContainerRef->data.objectReference;
				if (pBaseForm)
					pContainer = TES_RTTI(pBaseForm, TESForm, TESContainer);

				Helper::ExtraContainerInfo info(pXContainerChanges ? pXContainerChanges->changes->entryList : NULL);

				if (pContainer) 
				{
					Helper::ExtraContainerMerger formFiller(info, list);
					pContainer->Visit(formFiller);
				}

				info.ExportForms(list);
			}
		}
	}

	float						GetTotalItemWeight(TESObjectREFR* pContainerRef)
	{
		if (!pContainerRef)
			return 0;

		ExtraContainerChanges* pXContainerChanges = pContainerRef->extraList.GetByType<ExtraContainerChanges>();
		if (!pXContainerChanges)
			return 0.0;

		if (pContainerRef == PlayerCharacter::GetSingleton())
			return pXContainerChanges->changes->totalWeight;

		float			weight = 0.0;
		TESContainer*	pContainer = NULL;
		TESForm* pBaseForm = pContainerRef->data.objectReference;
		if (pBaseForm) 
		{
			pContainer = TES_RTTI(pBaseForm, TESForm, TESContainer);
		}

		if (!pContainer)
			return 0;

		Helper::ExtraContainerInfo info(pXContainerChanges ? pXContainerChanges->changes->entryList : NULL);

		if (pContainer) 
		{
			Helper::ExtraContainerWeightInfo weightCounter(info);
			pContainer->Visit(weightCounter);
			weight = weightCounter.m_weight;
		}

		// now sum the remaining weight
		weight += info.ExportFormWeight();
		return weight;
	}

	TESForm*					GetNthForm(TESObjectREFR* pContainerRef, uint32_t n)
	{
		if (!pContainerRef)
			return NULL;

		TESContainer* pContainer = NULL;
		TESForm* pBaseForm = pContainerRef->data.objectReference;

		if (pBaseForm) 
		{
			pContainer = TES_RTTI(pBaseForm, TESForm, TESContainer);
		}

		if (!pContainer)
			return NULL;

		uint32_t count = 0;

		ExtraContainerChanges* pXContainerChanges = pContainerRef->extraList.GetByType<ExtraContainerChanges>();
		Helper::ExtraContainerInfo info(pXContainerChanges ? pXContainerChanges->changes->entryList : NULL);

		if (pContainer) 
		{
			Helper::ExtraContainerInfoFinder finder(info, n);
			ContainerObject* pFound = pContainer->Find(finder);
			
			if (pFound) 
			{
				return pFound->obj;
			}
			else 
			{
				count = finder.m_Curidx;
			}
		}

		InventoryEntryData* pEntryData = info.ExportForm(n, count);
		if (pEntryData) 
		{
			return pEntryData->form;
		}

		return NULL;
	}

	uint32_t					GetNumItems(TESObjectREFR* pContainerRef)
	{
		if (!pContainerRef)
			return 0;

		TESContainer* pContainer = NULL;
		TESForm* pBaseForm = pContainerRef->data.objectReference;
		if (pBaseForm)
		{
			pContainer = TES_RTTI(pBaseForm, TESForm, TESContainer);
		}

		if (!pContainer)
			return 0;

		uint32_t count = 0;
		ExtraContainerChanges* pXContainerChanges = pContainerRef->extraList.GetByType<ExtraContainerChanges>();
		Helper::ExtraContainerInfo info(pXContainerChanges ? pXContainerChanges->changes->entryList : NULL);

		if (pContainer) 
		{
			Helper::ExtraContainerCountVaild counter(info);
			count = pContainer->Count(counter);
		}

		count += info.ExportFormCount();

		return count;
	}
	
	bool RegisterObjectReference(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		//
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetReferenceAliases),	TESObjectREFR, std::vector<BGSRefAlias*>>																				   ("GetReferenceAliases",		"ObjectReference", GetReferenceAliases));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetContainerForms),		TESObjectREFR, std::vector<TESForm*>>																					   ("GetContainerForms",		"ObjectReference", GetContainerForms));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(CreateEnchantment),		TESObjectREFR, void, float, std::vector<EffectSetting*>, std::vector<float>, std::vector<uint32_t>, std::vector<uint32_t>> ("CreateEnchantment",		"ObjectReference", CreateEnchantment));
		//

		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetDisplayName),			TESObjectREFR, BSFixedString>				 ("GetDisplayName",			"ObjectReference", GetDisplayName));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(IsHarvested),				TESObjectREFR, bool>						 ("IsHarvested",			"ObjectReference", IsHarvested));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(SetHarvested),			TESObjectREFR, void, bool>					 ("SetHarvested",			"ObjectReference", SetHarvested));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetNumItems),				TESObjectREFR, uint32_t>					 ("GetNumItems",			"ObjectReference", GetNumItems));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetNthForm),				TESObjectREFR, TESForm*, uint32_t>			 ("GetNthForm",				"ObjectReference", GetNthForm));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetTotalItemWeight),		TESObjectREFR, float>						 ("GetTotalItemWeight",		"ObjectReference", GetTotalItemWeight));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetTotalArmorWeight),		TESObjectREFR, float>						 ("GetTotalArmorWeight",	"ObjectReference", GetTotalArmorWeight));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(SetItemHealthPercent),	TESObjectREFR, void, float>					 ("SetItemHealthPercent",	"ObjectReference", SetItemHealthPercent));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetItemMaxCharge),		TESObjectREFR, float>						 ("GetItemMaxCharge",		"ObjectReference", GetItemMaxCharge));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(SetItemMaxCharge),		TESObjectREFR, void, float>					 ("SetItemMaxCharge",		"ObjectReference", SetItemMaxCharge));
	    VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetItemCharge),			TESObjectREFR, float>						 ("GetItemCharge",			"ObjectReference", GetItemCharge));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(SetItemCharge),			TESObjectREFR, void, float>					 ("SetItemCharge",			"ObjectReference", SetItemCharge));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetEnchantment),			TESObjectREFR, EnchantmentItem*>			 ("GetEnchantment",			"ObjectReference", GetEnchantment));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(SetEnchantment),			TESObjectREFR, void, EnchantmentItem*, float>("SetEnchantment",			"ObjectReference", SetEnchantment));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetPoison),				TESObjectREFR, AlchemyItem*>				 ("GetPoison",				"ObjectReference", GetPoison));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(SetDisplayName),			TESObjectREFR, bool, BSFixedString, bool>	 ("SetDisplayName",			"ObjectReference", SetDisplayName));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(ResetInventory),			TESObjectREFR, void>						 ("ResetInventory",			"ObjectReference", ResetInventory));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(IsOffLimits),				TESObjectREFR, bool>						 ("IsOffLimits",			"ObjectReference", IsOffLimits));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetEnableParent),			TESObjectREFR, TESObjectREFR*>				 ("GetEnableParent",		"ObjectReference", GetEnableParent));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetNumReferenceAliases),	TESObjectREFR, uint32_t>					 ("GetNumReferenceAliases", "ObjectReference", GetNumReferenceAliases));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetNthReferenceAlias),	TESObjectREFR, BGSRefAlias*, uint32_t>		 ("GetNthReferenceAlias",	"ObjectReference", GetNthReferenceAlias));
		VM->RegisterFunction(new BSScript::NativeFunction<false,   NFDLSE(GetAllForms),				TESObjectREFR, void, BGSListForm*>			 ("GetAllForms",			"ObjectReference", GetAllForms));

		return true;
	}
}