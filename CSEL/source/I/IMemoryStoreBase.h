#pragma once

namespace ConsoleRE
{
	struct MemoryStats
	{
	public:
		const char*		name;
		size_t			usedSize;
		size_t			committedSize;
		size_t			reservedSize;
		uint32_t		overhead;
		uint32_t		pad24;
		size_t			freeSize;
	};
	static_assert(sizeof(MemoryStats) == 0x30);

	class IMemoryStoreBase 
	{
	public:
		virtual ~IMemoryStoreBase() = default;
		
		// add
		virtual size_t		Size(const void* a_mem) const = 0;
		virtual void        GetMemoryStats(MemoryStats* a_stats) = 0;
		virtual bool        ContainsBlockImpl(const void* a_block) const = 0;
	public:
	};
	static_assert(sizeof(IMemoryStoreBase) == 0x8);
}