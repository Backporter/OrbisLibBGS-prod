#pragma once

#include "../N/NiAllocator.h"

namespace ConsoleRE
{
	class NiMemManager
	{
	public:
		void* Allocate(size_t a_sizeInBytes, size_t a_alignment, NiMemEventType a_eventType, bool a_provideAccurateSizeOnDeallocate = false, const char* a_sourceFile = nullptr, int32_t a_sourceLine = -1, const char* a_function = nullptr);
		void  Deallocate(void* a_mem, NiMemEventType a_eventType, size_t a_sizeinBytes = static_cast<size_t>(-1));
		void* Reallocate(void* a_mem, size_t a_sizeInBytes, size_t a_alignment, NiMemEventType a_eventType, bool a_provideAccurateSizeOnDeallocate = false, size_t a_sizeCurrent = static_cast<size_t>(-1), const char* a_sourceFile = nullptr, int32_t a_sourceLine = -1, const char* a_function = nullptr);
		bool  TrackAllocate(const void* const a_mem, size_t a_sizeInBytes, NiMemEventType a_eventType, const char* a_sourceFile = nullptr, int32_t a_sourceLine = -1, const char* a_function = nullptr);
		bool  TrackDeallocate(const void* const a_mem, NiMemEventType a_eventType);
		
		static NiMemManager* GetSingleton();
	public:
		NiAllocator* allocator;
	};
	static_assert(sizeof(NiMemManager) == 0x8);
}
