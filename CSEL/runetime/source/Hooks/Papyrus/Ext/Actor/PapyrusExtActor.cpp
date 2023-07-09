#include "../Actor/PapyrusExtActor.h"

#include "../../../../../../../OrbisUtil/include/CryptoHandler.h"

#include "../../../MessageQueueUI/MessageQueue.h"

#include "../../../../../Internal/Tasks/Tasks/TaskUpdateExpression.h"
#include "../../../../../Internal/Tasks/Tasks/TaskUpdateWeight.h"
#include "../../../../../Internal/Tasks/Tasks/TaskRegenHead.h"
#include "../../../../../Internal/Tasks/Tasks/TaskChangeHeadPart.h"

#include "../../../../../../source/A/AIProcess.h"
#include "../../../../../../source/B/BGSDefaultObjectManager.h"
#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/T/TESForm.h"
#include "../../../../../../source/F/FormTraits.h"
#include "../../../../../../source/B/BGSEquipmentManger.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/A/Actor.h"
#include "../../../../../../source/C/Character.h"
#include "../../../../../../source/S/SpellItem.h"
#include "../../../../../../source/E/ExtraContainerChanges.h"
#include "../../../../../../source/RTTI.h"

//
#include "../../../../../../source/P/PackUnpackImpl.h"
//

namespace PapyrusExtActor
{
	// I really hate doing this...
	using namespace ConsoleRE;

	std::vector<TESFaction*> GetFactions(Actor* thisActor, int32_t gte, int32_t lte)
	{
		std::vector<TESFaction*> factions;
	
		if (thisActor)
		{
			if (gte > SCHAR_MAX)
				gte = SCHAR_MAX;
			if (gte < SCHAR_MIN)
				gte = SCHAR_MIN;

			if (lte < SCHAR_MIN)
				lte = SCHAR_MIN;
			if (lte > SCHAR_MAX)
				lte = SCHAR_MAX;
	
			std::set<TESFaction*> rankSet;
			
			auto lambda = [&](TESFaction* faction, int8_t rank) -> bool
			{
				if (rank >= gte && rank <= lte)
				{
					rankSet.insert(faction);
				}

				return false;
			};

			thisActor->VisitFactions(lambda);
	
			for (auto it = rankSet.begin(); it != rankSet.end(); ++it)
			{
				factions.push_back(*it);
			}
		}
	
		return factions;
	}

	TESForm*		GetWornForm(Actor* thisActor, uint32_t mask)
	{
		TESBoundObject*	s_form	  = nullptr;
		ExtraDataList*	s_List	  = nullptr;
		Helper::EquipmentSlotMatcher matcher(mask);
		
		ExtraContainerChanges* pContainerChanges = thisActor->extraList.GetByType<ExtraContainerChanges>();
		if (pContainerChanges) 
		{
			pContainerChanges->FindEquipped(matcher, s_form, s_List);
			return s_form;
		}

		return nullptr;
	}

	BGSEquipSlot*	GetEquipSlotById(int32_t slotId)
	{
		if (slotId == 1)
			return BGSDefaultObjectManager::GetSingleton()->GetRightEquippedSlot();
		else if (slotId == 2)
			return BGSDefaultObjectManager::GetSingleton()->GetLeftEquipedSlot();
		else
			return NULL;
	}

	uint32_t		GetSpellCount(Actor* thisActor)
	{
		if (!thisActor) { return NULL; }

		return thisActor->addedSpells.size();

	}

	SpellItem*		GetNthSpell(Actor* thisActor, uint32_t n)
	{
		if (!thisActor) { return NULL; };

		return thisActor->addedSpells[n];
	}

	TESForm*		GetEquippedObject(Actor * thisActor, uint32_t slot)
	{
		if (!thisActor) return NULL;

		if (slot == 2)
			return thisActor->selectedPower;
		else
			return thisActor->GetEquippedObject(slot == 0);
	}

