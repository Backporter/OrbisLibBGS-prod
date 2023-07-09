#pragma once

#include "../G/GMemory.h"

#include <stdint.h>

#define GFC_REFCOUNTALLOC_CHECK_DELETE(class_name, p)

namespace ConsoleRE
{
	template <typename T, uint32_t N>
	class GRefCountBaseStatImpl : public T
	{
	public:
		GFC_MEMORY_REDEFINE_NEW_IMPL(T, GFC_REFCOUNTALLOC_CHECK_DELETE, N);
	public:
	};
}