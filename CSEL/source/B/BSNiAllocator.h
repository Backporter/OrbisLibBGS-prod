#pragma once

#include "../N/NiAllocator.h"

namespace ConsoleRE
{
	class BSNiAllocator : public NiAllocator
	{
	public:
		~BSNiAllocator() override;

		void* Allocate(size_t& a_sizeInBytes, size_t& a_alignment, NiMemEventType a_eventType, bool a_provideAccurateSizeOnDeallocate, const char* a_file, int32_t a_line, const char* a_function) override;
		void  Deallocate(void* a_memory, NiMemEventType a_eventType, size_t a_sizeInBytes) override;
		void* Reallocate(void* a_memory, size_t& a_sizeInBytes, size_t& a_alignment, NiMemEventType a_eventType, bool a_provideAccurateSizeOnDeallocate, size_t a_sizeCurrent, const char* a_file, int32_t a_line, const char* a_function) override;
		bool  TrackAllocate(const void* const a_memory, size_t a_sizeInBytes, NiMemEventType a_eventType, const char* a_file, int32_t a_line, const char* a_function) override;
		bool  TrackDeallocate(const void* const a_memory, NiMemEventType a_eventType) override;
		void  Unk_06(void) override;
		void  Initialize() override;
		void  Shutdown() override;
		bool  VerifyAddress(const void* a_memory) override;
	public:
	};
}