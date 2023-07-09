#include "../../../OrbisUtil/include/Relocation.h"

#include "../E/ExtraOwnership.h"

namespace ConsoleRE
{
	ExtraOwnership::ExtraOwnership() : ExtraOwnership(nullptr)
	{}
	
	ExtraOwnership::ExtraOwnership(TESForm* a_owner) : BSExtraData(), owner(a_owner)
	{
		Relocation<uintptr_t*> vtbl("RTTI_ExtraOwnership:.data.rel.ro", 0x1D1BE50);
		*((uintptr_t*)this) = vtbl.address();
	}

	uint32_t ExtraOwnership::GetType() const
	{
		return TypeID;
	}

	bool ExtraOwnership::IsNotEqual(const BSExtraData* a_rhs) const
	{
		auto rhs = static_cast<const ExtraOwnership*>(a_rhs);
		return owner != rhs->owner;
	}

}