	bool			CanEquipBothHands(Actor* actor, TESForm * item)
	{
		BGSEquipType * equipType = TES_RTTI(item, TESForm, BGSEquipType);
		if (!equipType)
			return false;

		BGSEquipSlot * equipSlot = equipType->equipSlot;
		if (!equipSlot)
			return false;

		if (equipSlot == BGSDefaultObjectManager::GetSingleton()->GetEquipedSlots())
		{
			return true;
		}
		else if (equipSlot == BGSDefaultObjectManager::GetSingleton()->GetLeftEquipedSlot() || equipSlot == BGSDefaultObjectManager::GetSingleton()->GetRightEquippedSlot())
		{
			return (actor->race->data.flags & 0x40000000) && item->IsWeapon();
		}

		return false;
	}

	bool			IsSwimming(Actor * thisActor)
	{
		if (!thisActor)
		{
			return false;
		}

		return thisActor->IsSwimming();
	}

	void			SheatheWeapon(Actor * thisActor)
	{
		if (thisActor) 
		{
			thisActor->DrawWeaponMagicHands(false);
		}
	}

	void			SetExpressionPhoneme(Actor * thisActor, uint32_t index, float value)
	{
		MessageQueue::UI::PushQueue(new Tasks::TaskUpdateExpression(thisActor, 3, index, value));
	}

	void			SetExpressionModifier(Actor * thisActor, uint32_t index, float value)
	{
		MessageQueue::UI::PushQueue(new Tasks::TaskUpdateExpression(thisActor, 2, index, value));
	}

	void			ResetExpressionOverrides(Actor * thisActor)
	{
		MessageQueue::UI::PushQueue(new Tasks::TaskUpdateExpression(thisActor, 255, 0, 0));
	}

	bool			IsAIEnabled(Actor * thisActor)
	{
		if (!thisActor)
			return false;

		return (thisActor->boolBits & 2) == 2;
	}

	void			ResetAI(Actor * thisActor)
	{
		if (!thisActor)
			return;

		uint32_t flags = thisActor->formFlags;

		if (!(flags & 0x800) && !(flags & 0x20))
			thisActor->EvaluatePackage(0, 1);
	}

	void			UpdateWeight(Actor * thisActor, float neckDelta)
	{
		thisActor->DoReset3D(true);
		MessageQueue::UI::PushQueue(new Tasks::TaskUpdateWeight(thisActor, neckDelta, 0, true));
	}

	void			RegenerateHead(Actor * thisActor)
	{
		MessageQueue::UI::PushQueue(new Tasks::TaskRegenHead(thisActor));
	}

	void			Reset3D(Actor* a_actor)
	{
		auto* s_cast = TES_RTTI(a_actor, Actor, Character);
		if (s_cast)
			s_cast->DoReset3D(false);
	}

	void			ChangeHeadPart(Actor * thisActor, BGSHeadPart * newPart)
	{
		if (!thisActor || !newPart)
			return;

		TESNPC* npc = TES_RTTI(thisActor->data.objectReference, TESForm, TESNPC);
		if (npc) 
		{
			if (newPart->type != 0) 
			{
				BGSHeadPart * oldPart = npc->GetCurrentHeadPartByType(newPart->type);
				npc->ChangeHeadPart(newPart);
				MessageQueue::UI::PushQueue(new Tasks::TaskChangeHeadPart(thisActor, oldPart, newPart));
			}
		}
	}

	void			ReplaceHeadPart(Actor * thisActor, BGSHeadPart * oldPart, BGSHeadPart * newPart)
	{
		if (!thisActor || !newPart)
			return;

		TESNPC* npc = TES_RTTI(thisActor->data.objectReference, TESForm, TESNPC);
		if (npc) 
		{
			if (!oldPart) 
			{
				oldPart = npc->GetCurrentHeadPartByType(newPart->type);
			}

			if (newPart->type != 0 && oldPart && oldPart->type == newPart->type) 
			{
				MessageQueue::UI::PushQueue(new Tasks::TaskChangeHeadPart(thisActor, oldPart, newPart));
			}
		}
	}

