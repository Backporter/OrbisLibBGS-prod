#pragma once

#include <stdint.h>
#include <stdio.h>

namespace ConsoleRE
{
	enum class NiMemEventType
	{
		kUnknown = 0,
		kOperNew = 1,
		kOperNewArray = 2,
		kOperDelete = 3,
		kOperDeleteArray = 4,
		kMalloc = 5,
		kRealloc = 6,
		kAlignedMalloc = 7,
		kAlignedRealloc = 8,
		kFree = 9,
		kAlignedFree = 10,
		kExternalAlloc = 11,
		kExternalFree = 12
	};

	class NiAllocator
	{
	public:
		virtual ~NiAllocator();

		// add
		virtual void* Allocate(size_t& a_sizeInBytes, size_t& a_alignment, NiMemEventType a_eventType, bool a_provideAccurateSizeOnDeallocate, const char* a_file, int32_t a_line, const char* a_function) = 0;
		virtual void  Deallocate(void* a_memory, NiMemEventType a_eventType, size_t a_sizeInBytes) = 0;
		virtual void* Reallocate(void* a_memory, size_t& a_sizeInBytes, size_t& a_alignment, NiMemEventType a_eventType, bool a_provideAccurateSizeOnDeallocate, size_t a_sizeCurrent, const char* a_file, int32_t a_line, const char* a_function) = 0;
		virtual bool  TrackAllocate(const void* const a_memory, size_t a_sizeInBytes, NiMemEventType a_eventType, const char* a_file, int32_t a_line, const char* a_function) = 0;
		virtual bool  TrackDeallocate(const void* const a_memory, NiMemEventType a_eventType) = 0;
		virtual void  Unk_06(void) = 0;
		virtual void  Initialize() = 0;
		virtual void  Shutdown() = 0;
		virtual bool  VerifyAddress(const void* a_memory) = 0;
	public:
	};
	static_assert(sizeof(NiAllocator) == 0x8);
}