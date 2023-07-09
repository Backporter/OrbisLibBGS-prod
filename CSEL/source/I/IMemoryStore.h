#pragma once

#include "../I/IMemoryStoreBase.h"

namespace ConsoleRE
{
	class IMemoryStore : public IMemoryStoreBase
	{
	public:
		~IMemoryStore() override = default;
		
		// add
		virtual void* AllocateAlignImpl(size_t a_size, uint32_t a_alignment) = 0;
		virtual void  DeallocateAlignImpl(void*& a_block) = 0;
		virtual void* TryAllocateImpl(size_t a_size, uint32_t a_alignment)  { return nullptr; }
	public:
	};
	static_assert(sizeof(IMemoryStore) == 0x8);
}