	int32_t			GetEquippedItemId(Actor * thisActor, uint32_t slot)
	{	
		TESBoundObject*	s_dstForm = nullptr;
		ExtraDataList*	s_dstList = nullptr;

		if (!thisActor)
			return NULL;
	
		TESForm * equippedForm = thisActor->GetEquippedObject(slot == 0);
		if (!equippedForm)
			return 0;
	
		ExtraContainerChanges* containerChanges = thisActor->extraList.GetByType<ExtraContainerChanges>();
		if (!containerChanges)
			return 0;

		Helper::EquipmentFormMatcher matcher(equippedForm);
		containerChanges->FindEquipped(matcher, s_dstForm, s_dstList, slot == 1, slot == 0);

		if (!s_dstForm || !s_dstList)
			return 0;

		const char* name = s_dstList->GetDisplayName(s_dstForm);
		if (!name)
		{
			TESFullName* fullname = TES_RTTI(s_dstForm, TESForm, TESFullName);
			if (fullname)
				name = fullname->name.m_data;
		}

		if (!name)
			return 0;

		return xUtilty::CryptoHandler::GetCRC32(name, s_dstForm->FormID & 0x00FFFFFF);
	}

	int32_t			GetWornItemId(Actor* thisActor, uint32_t mask)
	{
		TESBoundObject*		s_dstForm = nullptr; 
		ExtraDataList*		s_dstList = nullptr;

		ExtraContainerChanges* containerChanges = thisActor->extraList.GetByType<ExtraContainerChanges>();
		if (!containerChanges)
			return 0;
	
		Helper::EquipmentSlotMatcher matcher(mask);
		containerChanges->FindEquipped(matcher, s_dstForm, s_dstList);
	
		if (!s_dstForm || !s_dstList)
			return 0;

		const char* name = s_dstList->GetDisplayName(s_dstForm);
		if (!name)
		{
			TESFullName* fullname = TES_RTTI(s_dstForm, TESForm, TESFullName);
			if (fullname)
				name = fullname->name.m_data;
		}

		if (!name)
			return 0;

		return xUtilty::CryptoHandler::GetCRC32(name, s_dstForm->FormID & 0x00FFFFFF);
	}
	
	TESObjectREFR*	GetFurnitureReference(Actor* thisActor)
	{
		NiPointer<TESObjectREFR> refr;
	
		if (!thisActor)
		{
			return NULL;
		}
	
		auto* processManager = thisActor->currentProcess;
		if(!processManager)
		{
			return NULL;
		}

		auto* middleProcess = processManager->middleHigh;
		if(!middleProcess)
		{
			return NULL;
		}
		
		uint32_t furnitureHandle = middleProcess->occupiedFurniture;
		if(furnitureHandle == (*Relocation<uint32_t*>("", 0x20BD820)) || furnitureHandle == 0)
			return NULL;
	

		Relocation<void(*)(uint32_t&, NiPointer<TESObjectREFR>&)> func("", 0x5DB210);
		func(furnitureHandle, refr);

		return refr;
	}

