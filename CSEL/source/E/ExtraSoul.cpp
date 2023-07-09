#include "../../../OrbisUtil/include/Relocation.h"

#include "../E/ExtraSoul.h"

namespace ConsoleRE
{
	ExtraSoul::ExtraSoul() : ExtraSoul(0)
	{}


	ExtraSoul::ExtraSoul(uint8_t a_soulLevel) : BSExtraData(), soul(a_soulLevel)
	{
		Relocation<uintptr_t*> vtbl("RTTI_ExtraSoul:.data.rel.ro", 0x1D1BF40);
		*((uintptr_t*)this) = vtbl.address();
	}

	uint32_t ExtraSoul::GetType() const
	{
		return TypeID;
	}

	bool ExtraSoul::IsNotEqual(const BSExtraData* a_rhs) const
	{
		auto rhs = static_cast<const ExtraSoul*>(a_rhs);
		return soul != rhs->soul;
	}
}