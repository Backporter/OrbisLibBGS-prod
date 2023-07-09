#include "../../../OrbisUtil/include/Relocation.h"

#include "../E/ExtraHealth.h"

namespace ConsoleRE
{
	ExtraHealth::ExtraHealth() : ExtraHealth(1.0f)
	{}

	ExtraHealth::ExtraHealth(float a_health) : BSExtraData(), health(a_health), pad14(0)
	{
		Relocation<uintptr_t> vtbl("RTTI_ExtraHealth:.data.rel.ro", 0x1D1CBA8);
		*((uintptr_t*)this) = vtbl.address();
	}

	uint32_t ExtraHealth::GetType() const
	{
		return TypeID;
	}

	bool ExtraHealth::IsNotEqual(const BSExtraData* a_rhs) const
	{
		auto rhs = static_cast<const ExtraHealth*>(a_rhs);
		return health != rhs->health;
	}
}