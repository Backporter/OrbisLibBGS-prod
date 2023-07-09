#pragma once

#include "../H/hkMemoryAllocator.h"
#include "../I/IMemoryHeap.h"

namespace ConsoleRE
{
	class bhkThreadMemorySource : public hkMemoryAllocator, public IMemoryHeap
	{
	public:
		struct FreeBlock
		{
		public:
			FreeBlock* next;
		};
		static_assert(sizeof(FreeBlock) == 0x8);

		struct BlockPage
		{
		public:
			BlockPage*    left;
			BlockPage*    right;
			FreeBlock*    blocks;
			uint16_t	  totalElem;
			uint16_t	  freeElem;
			uint32_t	  pad1C;
		};
		static_assert(sizeof(BlockPage) == 0x20);

		struct Row
		{
		public:
			BlockPage*   pageList;
			BlockPage*   currAlloc;
			int32_t		 totalFreeBlocks;
			int32_t		 totalAllocatedBlocks;
			int32_t		 totalBytes;
			int32_t		 elemSize;
		};
		static_assert(sizeof(Row) == 0x20);

		struct MegaBlockPage
		{
		public:
			char           mem[sizeof(BlockPage[255]) * 256];
			BlockPage      blockPages[255];
			MegaBlockPage* left;
			MegaBlockPage* right;
			BlockPage*     freeBlockPages;
			uint16_t	   numFreeBlockPages;
			uint16_t	   nextBlockPageAlloc;
			bool           decommitted;
			uint8_t		   pad1FFFFD;
			uint16_t	   pad1FFFFE;
		};
		static_assert(sizeof(MegaBlockPage) == 0x200000);
	public:
		~bhkThreadMemorySource() override;

		// override (hkMemoryAllocator)
		void*        BlockAlloc(int32_t a_numBytes) override;
		void         BlockFree(void* a_ptr, int32_t a_numBytes) override;
		void*        BufAlloc(int32_t& a_reqNumBytesInOut) override;
		void         BufFree(void* a_ptr, int32_t a_numBytes) override;
		void*        BufRealloc(void* a_ptrOld, int32_t a_oldNumBytes, int32_t& a_reqNumBytesInOut) override;
		void         BlockAllocBatch(void** a_ptrsOut, int32_t a_numPtrs, int32_t a_blockSize) override;
		void         BlockFreeBatch(void** a_ptrsIn, int32_t a_numPtrs, int32_t a_blockSize) override;
		void         GetMemoryStatistics(MemoryStatistics& a_usage) override;
		int32_t		 GetAllocatedSize(const void* a_obj, int32_t a_numBytes) override;

		// override (IMemoryHeap)
		size_t		Size(const void* a_block) const override;
		void        GetMemoryStats(MemoryStats* a_stats) override;
		const char* GetName() const override;
		void*       Allocate(size_t a_size, uint32_t a_alignment) override;
		void        Deallocate(void* a_pointer, uint32_t) override;
		bool        PointerInHeap(const void* a_pointer) const override;
		size_t		TotalSize(const void* a_pointer) const override;
		void        GetHeapStats(HeapStats* a_stats, bool a_fullBlockInfo) override;
		bool        ShouldTrySmallBlockPools(size_t a_size, MEM_CONTEXT a_context) override;
		uint32_t	GetPageSize() const override;
	public:
		BSCriticalSection	lock;
		Row*				rows;
		uint16_t*			smallRowIndexes;
		uint16_t*			largeRowIndexes;
		HeapBlock**			lists;
		HeapBlockFreeHead*	largeFreeTrees;
		HeapBlock*			firstBlock;
		HeapBlock*			lastBlock;
		void*				memoryRoot;
		char*				allocBase;
		char*				blockStart;
		char*				allocEnd;
		char*				commitEnd;
		char*				blockPageCommit;
		char*				addressSpaceEnd;
		MegaBlockPage*		megaBlockPageList;
		MegaBlockPage*		currMegaBlockPageAlloc;
		int32_t				addressSpaceSize;
		int32_t				totalFreeBlockPages;
		uint32_t			usedRows;
		int32_t				totalAllocated;
		int32_t				totalFreeBlocks;
		int32_t				totalBlocks;
		bool				allowDecommits;
		uint8_t				padD1;
		uint16_t			padD2;
	};
	static_assert(sizeof(bhkThreadMemorySource) == 0xB8);
}