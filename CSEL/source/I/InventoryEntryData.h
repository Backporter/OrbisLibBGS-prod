#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include "../B/BSTList.h"

namespace ConsoleRE
{
	class Actor;
	class ExtraDataList;
	class TESBoundObject;
	class TESForm;

	class InventoryEntryData
	{
	public:
		InventoryEntryData() = default;
		InventoryEntryData(TESBoundObject* a_object, int32_t a_countDelta) : form(a_object), countDelta(a_countDelta) {}
		~InventoryEntryData() { delete extraLists; }

		void                                          AddExtraList(ExtraDataList* a_extra);
		const char*									  GetDisplayName();
		double										  GetEnchantmentCharge();
		constexpr TESBoundObject*					  GetObject() noexcept { return form; }
		constexpr const TESBoundObject*				  GetObject() const noexcept { return form; }
		TESForm*									  GetOwner();
		uint32_t									  GetSoulLevel();

		int32_t GetValue() const
		{
			using func_t = decltype(&InventoryEntryData::GetValue);
			Relocation<func_t> func("", 0x1365C0);
			return func(this);
		}

		float GetWeight();
		bool IsEnchanted();
		bool IsLeveled();
		bool IsWorn();

		bool IsOwnedBy(Actor* a_testOwner, bool a_defaultTo = true)
		{
			return IsOwnedBy(a_testOwner, GetOwner(), a_defaultTo);
		}

		bool IsOwnedBy(Actor* a_testOwner, TESForm* a_itemOwner, bool a_defaultTo = true)
		{
			return IsOwnedBy_Impl(a_testOwner, a_itemOwner, a_defaultTo);
		}

		bool IsQuestObject()
		{
			using func_t = decltype(&InventoryEntryData::IsQuestObject);
			Relocation<func_t> func("", 0x134FB0);
			return func(this);
		}
	public:
		TESBoundObject*						form{ nullptr };
		BSSimpleList<ExtraDataList*>*		extraLists{ nullptr };
		uint32_t							countDelta{ 0 };
	private:
		// const char* GetDisplayName()														   { Relocation<const char*(*)(decltype(this))>					 func("InventoryEntryData::GetDisplayName",    0x137290); return func(this); }
		// uint32_t	GetSoulLevel()															   { Relocation<uint32_t(*)(decltype(this))>					 func("InventoryEntryData::GetSoulLevel",      0x136BB0); return func(this); }
		// bool	IsOwnedBy(Actor* a_testOwner, bool a_defaultTo = true)						   { Relocation<bool(*)(decltype(this), Actor*, bool)>			 func("InventoryEntryData::IsOwnedBy",		   0x136890); return func(this, a_testOwner, a_defaultTo); }

		bool IsOwnedBy_Impl(Actor* a_testOwner, TESForm* a_itemOwner, bool a_defaultTo) 
		{
			using func_t = decltype(&InventoryEntryData::IsOwnedBy_Impl);
			Relocation<func_t> func("", 0x1368F0);
			return func(this, a_testOwner, a_itemOwner, a_defaultTo); 
		}
	};
}