	// void			EquipItemEx(Actor* thisActor, TESForm* item, int32_t slotId, bool preventUnequip, bool equipSound)
	// {
	// 	if (!item)
	// 		return;
	// 
	// 	if (!item->IsMagicItem())
	// 		return;
	// 
	// 	BGSEquipmentManger* equipManager = BGSEquipmentManger::GetSingleton();
	// 	if (!equipManager)
	// 		return;
	// 
	// 	ExtraContainerChanges* containerChanges = static_cast<ExtraContainerChanges*>(thisActor->extraList.GetByType(ExtraContainerChanges::TypeID));
	// 	InventoryChanges* containerData = containerChanges ? containerChanges->changes : NULL;
	// 	if (!containerData)
	// 		return;
	// 
	// 	InventoryEntryData* entryData = containerData->CreateEquipEntryData(item);
	// 	if (!entryData)
	// 		return;
	// 
	// 	BGSEquipSlot* targetEquipSlot = GetEquipSlotById(slotId);
	// 
	// 	int32_t itemCount = entryData->countDelta;
	// 	int32_t equipCount = item->IsAmmo() ? itemCount : 1;
	// 
	// 	bool isTargetSlotInUse = false;
	// 	bool hasItemMinCount = itemCount > 0;
	// 
	// 	BaseExtraList* rightEquipList = NULL;
	// 	BaseExtraList* leftEquipList  = NULL;
	// 	BaseExtraList* curEquipList   = NULL;
	// 	BaseExtraList* enchantList    = NULL;
	// 
	// 	if (hasItemMinCount)
	// 	{
	// 		
	// 		entryData->GetExtraWornBaseLists(&rightEquipList, &leftEquipList);
	// 
	// 		// Case 1: Already equipped in both hands.
	// 		if (leftEquipList && rightEquipList)
	// 		{
	// 			isTargetSlotInUse = true;
	// 			curEquipList = (targetEquipSlot == BGSDefaultObjectManager::GetLeftEquipedSlot()) ? leftEquipList : rightEquipList;
	// 			enchantList = NULL;
	// 		}
	// 		// Case 2: Already equipped in right hand.
	// 		else if (rightEquipList)
	// 		{
	// 			isTargetSlotInUse = targetEquipSlot == BGSDefaultObjectManager::GetRightEquippedSlot();
	// 			curEquipList = rightEquipList;
	// 			enchantList = NULL;
	// 		}
	// 		// Case 3: Already equipped in left hand.
	// 		else if (leftEquipList)
	// 		{
	// 			isTargetSlotInUse = targetEquipSlot == BGSDefaultObjectManager::GetLeftEquipedSlot();
	// 			curEquipList = leftEquipList;
	// 			enchantList = NULL;
	// 		}
	// 		// Case 4: Not equipped yet.
	// 		else
	// 		{
	// 			isTargetSlotInUse = false;
	// 			curEquipList = NULL;
	// 			enchantList = entryData->extraLists->GetItem(0);
	// 		}
	// 	}
	// 
	// 	// Free temp equip entryData
	// 	entryData->Delete();
	// 
	// 	// Normally EquipManager would update CannotWear, if equip is skipped we do it here
	// 	if (isTargetSlotInUse)
	// 	{
	// 		BSExtraData* xCannotWear = curEquipList->GetByType(kExtraData_CannotWear);
	// 		if (xCannotWear && !preventUnequip)
	// 			curEquipList->Remove(kExtraData_CannotWear, xCannotWear);
	// 		else if (!xCannotWear && preventUnequip)
	// 			curEquipList->Add(kExtraData_CannotWear, ExtraCannotWear::Create());
	// 
	// 		// Slot in use, nothing left to do
	// 		return;
	// 	}
	// 
	// 	// For dual wield, prevent that 1 item can be equipped in two hands if its already equipped
	// 	bool isEquipped = (rightEquipList || leftEquipList);
	// 	if (targetEquipSlot && isEquipped && CanEquipBothHands(thisActor, item))
	// 		hasItemMinCount = itemCount > 1;
	// 
	// 	if (!isTargetSlotInUse && hasItemMinCount)
	// 		equipManager->EquipItem(thisActor, item, enchantList, equipCount, targetEquipSlot, equipSound, preventUnequip, false, NULL);
	// }

	// void UnequipItemEx(Actor* thisActor, TESForm* item, int32_t slotId, bool preventEquip)
	// {
	// 	if (!item)
	// 		return;
	// 
	// 	if (!item->Has3D())
	// 		return;
	// 
	// 	EquipManager* equipManager = EquipManager::GetSingleton();
	// 	if (!equipManager)
	// 		return;
	// 
	// 	ExtraContainerChanges* containerChanges = static_cast<ExtraContainerChanges*>(thisActor->extraData.GetByType(kExtraData_ContainerChanges));
	// 	ExtraContainerChanges::Data* containerData = containerChanges ? containerChanges->data : NULL;
	// 	if (!containerData)
	// 		return;
	// 
	// 	InventoryEntryData* entryData = containerData->FindItemEntry(item);
	// 	if (!entryData)
	// 		return;
	// 
	// 	BGSEquipSlot * targetEquipSlot = GetEquipSlotById(slotId);
	// 
	// 	int32_t itemCount = entryData->countDelta;
	// 
	// 	// For ammo, use count, otherwise always equip 1
	// 	int32_t equipCount = item->IsAmmo() ? itemCount : 1;
	// 
	// 	BaseExtraList * rightEquipList = NULL;
	// 	BaseExtraList * leftEquipList = NULL;
	// 
	// 	entryData->GetExtraWornBaseLists(&rightEquipList, &leftEquipList);
	// 
	// 	bool unequipRight = false;
	// 	bool unequipLeft = false;
	// 
	// 	if (targetEquipSlot == GetRightHandSlot())
	// 		unequipRight = true;
	// 	else if (targetEquipSlot == GetLeftHandSlot())
	// 		unequipLeft = true;
	// 	else
	// 		unequipRight = unequipLeft = true;
	// 
	// 	if (rightEquipList && unequipRight)
	// 	{
	// 		BSExtraData* xCannotWear = rightEquipList->GetByType(kExtraData_CannotWear);
	// 		if (xCannotWear)
	// 			rightEquipList->Remove(kExtraData_CannotWear, xCannotWear);
	// 
	// 		CALL_MEMBER_FN(equipManager, UnequipItem)(thisActor, item, rightEquipList, equipCount, GetRightHandSlot(), true, preventEquip, true, false, NULL);
	// 	}
	// 
	// 	if (leftEquipList && unequipLeft)
	// 	{
	// 		BSExtraData* xCannotWear = leftEquipList->GetByType(kExtraData_CannotWear);
	// 		if (xCannotWear)
	// 			leftEquipList->Remove(kExtraData_CannotWear, xCannotWear);
	// 
	// 		CALL_MEMBER_FN(equipManager, UnequipItem)(thisActor, item, leftEquipList, equipCount, GetLeftHandSlot(), true, preventEquip, true, false, NULL);
	// 	}
	// }

