#include "../../../OrbisUtil/include/Relocation.h"

#include "../E/ExtraAliasInstanceArray.h"

namespace ConsoleRE
{
	ExtraAliasInstanceArray::ExtraAliasInstanceArray() : BSExtraData(), aliases(), lock()
	{
		//
		Relocation<uintptr_t> vtbl("RTTI_ExtraAliasInstanceArray:.data.rel.ro", 0x1D1C570);
		*((uintptr_t*)this) = vtbl.address();
	}

	ExtraAliasInstanceArray::~ExtraAliasInstanceArray()
	{
		for (auto& aliase : aliases)
		{
			free(aliase);
		}
	}

	uint32_t ExtraAliasInstanceArray::GetType() const
	{
		return TypeID;
	}
}