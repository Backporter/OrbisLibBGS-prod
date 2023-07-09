#include "../../../OrbisUtil/include/Relocation.h"

#include "../N/NiMemManager.h"

namespace ConsoleRE
{
	NiMemManager* NiMemManager::GetSingleton()
	{
		Relocation<NiMemManager**> singleton("", 0x373BD00);
		return *singleton;
	}

	void* NiMemManager::Allocate(size_t a_sizeInBytes, size_t a_alignment, NiMemEventType a_eventType, bool a_provideAccurateSizeOnDeallocate, const char* a_sourceFile, int32_t a_sourceLine, const char* a_function)
	{
		assert(allocator != nullptr);
		auto mem = allocator->Allocate(a_sizeInBytes, a_alignment, a_eventType, a_provideAccurateSizeOnDeallocate, a_sourceFile, a_sourceLine, a_function);
		assert(mem != nullptr);
		return mem;
	}
	
	void NiMemManager::Deallocate(void* a_mem, NiMemEventType a_eventType, size_t a_sizeinBytes)
	{
		assert(allocator);
		allocator->Deallocate(a_mem, a_eventType, a_sizeinBytes);
	}

	void* NiMemManager::Reallocate(void* a_mem, size_t a_sizeInBytes, size_t a_alignment, NiMemEventType a_eventType, bool a_provideAccurateSizeOnDeallocate, size_t a_sizeCurrent, const char* a_sourceFile, int32_t a_sourceLine, const char* a_function)
	{
		assert(allocator != nullptr);
		auto mem = allocator->Reallocate(a_mem, a_sizeInBytes, a_alignment, a_eventType, a_provideAccurateSizeOnDeallocate, a_sizeCurrent, a_sourceFile, a_sourceLine, a_function);
		assert(mem != nullptr);
		return mem;
	}

	bool NiMemManager::TrackAllocate(const void* const a_mem, size_t a_sizeInBytes, NiMemEventType a_eventType, const char* a_sourceFile, int32_t a_sourceLine, const char* a_function)
	{
		assert(allocator);
		return allocator->TrackAllocate(a_mem, a_sizeInBytes, a_eventType, a_sourceFile, a_sourceLine, a_function);
	}

	bool NiMemManager::TrackDeallocate(const void* const a_mem, NiMemEventType a_eventType)
	{
		assert(allocator);
		return allocator->TrackDeallocate(a_mem, a_eventType);
	}
}