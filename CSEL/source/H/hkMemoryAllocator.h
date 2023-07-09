#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class hkMemoryAllocator
	{
	public:
		using MemoryWalkCallback = void(void* a_start, size_t a_size, bool a_allocated, int32_t a_pool, void* a_param);

		enum class MemoryState
		{
			kOK,
			kOutOfMemory
		};

		struct MemoryStatistics
		{
		public:
			static constexpr int64_t INFINITE_SIZE = -1;
		public:
			int64_t allocated;
			int64_t inUse;
			int64_t peakInUse;
			int64_t available;
			int64_t totalAvailable;
			int64_t largestBlock;
		};
		static_assert(sizeof(MemoryStatistics) == 0x30);

		struct ExtendedInterface
		{
		public:
			virtual ~ExtendedInterface();

			// add
			virtual void						GarbageCollect() = 0;
			virtual void						IncrementalGarbageCollect(int32_t a_numBlocks) = 0;
			virtual uint32_t					SetMemorySoftLimit(size_t a_maxMemory) = 0;
			virtual size_t						GetMemorySoftLimit() const = 0;
			virtual bool						CanAllocTotal(int32_t a_numBytes) = 0;
			virtual uint32_t					WalkMemory(MemoryWalkCallback* a_callback, void* a_param) = 0;
		};
		static_assert(sizeof(ExtendedInterface) == 0x8);
	public:
		virtual ~hkMemoryAllocator();

		// add
		virtual void*        BlockAlloc(int32_t a_numBytes) = 0;
		virtual void         BlockFree(void* a_ptr, int32_t a_numBytes) = 0;
		virtual void*        BufAlloc(int32_t& a_reqNumBytesInOut);
		virtual void         BufFree(void* a_ptr, int32_t a_numBytes);
		virtual void*        BufRealloc(void* a_ptrOld, int32_t a_oldNumBytes, int32_t& a_reqNumBytesInOut);
		virtual void         BlockAllocBatch(void** a_ptrsOut, int32_t a_numPtrs, int32_t a_blockSize);
		virtual void         BlockFreeBatch(void** a_ptrsIn, int32_t a_numPtrs, int32_t a_blockSize);
		virtual void         GetMemoryStatistics(MemoryStatistics& a_usage) = 0;
		virtual int32_t		 GetAllocatedSize(const void* a_obj, int32_t a_numBytes) = 0;
		virtual void         ResetPeakMemoryStatistics();
	};
}