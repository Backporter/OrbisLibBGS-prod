#pragma once

#include "../N/NiTCollection.h"

#define NiTDefaultAllocator DFALL

namespace ConsoleRE
{
	template <typename T>
	class NiTDefaultAllocator
	{
	public:
		void* Allocate()
		{
			return NiMalloc(sizeof(T));
		}

		void Release(T* a_ptr)
		{
			return NiFree(a_ptr);
		}
	};
}