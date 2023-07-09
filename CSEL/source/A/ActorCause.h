#pragma once

#include "../N/NiPoint3.h"

#include <stdint.h>

namespace ConsoleRE
{
	class ActorCause
	{
	public:
		int32_t DecRefCount()
		{
			return __sync_sub_and_fetch(&refCount, 1);
		}

		int32_t IncRefCount()
		{
			return __sync_add_and_fetch(&refCount, 1);
		}

		int32_t GetRefCount()
		{ 
			return refCount; 
		}
	public:
		uint32_t						actor;
		NiPoint3						origin;
		uint32_t						actorCauseID;
		volatile mutable int32_t		refCount;
	};
	static_assert(sizeof(ActorCause) == 0x18);
}