#pragma once
#include <stdint.h>

namespace ConsoleRE
{
	// ?
	template <class T>
	struct BSTFreeListElem
	{
		char                elem[sizeof(T)];  // 00
		BSTFreeListElem<T>* next;             // ??
	};

	template <typename T>
	class BSTFreeList
	{
	public:
		virtual ~BSTFreeList();
	public:
		uint32_t			lock;
		uint32_t			pad0C;
		BSTFreeListElem<T>* free;
	};

	template <typename T, size_t N>
	class BSTStaticFreeList : public BSTFreeList<T>
	{
	public:
		virtual ~BSTStaticFreeList();
	public:
		BSTFreeListElem<T> elems[N];
	};
}