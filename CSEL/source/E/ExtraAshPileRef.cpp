#include "../../../OrbisUtil/include/Relocation.h"

#include "../E/ExtraAshPileRef.h"

namespace ConsoleRE
{
	ExtraAshPileRef::ExtraAshPileRef() : ExtraAshPileRef(0)
	{}

	ExtraAshPileRef::ExtraAshPileRef(uint32_t a_ref) : BSExtraData(), ashPileRef(a_ref), pad14(0)
	{
		Relocation<uintptr_t> vtbl("RTTI_ExtraAshPileRef:.data.rel.ro", 0x1D1D2B8);
		*((uintptr_t*)this) = vtbl.address();
	}

	uint32_t ExtraAshPileRef::GetType() const
	{
		return TypeID;
	}
}