#pragma once

#include "../G/GList.h"

namespace ConsoleRE
{
	class GSysAllocPaged;
	struct GStatBag;

	class GMemoryHeap : public GListNode<GMemoryHeap>
	{
	public:
		struct HeapDesc
		{
		public:
			HeapDesc(uint32_t a_flags = 0, size_t a_minAlign = 16, size_t a_granularity = 8 * 1024, size_t a_reserve = 8 * 1024, size_t a_threshold = SIZE_MAX, size_t a_limit = 0, uint32_t a_heapID = 0, size_t a_arena = 0) :
				flags(a_flags), pad04(0), minAlign(a_minAlign), granularity(a_granularity), reserve(a_reserve), threshold(a_threshold), limit(a_limit), heapID(a_heapID), arena(a_arena)
			{ }

			void Clear()
			{
				flags = 0;
				granularity = 0;
				minAlign = 16;
				reserve = 0;
				threshold = SIZE_MAX;
				limit = 0;
				heapID = 0;
				arena = 0;
			}
		public:
			uint32_t									flags;
			uint32_t									pad04;
			size_t										minAlign;
			size_t										granularity;
			size_t										reserve;
			size_t										threshold;
			size_t										limit;
			uint32_t									heapID;
			size_t										arena;
		};
		static_assert(sizeof(HeapDesc) == 0x40);
	public:
		virtual ~GMemoryHeap();
		virtual void         CreateArena(size_t, GSysAllocPaged*) = 0;
		virtual void         DestroyArena(size_t) = 0;
		virtual bool         ArenaIsEmpty(size_t) = 0;
		virtual GMemoryHeap* CreateHeap(const char*, const HeapDesc&) = 0;
		virtual void         SetLimitHandler(void*) = 0;
		virtual void         SetLimit(size_t) = 0; 
		virtual void         AddRef() = 0;
		virtual void         Release() = 0;
		virtual void*        Alloc(size_t ) = 0;
		virtual void*        Alloc(size_t, size_t) = 0;
		virtual void*        Realloc(void*, size_t) = 0;
		virtual void         Free(void*) = 0;
		virtual void*        AllocAutoHeap(const void*, size_t) = 0;
		virtual void*        AllocAutoHeap(const void*, size_t, size_t) = 0;
		virtual GMemoryHeap* GetAllocHeap(const void*) = 0;
		virtual size_t       GetUsableSize(const void*) = 0;
		virtual void*        AllocSysDirect(size_t ) = 0;
		virtual void         FreeSysDirect(void* , size_t ) = 0;
		virtual bool         GetStats(GStatBag* a_bag) = 0;
		virtual size_t       GetFootprint()  = 0;
		virtual size_t       GetTotalFootprint()  = 0;
		virtual size_t       GetUsedSpace()  = 0;
		virtual size_t       GetTotalUsedSpace()  = 0;
		virtual void         GetRootStats(void*) = 0;
		virtual void         VisitMem(void*, uint32_t) = 0;
		virtual void         VisitRootSegments(void*) = 0;
		virtual void         VisitHeapSegments(void*) = 0;
		virtual void         SetTracer(void*) = 0;
		virtual void		 DestroyItself() = 0;
		virtual void		 UltimateCheck_Internal() = 0;
		virtual void		 ReleaseCachedMem() = 0;
		virtual bool		 DumpMemoryLeaks_Internal() = 0;
		virtual void		 CheckIntegrity_Internal() = 0;
		virtual void		 GetUserDebugStats(void*) = 0;
	public:
		GMemoryHeap* CreateHeap(const char* a_name, uint32_t a_flags = 0, size_t a_minAlign = 16, size_t a_granularity = 16 * 1024, size_t a_reserve = 16 * 1024, size_t a_threshold = SIZE_MAX, size_t a_limit = 0, size_t a_heapID = 0, size_t a_arena = 0)
		{
			const HeapDesc heap(a_flags, a_minAlign, a_granularity, a_reserve, a_threshold, a_limit, a_heapID, a_arena);

			return CreateHeap(a_name, heap);
		}
	public:
		size_t			  m_size;
		volatile uint32_t m_refCount;
	};
}