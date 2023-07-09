#pragma once

#include "../A/AbstractHeap.h"

namespace ConsoleRE
{
	class MemoryHeap : public AbstractHeap
	{
	public:
		~MemoryHeap() override;
	
		// override (AbstractHeap)
		size_t		Size(const void* a_block) const override;
		void*       Allocate(size_t a_size, uint32_t a_alignment) override;
		void        Deallocate(void* a_pointer, uint32_t) override;
		size_t		TotalSize(const void* a_pointer) const override;
		void        GetHeapStats(HeapStats* a_stats, bool a_fullBlockInfo) override;
		void*       DoHeapAllocation(size_t a_size, size_t a_initialSize) override;
		void        DoHeapFree(void* a_ptr) override;
		size_t		CreateMorePages(void* a_memory, size_t a_currentSize, size_t a_requestedBytes) override;
		size_t		CleanExtraPages(void* a_memory, size_t a_currentSize, size_t a_freeBytes) override;
		void        DecommitPages(HeapBlock* a_block) override;
	public:
		bool		deletingHeap;
	};
	static_assert(sizeof(MemoryHeap) == 0x298);
}