	//void EquipItemById(Actor* thisActor, TESForm* item, int32_t itemId, int32_t slotId, bool preventUnequip /*unused*/, bool equipSound)
	//{
	//	if (!item || !item->Has3D() || itemId == 0)
	//		return;
	//
	//	// Can't be improved or enchanted, no need for itemId
	//	if (item->IsAmmo())
	//	{
	//		EquipItemEx(thisActor, item, slotId, preventUnequip, equipSound);
	//		return;
	//	}
	//
	//	BGSEquipmentManger* equipManager = BGSEquipmentManger::GetSingleton();
	//	if (!equipManager)
	//		return;
	//
	//	ExtraContainerChanges* containerChanges = static_cast<ExtraContainerChanges*>(thisActor->extraList.GetByType(ExtraContainerChanges::TypeID));
	//	InventoryChanges* containerData = containerChanges ? containerChanges->Unk10 : NULL;
	//	if (!containerData)
	//		return;
	//
	//	InventoryEntryData::EquipData itemData;
	//	containerData->GetEquipItemData(itemData, item, itemId);
	//
	//	BGSEquipSlot * targetEquipSlot = GetEquipSlotById(slotId);
	//	bool isTargetSlotInUse = false;
	//
	//	int32_t itemCount = itemData.itemCount;
	//
	//	// Need at least 1 (maybe 2 for dual wield, checked later)
	//	bool hasItemMinCount = itemCount > 0;
	//	bool canDualWield = false;
	//
	//	BaseExtraList * newEquipList = itemData.itemExtraList;
	//
	//	if (hasItemMinCount)
	//	{
	//		// Case 1: Type already equipped in both hands.
	//		if (itemData.isTypeWorn && itemData.isTypeWornLeft)
	//		{
	//			isTargetSlotInUse = true;
	//		}
	//		// Case 2: Type already equipped in right hand.
	//		else if (itemData.isTypeWorn)
	//		{
	//			isTargetSlotInUse = targetEquipSlot == GetRightHandSlot() || targetEquipSlot == NULL;
	//		}
	//		// Case 3: Type already equipped in left hand.
	//		else if (itemData.isTypeWornLeft)
	//		{
	//			isTargetSlotInUse = targetEquipSlot == GetLeftHandSlot();
	//		}
	//		// Case 4: Type not equipped yet.
	//		else
	//		{
	//			isTargetSlotInUse = false;
	//		}
	//	}
	//
	//	// This also returns if the target slot is in use by another weapon of the same type.
	//	// Could handle this, but switching them here causes a bug (0 damage) for some reason.
	//	// So we just skip it. Can be handled on the Papyrus side.
	//	if (isTargetSlotInUse || !hasItemMinCount)
	//		return;
	//
	//	bool isItemEquipped = itemData.isItemWorn || itemData.isItemWornLeft;
	//
	//	// Does this item qualify for dual wield?
	//	if (item->IsWeapon() && targetEquipSlot && isItemEquipped && CanEquipBothHands(thisActor, item))
	//		canDualWield = true;
	//
	//	// Not enough items to dual wield, weapon has to swap hands
	//	if (canDualWield && itemCount < 2)
	//	{
	//		BaseExtraList* unequipList = itemData.isItemWornLeft ? itemData.wornLeftExtraList : itemData.wornExtraList;
	//
	//		// Unequip might destroy passed list (return value indicates that).
	//		newEquipList = equipManager->UnequipItem(thisActor, item, unequipList, 1, 0, false, false, true, false, NULL) ? NULL : unequipList;
	//	}
	//
	//	equipManager->EquipItem(thisActor, item, newEquipList, 1, targetEquipSlot, equipSound, preventUnequip, false, NULL);
	//}

