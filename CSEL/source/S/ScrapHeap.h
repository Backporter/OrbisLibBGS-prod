#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include "../I/IMemoryStore.h"

namespace ConsoleRE
{
	class ScrapHeap : public IMemoryStore
	{
	public:
		~ScrapHeap() override { }
		
		// override
		size_t		Size(void const* a_mem) const override { return *static_cast<const size_t*>(a_mem) & ~(std::size_t{ 3 } << 62); }
		void        GetMemoryStats(MemoryStats*) override { return; }
		bool        ContainsBlockImpl(const void* a_block) const override { return baseAddress <= a_block && a_block <= endAddress; }
		void*       AllocateAlignImpl(size_t a_size, uint32_t a_alignment) override { return allocate(a_size, a_alignment); }
		
		void        DeallocateAlignImpl(void*& a_block) override
		{
			deallocate(a_block);
			a_block = nullptr;
		}

		void* allocate(size_t a_size, size_t a_allignment)
		{
			using func_t = decltype(&ScrapHeap::allocate);
			Relocation<func_t> func("ScrapHeap::allocate", 0xE2DAE0);
			return func(this, a_size, a_allignment);
		}

		void deallocate(void* a_mem)
		{
			using func_t = decltype(&ScrapHeap::deallocate);
			Relocation<func_t> func("ScrapHeap::deallocate", 0xE2E130);
			return func(this, a_mem);
		}
	public:
		void*		  smallBlocks[6] { nullptr };
		void*		  freeList { nullptr };
		void*         lastBlock { nullptr };
		void*         baseAddress { nullptr };
		void*         endAddress { nullptr };
		void*         commitEnd { nullptr };
		size_t		  reserveSize { 1 << 26 };
		size_t		  minCommit { 1 << 17 };
		size_t		  totalAllocated { 0 };
		uint32_t	  keepPagesRequest { 0 };
		uint32_t	  totalFreeBlocks { 0 };
		uint32_t	  freeSmallBlocks { 0 };
		uint32_t	  totalAllocatedBlocks { 0 };
		uint32_t	  pmpBarrier { 0 };
	};
	static_assert(sizeof(ScrapHeap) == 0x90);
}