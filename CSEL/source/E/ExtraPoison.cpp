#include "../../../OrbisUtil/include/Relocation.h"

#include "../E/ExtraPoison.h"

namespace ConsoleRE
{
	ExtraPoison::ExtraPoison() : ExtraPoison(nullptr, 0)
	{}

	ExtraPoison::ExtraPoison(AlchemyItem* a_poison, int32_t a_count) : BSExtraData(), poison(a_poison), count(a_count)
	{
		Relocation<uintptr_t> vtbl("RTTI_ExtraPoison:.data.rel.ro", 0x1D1C260);
		*((uintptr_t*)this) = vtbl.address();
	}

	uint32_t ExtraPoison::GetType() const
	{
		return TypeID;
	}

	bool ExtraPoison::IsNotEqual(const BSExtraData* a_rhs) const
	{
		return poison != static_cast<const ExtraPoison*>(a_rhs)->poison || count != static_cast<const ExtraPoison*>(a_rhs)->count;
	}
}