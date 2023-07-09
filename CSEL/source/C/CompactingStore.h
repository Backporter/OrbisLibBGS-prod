#pragma once

#include "../B/BSAtomic.h"
#include "../I/IMemoryStoreBase.h"

namespace ConsoleRE
{
	namespace CompactingStore
	{
		class BlockHeader;
		class FreeBlock;
		class StoreBlock;

		class Store : public IMemoryStoreBase
		{
		public:
			~Store() override;

			// override (IMemoryStoreBase)
			size_t		Size(const void* a_block) const override;
			void        GetMemoryStats(MemoryStats* a_stats) override;
			bool        ContainsBlockImpl(const void* a_block) const override;
		public:
			BSNonReentrantSpinLock lock;
			void*                  allocBase;
			void*                  allocEndMin;
			void*                  allocEnd;
			void*                  storeEnd;
			BlockHeader*           lastBlock;
			FreeBlock*             smallFree[66];
			FreeBlock*             currentFree;
			FreeBlock*             nextMerge;
			StoreBlock*            storeBlockMin;
			StoreBlock*            nextStoreBlock;
			StoreBlock*            freeStoreBlockList;
			pthread_t			   currentThread;
			size_t				   allocated;
			uint32_t			   numAllocatedBlocks;
			size_t				   free;
			uint32_t			   numFreeBlocks;
			uint32_t			   compacted;
			uint32_t			   batchDeallocateTlsSlot;
		};
		static_assert(sizeof(Store) == 0x2A0);
	}
}