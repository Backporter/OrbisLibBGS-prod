#include "../../../OrbisUtil/include/Relocation.h"

#include "../E/ExtraEncounterZone.h"

namespace ConsoleRE
{
	ExtraEncounterZone::ExtraEncounterZone() : ExtraEncounterZone(nullptr)
	{}

	ExtraEncounterZone::ExtraEncounterZone(BGSEncounterZone* a_zone) : BSExtraData(), zone(a_zone)
	{
		Relocation<uintptr_t> vtbl("RTTI_ExtraEncounterZone:.data.rel.ro", 0x1D1D048);
		*((uintptr_t*)this) = vtbl.address();
	}

	uint32_t ExtraEncounterZone::GetType() const
	{
		return TypeID;
	}

	bool ExtraEncounterZone::IsNotEqual(const BSExtraData* a_rhs) const
	{
		auto rhs = static_cast<const ExtraEncounterZone*>(a_rhs);
		return zone != rhs->zone;
	}
}