#pragma once

#include "../B/BSAtomic.h"
#include "../I/IMemoryStore.h"

namespace ConsoleRE
{
	class BSSmallBlockAllocator : public IMemoryStore
	{
	public:
		~BSSmallBlockAllocator() override;

		// override (IMemoryStore)
		size_t		Size(const void* a_block) const override;
		void        GetMemoryStats(MemoryStats* a_stats) override;
		bool        ContainsBlockImpl(const void* a_block) const override;
		void*       AllocateAlignImpl(size_t a_size, uint32_t a_alignment) override;
		void        DeallocateAlignImpl(void*& a_freeBlock) override;
		void*       TryAllocateImpl(size_t a_size, uint32_t a_alignment) override;
	public:
	};
}