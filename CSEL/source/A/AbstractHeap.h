#pragma once

#include "../B/BSAtomic.h"
#include "../I/IMemoryHeap.h"

namespace ConsoleRE
{
	class HeapBlock;
	class HeapBlockFreeHead;

	class AbstractHeap : public IMemoryHeap
	{
	public:
		~AbstractHeap() override;

		// override (IMemoryHeap)
		virtual void          GetMemoryStats(MemoryStats* a_stats) override;
		virtual void*         AllocateAlignImpl(size_t a_size, uint32_t a_alignment) override;
		virtual void*         TryAllocateImpl(size_t a_size, uint32_t a_alignment) override;
		virtual const char*   GetName() const override;
		virtual bool          PointerInHeap(const void* a_pointer) const override;
		virtual void          GetHeapStats(HeapStats* a_stats, bool a_fullBlockInfo) override;
		virtual bool          ShouldTrySmallBlockPools(size_t a_size, MEM_CONTEXT a_context) override;
		virtual uint32_t	  GetPageSize() const override;

		// add
		virtual void*       DoHeapAllocation(size_t a_size, size_t a_initialSize) = 0;
		virtual void        DoHeapFree(void* a_ptr) = 0;
		virtual size_t		CreateMorePages(void* a_memory, size_t a_currentSize, size_t a_requestedBytes);
		virtual size_t		CleanExtraPages(void* a_memory, size_t a_currentSize, size_t a_freeBytes);
		virtual void        DecommitPages(HeapBlock* a_block);
		virtual void        CommitPages(HeapBlock*, size_t);
	public:
		BSCriticalSection	criticalSection;
		const char*			name;
		size_t				minFreeBlockSize;
		uint32_t			pageSize;
		uint32_t			pageSizeFlag;
		size_t				memHeapSize;
		size_t				initialSize;
		size_t				currentSize;
		size_t				wastedMemory;
		size_t				memAllocated;
		size_t				memAllocatedHigh;
		size_t				blockMemAllocated;
		char*				memHeap;
		int32_t				numBlocks;
		uint32_t			pad08C;
		HeapBlock*			blockHead;
		HeapBlock*			blockTail;
		int32_t				numFreeBlocks;
		bool				allowDecommits;
		bool				supportsSwapping;
		uint16_t			pad0A0;
		HeapBlock*			smallFreeLists[32];
		HeapBlockFreeHead*	largeFreeTrees[32];
		uint64_t			Unk288;
	};
	static_assert(sizeof(AbstractHeap) == 0x290);
}