	bool RegisterActor(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		//
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetFactions), Actor, std::vector<TESFaction*>, int32_t, int32_t>("GetFactions", "Actor", GetFactions));
		//

		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetWornForm),					Actor, TESForm*, uint32_t>								("GetWornForm",					"Actor", GetWornForm));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetEquippedObject),			Actor, TESForm*, uint32_t>								("GetEquippedObject",			"Actor", GetEquippedObject));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetSpellCount),				Actor, uint32_t>										("GetSpellCount",				"Actor", GetSpellCount));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthSpell),					Actor, SpellItem*, uint32_t>							("GetNthSpell",					"Actor", GetNthSpell));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(Reset3D),						Actor, void>											("QueueNiNodeUpdate",			"Actor", Reset3D));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(ChangeHeadPart),				Actor, void, BGSHeadPart*>								("ChangeHeadPart",				"Actor", ChangeHeadPart));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(ReplaceHeadPart),				Actor, void, BGSHeadPart*, BGSHeadPart*>				("ReplaceHeadPart",				"Actor", ReplaceHeadPart));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(RegenerateHead),				Actor, void>											("RegenerateHead",				"Actor", RegenerateHead));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(UpdateWeight),					Actor, void, float>										("UpdateWeight",				"Actor", UpdateWeight));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(IsAIEnabled),					Actor, bool>											("IsAIEnabled",					"Actor", IsAIEnabled));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(ResetAI),						Actor, void>											("ResetAI",						"Actor", ResetAI));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(IsSwimming),					Actor, bool>											("IsSwimming",					"Actor", IsSwimming));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SheatheWeapon),				Actor, void>											("SheatheWeapon",				"Actor", SheatheWeapon));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetEquippedItemId),			Actor, int32_t, uint32_t>								("GetEquippedItemId",			"Actor", GetEquippedItemId));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetWornItemId),				Actor, int32_t, uint32_t>								("GetWornItemId",				"Actor", GetWornItemId));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetFurnitureReference),		Actor, TESObjectREFR*>									("GetFurnitureReference",		"Actor", GetFurnitureReference));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetExpressionPhoneme),			Actor, void, uint32_t, float>							("SetExpressionPhoneme",		"Actor", SetExpressionPhoneme));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetExpressionModifier),		Actor, void, uint32_t, float>							("SetExpressionModifier",		"Actor", SetExpressionModifier));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(ResetExpressionOverrides),		Actor, void>											("ResetExpressionOverrides",	"Actor", ResetExpressionOverrides));
		
		// VM->RegisterFunction(new BSScript::NativeFunction4 <NFDLSE(EquipItemEx),				Actor, void, TESForm*, int32_t, bool, bool>				("EquipItemEx",					"Actor", EquipItemEx,				VM));
		// VM->RegisterFunction(new BSScript::NativeFunction3 <NFDLSE(UnequipItemEx),			Actor, void, TESForm*, int32_t, bool>					("UnequipItemEx",				"Actor", UnequipItemEx,				VM));
		// VM->RegisterFunction(new BSScript::NativeFunction5 <NFDLSE(EquipItemById),			Actor, void, TESForm*, int32_t, int32_t, bool, bool>	("EquipItemById",				"Actor", EquipItemById,				VM));

		return true;
	}
}