#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	struct BSTLocklessQueue
	{
		template <class T, uint32_t SIZE, uint32_t UNKNOWN>
		class PtrMultiProdCons
		{
			T*                     data[SIZE];
			volatile uint32_t	   start;
			volatile uint32_t	   fetched;
			volatile uint32_t	   end;
			volatile uint32_t	   allocated;
		};
		static_assert(sizeof(PtrMultiProdCons<void*, 1, 1>) == 0x18);

		template <class QueueContainer, class T, uint32_t SIZE, uint32_t UNKNOWN>
		struct ObjQueueBase
		{
			T              data[SIZE];
			QueueContainer queued;
			QueueContainer free;
		};

		template <class T, uint32_t SIZE, uint32_t UNKNOWN>
		class ObjMultiProdCons : public ObjQueueBase<PtrMultiProdCons<T, SIZE * 2, UNKNOWN>, T, SIZE, UNKNOWN>
		{
		};
	};
}