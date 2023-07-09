#include "../../../OrbisUtil/include/Relocation.h"

#include "../E/ExtraCount.h"

namespace ConsoleRE
{
	ExtraCount::ExtraCount() : ExtraCount(0)
	{}

	ExtraCount::ExtraCount(int16_t a_count) :
		BSExtraData(), count(a_count)
	{
		Relocation<uintptr_t> vtbl("RTTI_ExtraCount:.data.rel.ro", 0x1D1BF10);
		*((uintptr_t*)this) = vtbl.address();
	}


	uint32_t ExtraCount::GetType() const
	{
		return 36;
	}

	bool ExtraCount::IsNotEqual(const BSExtraData* a_rhs) const
	{
		auto rhs = static_cast<const ExtraCount*>(a_rhs);
		return count != rhs->count;
	}
}