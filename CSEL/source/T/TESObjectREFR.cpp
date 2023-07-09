#include "TESObjectREFR.h"

#include "../I/InventoryEntryData.h"
#include "..//F/FormTraits.h"
#include "../E/ExtraOwnership.h"

#include <type_traits>

namespace ConsoleRE
{
	TESNPC*					TESObjectREFR::GetActorOwner()
	{
		auto xOwnership = extraList.GetByType<ExtraOwnership>();
		if (xOwnership && xOwnership->owner && xOwnership->owner->Is(43))
		{
			return static_cast<TESNPC*>(xOwnership->owner);
		}
		else 
		{
			return nullptr;
		}
	}

	NiPoint3				TESObjectREFR::GetAngle() 
	{ 
		return data.angle; 
	}
	
	float					TESObjectREFR::GetAngleX() 
	{ 
		return data.angle.x; 
	}
	
	float					TESObjectREFR::GetAngleY() 
	{ 
		return data.angle.y; 
	}
	
	float					TESObjectREFR::GetAngleZ() 
	{ 
		return data.angle.z; 
	}

	TESBoundObject*			TESObjectREFR::GetBaseObject() 
	{ 
		return data.objectReference; 
	}
	
	const TESBoundObject*	TESObjectREFR::GetBaseObject() const 
	{ 
		return data.objectReference; 
	}

	bool					TESObjectREFR::IsMarkedForDeletion()
	{
		return (formFlags & RecordFlags::kDeleted) != 0;
	}

	bool					TESObjectREFR::IsDisabled()
	{
		return (formFlags & RecordFlags::kInitiallyDisabled) != 0;
	}

	const char*				TESObjectREFR::GetDisplayFullName()
	{
		using func_t = decltype(&TESObjectREFR::GetDisplayFullName);
		Relocation <func_t> func("", 0x219490);
		return func(this);
	}

	TESBoundObject*			TESObjectREFR::GetObjectReference() const noexcept 
	{ 
		return data.objectReference; 
	}
	
	void					TESObjectREFR::UpdateHarvestModel(NiAVObject* a_node)
	{
		using func_t = decltype(&TESObjectREFR::UpdateHarvestModel);
		Relocation<func_t> func("", 0xF0EA0);
		return func(this, a_node);
	}

	TESForm*				TESObjectREFR::GetOwner()
	{
		using func_t = decltype(&TESObjectREFR::GetOwner);
		Relocation<func_t> func("", 0x2418F0);
		return func(this);
	}

	TESObjectCELL*			TESObjectREFR::GetParentCell() 
	{ 
		return parentCell; 
	}
	
	NiPoint3				TESObjectREFR::GetPosition() 
	{ 
		return data.location; 
	}
	
	float					TESObjectREFR::GetPositionX() 
	{ 
		return data.location.x; 
	}
	
	float					TESObjectREFR::GetPositionY() 
	{ 
		return data.location.y; 
	}
	
	float					TESObjectREFR::GetPositionZ()
	{ 
		return data.location.z; 
	}

	uint32_t				TESObjectREFR::GetStealValue(const InventoryEntryData* a_entryData, uint32_t a_numItems, bool a_useMult)
	{
		using func_t = decltype(&TESObjectREFR::GetStealValue);
		Relocation<func_t> func("", 0x14EC60);
		return func(this, a_entryData, a_numItems, a_useMult);
	}

	float					TESObjectREFR::GetWeight()
	{
#if true
		auto obj = GetObjectReference();
		return obj ? obj->GetWeight() : 0.0F;
#else
		using func_t = decltype(&TESObjectREFR::GetWeight);
		Relocation<func_t> func("", 0x23D410);
		return func(this);
#endif
	}

	TESWorldSpace*			TESObjectREFR::GetWorldSpace()
	{
#if true
		auto cell = parentCell;
		if (!cell)
		{
			cell = GetSaveParentCell();
		}

		if (cell && cell->IsExteriorCell())
		{
			return cell->worldSpace;
		}
		else 
		{
			return nullptr;
		}
#else
		using func_t = TESWorldSpace*(decltype(this));
		Relocation<func_t*> func("", 0x219930);
		return func(this);
#endif
	}

	float					TESObjectREFR::GetScale()
	{
		using func_t = decltype(&TESObjectREFR::GetScale);
		Relocation<func_t> func("", 0x21A660);
		return func(this);
	}

	bool					TESObjectREFR::IsCrimeToActivate()
	{
		using func_t = decltype(&TESObjectREFR::IsCrimeToActivate);
		Relocation<func_t> func("", 0x2314B0);
		return func(this);
	}

	bool					TESObjectREFR::IsOffLimits()
	{
		return IsCrimeToActivate();
	}
}