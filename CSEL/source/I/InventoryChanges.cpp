#include "../../../OrbisUtil/include/Relocation.h"

#include "InventoryChanges.h"

namespace ConsoleRE
{
	InventoryChanges::InventoryChanges() : InventoryChanges(nullptr)
	{
	}

	InventoryChanges::InventoryChanges(TESObjectREFR* a_ref)
	{
		Ctor(a_ref);
	}

	InventoryChanges::~InventoryChanges()
	{
		Dtor();
	}

	void InventoryChanges::Ctor(TESObjectREFR* a_ref)
	{
		using func_t = decltype(&InventoryChanges::Ctor);
		Relocation<func_t> func("", 0x137C60);
		return func(this, a_ref);
	}

	void InventoryChanges::Dtor()
	{
		using func_t = decltype(&InventoryChanges::Dtor);
		Relocation<func_t> func("", 0x137D70);
		return func(this);
	}
}