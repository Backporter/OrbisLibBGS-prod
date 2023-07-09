#pragma once
#include "../N/NiRefObject.h"

namespace ConsoleRE
{
	class BSHandleRefObject : public NiRefObject
	{
	public:
		enum
		{
			kRefCountMask = 0x3FF,
			kHandleValid = 1 << 10
		};
	public:
		~BSHandleRefObject() override
		{
			refcount &= kRefCountMask;
			__sync_sub_and_fetch(GetTotalObjectCount(), 1);
		}

		bool IsHandleValid() const 
		{ 
			return static_cast<bool>(refcount & kHandleValid); 
		}

		uint32_t GetRefCount() const 
		{ 
			return refcount & kRefCountMask; 
		}

		void IncrementRef()
		{
			__sync_add_and_fetch(&refcount, 1);
		}

		void DeincrementRef()
		{
			if ((__sync_sub_and_fetch(&refcount, 1) & kRefCountMask) == 0)
			{
				DeleteThis();
			}
		}
	};
}