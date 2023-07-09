#pragma once

#include "../../OrbisUtil/include/Relocation.h"

#include "Offsets_RTTI.h"

namespace ConsoleRE
{
	inline void* RTDynamicCast(const void* a_obj, Relocation<void**> a_src, Relocation<void**> a_dst)
	{
		Relocation<void*(*)(const void*, void*, void*, long)> __dynamic_cast("", 0x17153D8);
		return  __dynamic_cast(a_obj, *a_src.get(), *a_dst.get(), 0);
	}
}

#if USE_TEMPLATE_RTTI
#else
#define TES_RTTI(obj, from, to) (to*) ConsoleRE::RTDynamicCast(obj, RTTI_ ##from, RTTI_ ##to);
#endif