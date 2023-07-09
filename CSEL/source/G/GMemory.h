#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include "../G/GMemoryHeap.h"

#include <stdint.h>

namespace ConsoleRE
{
	class GMemory
	{
	public:
		static void         SetGlobalHeap(GMemoryHeap* a_heap)
		{
			GetGlobalHeapRef() = a_heap;
		}

		static GMemoryHeap* GetGlobalHeap()
		{
			return GetGlobalHeapRef();
		}

		static void         CreateArena(size_t a_arena, GSysAllocPaged* a_sysAlloc)
		{
			GetGlobalHeapRef()->CreateArena(a_arena, a_sysAlloc);
		}

		static void         DestroyArena(size_t a_arena)
		{
			GetGlobalHeapRef()->DestroyArena(a_arena);
		}

		static bool         ArenaIsEmpty(size_t a_arena)
		{
			return GetGlobalHeapRef()->ArenaIsEmpty(a_arena);
		}

		static void*        Alloc(size_t a_count)
		{
			return GetGlobalHeapRef()->Alloc(a_count);
		}
		
		static void*        Alloc(size_t a_count, size_t a_al)
		{
			return GetGlobalHeapRef()->Alloc(a_count, a_al);
		}

		static void*        AllocAutoHeap(const void* a_ptr, size_t a_count)
		{
			return GetGlobalHeapRef()->AllocAutoHeap(a_ptr, a_count);
		}

		static void*        AllocAutoHeap(const void* a_ptr, size_t a_count, size_t a_al)
		{
			return GetGlobalHeapRef()->AllocAutoHeap(a_ptr, a_count, a_al);
		}

		static void*        AllocInHeap(GMemoryHeap* a_heap, size_t a_count)
		{
			assert(a_heap);
			return a_heap->Alloc(a_count);
		}

		static void*        AllocInHeap(GMemoryHeap* a_heap, size_t a_count, size_t a_al)
		{
			assert(a_heap);
			return a_heap->Alloc(a_count, a_al);
		}

		static void*        Realloc(void* a_ptr, size_t a_newCount)
		{
			return GetGlobalHeapRef()->Realloc(a_ptr, a_newCount);
		}

		static void         Free(void* a_ptr)
		{
			if (a_ptr) 
			{
				return GetGlobalHeapRef()->Free(a_ptr);
			}
		}

		static void         FreeInHeap(GMemoryHeap* a_heap, void* a_ptr)
		{
			assert(a_heap);
			if (a_ptr) 
			{
				a_heap->Free(a_ptr);
			}
		}

		static GMemoryHeap* GetHeapByAddress(const void* a_ptr)
		{
			return GetGlobalHeapRef()->GetAllocHeap(a_ptr);
		}
		
		static bool         DetectMemoryLeaks()
		{
			return GetGlobalHeapRef()->DumpMemoryLeaks_Internal();
		}

	protected:
		static GMemoryHeap*& GetGlobalHeapRef()
		{
			Relocation<GMemoryHeap**> globalHeap("", 0x37EA730);
			return *globalHeap;
		}
	};
}

// Global heap
#define GALLOC(a_count)				ConsoleRE::GMemory::Alloc((a_count))
#define GMEMALIGN(a_sz, a_al)		ConsoleRE::GMemory::Alloc((a_count), (a_al))
#define GREALLOC(a_ptr, a_count)	ConsoleRE::GMemory::Realloc((a_ptr), (a_count))
#define GFREE(a_ptr)				ConsoleRE::GMemory::Free((a_ptr))
#define GFREE_ALIGN(a_count)		ConsoleRE::GMemory::Free((a_count))

// Local heap
#define GHEAP_ALLOC(a_heap, a_count)			ConsoleRE::GMemory::AllocInHeap((a_heap), (a_count))
#define GHEAP_MEMALIGN(a_heap, a_count, a_al)	ConsoleRE::GMemory::AllocInHeap((a_heap), (a_count), (a_al))
#define GHEAP_AUTO_ALLOC(a_addr, a_count)		ConsoleRE::GMemory::AllocAutoHeap((a_addr), (a_count))
#define GHEAP_FREE(a_heap, a_ptr)				ConsoleRE::GMemory::FreeInHeap((a_heap), (a_ptr))

#define GFC_MEMORY_REDEFINE_NEW_IMPL(a_className, a_check_delete, a_statType)                                   \
	void* operator new(size_t a_count) { return GALLOC(a_count); }                                         \
	void* operator new[](size_t a_count) { return GALLOC(a_count); }                                       \
	void* operator new(size_t a_count, void* a_plcmnt) { return a_plcmnt; }               \
	void* operator new[](size_t a_count, void* a_plcmnt) { return a_plcmnt; }             \
	void* operator new(size_t a_count, ConsoleRE::GMemoryHeap* a_heap) { return GHEAP_ALLOC(a_heap, a_count); }   \
	void* operator new[](size_t a_count, ConsoleRE::GMemoryHeap* a_heap) { return GHEAP_ALLOC(a_heap, a_count); } \
	void  operator delete(void* a_ptr) { GFREE(a_ptr); }                                                        \
	void  operator delete[](void* a_ptr) { GFREE(a_ptr); }                                                      \
	void  operator delete( void* a_ptr,  void* a_plcmnt) {}                     \
	void  operator delete[]( void* a_ptr,  void* a_plcmnt) {}                   \
	void  operator delete(void* a_ptr, ConsoleRE::GMemoryHeap* a_heap) { GHEAP_FREE(a_heap, a_ptr); }

#define GFC_MEMORY_CHECK_DELETE_NONE(a_className, a_ptr)
#define GFC_MEMORY_REDEFINE_NEW(a_className, a_statType) GFC_MEMORY_REDEFINE_NEW_IMPL(a_className, GFC_MEMORY_CHECK_DELETE_NONE, a_statType)