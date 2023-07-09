#pragma once
#include "../../../OrbisUtil/include//Relocation.h"

#include "../G/GMemoryHeap.h"

namespace ConsoleRE
{
	class GMemoryHeapPT : public GMemoryHeap
	{
	public:
		~GMemoryHeapPT() override;

		void         CreateArena(size_t, GSysAllocPaged*) override;
		void         DestroyArena(size_t) override;
		bool         ArenaIsEmpty(size_t) override;
		GMemoryHeap* CreateHeap(const char*, const HeapDesc&) override;
		void         SetLimitHandler(void*) override;
		void         SetLimit(size_t) override;
		void         AddRef() override;
		void         Release() override;
		void*        Alloc(size_t) override;
		void*        Alloc(size_t, size_t) override;
		void*        Realloc(void*, size_t) override;
		void         Free(void*) override;
		void*        AllocAutoHeap(const void*, size_t) override;
		void*        AllocAutoHeap(const void*, size_t, size_t) override;
		GMemoryHeap* GetAllocHeap(const void*) override;
		size_t       GetUsableSize(const void*) override;
		void*        AllocSysDirect(size_t) override;
		void         FreeSysDirect(void*, size_t) override;
		bool         GetStats(GStatBag* a_bag) override;
		size_t       GetFootprint() override;
		size_t       GetTotalFootprint() override;
		size_t       GetUsedSpace() override;
		size_t       GetTotalUsedSpace() override;
		void         GetRootStats(void*) override;
		void         VisitMem(void*, uint32_t) override;
		void         VisitRootSegments(void*) override;
		void         VisitHeapSegments(void*) override;
		void         SetTracer(void*) override;
		void		 DestroyItself() override;
		void		 UltimateCheck_Internal() override;
		void		 ReleaseCachedMem() override;
		bool		 DumpMemoryLeaks_Internal() override;
		void		 CheckIntegrity_Internal() override;
		void		 GetUserDebugStats(void*) override;
	public:
	};
}