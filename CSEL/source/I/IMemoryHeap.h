#pragma once

#include "../I/IMemoryStore.h"

#include <stdint.h>

namespace ConsoleRE
{
	enum class MEM_CONTEXT : int32_t;

	struct HeapStats
	{
	public:
		const char*  heapName;
		size_t		 memHeapSize;
		size_t		 memHeapCommitted;
		size_t		 memAllocatedToBlocks;
		int32_t		 numBlocks;
		int32_t		 numFreeBlocks;
		size_t		 memFreeInBlocks;
		size_t		 memUsedInBlocks;
		size_t		 smallestFreeBlock;
		size_t		 largestFreeBlock;
		size_t		 heapOverhead;
		size_t		 freeListOverhead;
		size_t		 blockOverhead;
		size_t		 totalFree;
	};
	static_assert(sizeof(HeapStats) == 0x68);

	class IMemoryHeap : public IMemoryStore
	{
	public:
		~IMemoryHeap() override = default;
		
		// override (IMemoryStore)
		bool  ContainsBlockImpl(const void* a_block) const override { return PointerInHeap(a_block); }
		void* AllocateAlignImpl(size_t a_size, uint32_t a_alignment) override { return Allocate(a_size, a_alignment); }
		void  DeallocateAlignImpl(void*& a_block) override { Deallocate(a_block, 0); }

		// add
		virtual const char*					GetName() const = 0;    
		virtual void*                       Allocate(size_t a_size, uint32_t a_alignment) = 0;
		virtual void                        Deallocate(void* a_mem, uint32_t) = 0;
		virtual bool                        PointerInHeap(const void* a_pointer) const = 0;
		virtual size_t						TotalSize(const void* a_pointer) const = 0;
		virtual void                        GetHeapStats(HeapStats* a_stats, bool a_fullBlockInfo) = 0;
		virtual bool                        ShouldTrySmallBlockPools(size_t a_size, MEM_CONTEXT a_context) = 0;
		virtual uint32_t					GetPageSize() const = 0;
	public:
	};
}