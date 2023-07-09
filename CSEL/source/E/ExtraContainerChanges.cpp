#include "../E/ExtraContainerChanges.h"

namespace ConsoleRE
{
	ExtraContainerChanges::ExtraContainerChanges() : ExtraContainerChanges(nullptr)
	{}

	ExtraContainerChanges::ExtraContainerChanges(InventoryChanges* a_changes) : BSExtraData(), changes(a_changes)
	{
		Relocation<uintptr_t> vtbl("RTTI_ExtraContainerChanges:.data.rel.ro", 0x1D1BE20);
		*((uintptr_t*)this) = vtbl.address();
	}

	ExtraContainerChanges::~ExtraContainerChanges()
	{
		delete changes;
	}

	uint32_t ExtraContainerChanges::GetType() const 
	{ 
		return TypeID; 
	}

}