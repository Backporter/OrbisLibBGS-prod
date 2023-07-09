#include "../../../OrbisUtil/include/Relocation.h"

#include "../E/ExtraReferenceHandle.h"

namespace ConsoleRE
{
	ExtraReferenceHandle::ExtraReferenceHandle() : ExtraReferenceHandle(0)
	{}

	ExtraReferenceHandle::ExtraReferenceHandle(uint32_t a_containerRef) : BSExtraData(), containerRef(a_containerRef)
	{
		Relocation<uintptr_t> vtbl("RTTI_ExtraReferenceHandle:.data.rel.ro", 0x1D1CE08);
		*((uintptr_t*)this) = vtbl.address();
	}


	uint32_t ExtraReferenceHandle::GetType() const
	{
		return TypeID;
	}

	bool ExtraReferenceHandle::IsNotEqual(const BSExtraData* a_rhs) const
	{
		auto rhs = static_cast<const ExtraReferenceHandle*>(a_rhs);
		return rhs->containerRef != containerRef;
	}


	TESObjectREFR* ExtraReferenceHandle::GetOriginalReference()
	{
		TESObjectREFR* ret = NULL;

		using func_t = void(uint32_t&, TESObjectREFR*&);
		Relocation<func_t*> func("", 0x5DB210);
		func(containerRef, ret);

		return ret;
	}
}