#include "../../../OrbisUtil/include/Relocation.h"

#include "../E/ExtraCharge.h"

namespace ConsoleRE
{
	ExtraCharge::ExtraCharge(float a_charge) : BSExtraData(), charge(a_charge), pad14(0)
	{
		Relocation<uintptr_t*> vtbl("RTTI_ExtraCharge:.data.rel.ro", 0x1d1cc98);
		*((uintptr_t*)this) = vtbl.address();
	}

	ExtraCharge::ExtraCharge() : ExtraCharge(0.0f)
	{}


	uint32_t ExtraCharge::GetType() const
	{
		return TypeID;
	}

	bool ExtraCharge::IsNotEqual(const BSExtraData* a_rhs) const
	{
		return charge != static_cast<const ExtraCharge*>(a_rhs)->charge;
	}
}