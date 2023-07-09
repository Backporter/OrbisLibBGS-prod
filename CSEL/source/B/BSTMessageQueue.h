#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class ScrapHeap;

	template <class T>
	class BSTMessageQueue
	{
	public:
		virtual ~BSTMessageQueue();
		
		// add (BSTMessageQueue)
		virtual bool Unk_02(T*) = 0;
		virtual bool Unk_03(T*) = 0;
		virtual bool Unk_04(T*) = 0;
		virtual bool Unk_05(T*) = 0;
	};
	static_assert(sizeof(BSTMessageQueue<void*>) == 0x8);

	template <class T>
	class BSTCommonMessageQueue : public BSTMessageQueue<T>
	{
		virtual ~BSTCommonMessageQueue();

		// override (BSTMessageQueue<T>)
		bool Unk_02(T*) override;
		bool Unk_03(T*) override;
		bool Unk_04(T*) override;
		bool Unk_05(T*) override;

		// add (BSTCommonMessageQueue)
		virtual bool Unk_06(T*);
		virtual bool Unk_07(T*);
	public:
		uint32_t lock;
	};
	static_assert(sizeof(BSTCommonMessageQueue<void*>) == 0x10);

	template <class T>
	class BSTCommonScrapHeapMessageQueue : public BSTCommonMessageQueue<T>
	{
	public:
		~BSTCommonScrapHeapMessageQueue();
	public:
		ScrapHeap*    unk10;
		uint64_t	  unk18;
		uint64_t	  unk20;
	};
	static_assert(sizeof(BSTCommonScrapHeapMessageQueue<void*>) == 0x28);

	template <typename T>
	class BSTCommonLLMessageQueue : public BSTCommonMessageQueue<T>
	{
	public:
		virtual ~BSTCommonLLMessageQueue();

		// override (BSTCommonMessageQueue)
		bool Unk_06(T*) override;
		bool Unk_07(T*) override;
	public:
		void* Unk10;
		void* Unk18;
		void* Unk20;
	};
	static_assert(sizeof(BSTCommonLLMessageQueue<void*>) == 0x28);

	template <class T, size_t N>
	class BSTCommonStaticMessageQueue : public BSTCommonMessageQueue<T>
	{
	public:
		virtual ~BSTCommonStaticMessageQueue();

		// override (BSTCommonMessageQueue)
		bool Unk_06(T*) override;
		bool Unk_07(T*) override;
	public:
		char	 Unk10[sizeof(T) * N];
		uint32_t numEntries;
		uint32_t pushIdx;
		uint32_t popIdx;
	};
}