#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include <stdint.h>

namespace ConsoleRE
{
	class NiRefObject
	{
	public:
		NiRefObject()
		{
			__sync_add_and_fetch(GetTotalObjectCount(), 1);
		}
		
		virtual ~NiRefObject()
		{
			__sync_sub_and_fetch(GetTotalObjectCount(), 1);
		}

		// add
		virtual void DeleteThis(void)
		{
			delete this;
		}

		void IncrementRef()
		{
			__sync_add_and_fetch(&refcount, 1);
		}

		void DeincrementRef()
		{
			if (__sync_sub_and_fetch(&refcount, 1) == 0)
			{
				DeleteThis();
			}
		}

		uint32_t GetRefCount() const noexcept
		{
			return refcount;
		}

		volatile uint32_t* GetTotalObjectCount()
		{
			static Relocation<volatile uint32_t*> totalObjectCount("", 0x37C7178);
			return totalObjectCount.get();
		}
	public:
		volatile int32_t refcount;
		uint32_t		 Pad0C;
	};
	static_assert(sizeof(NiRefObject) == 0x10);
}