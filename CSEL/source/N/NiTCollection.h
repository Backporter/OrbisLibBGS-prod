#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

namespace ConsoleRE
{
	void*          NiMalloc(size_t a_sizeInBytes);
	void*          NiAlignedMalloc(size_t a_sizeInBytes, size_t a_alignment);
	void*          NiRealloc(void* a_mem, size_t a_sizeInBytes);
	void*          NiAlignedRealloc(void* a_mem, size_t a_sizeInBytes, size_t a_alignment);
	void           NiFree(void* a_mem);
	void           NiAlignedFree(void* a_mem);
	constexpr bool NiTrackAlloc(void* a_mem, size_t a_sizeInBytes) { return false; }
	constexpr bool NiTrackFree(void* a_mem) { return false; }

	// calloc
	template <class T>
	T* NiAlloc(size_t a_count)
	{
		return static_cast<T*>(NiMalloc(sizeof(T) * a_count));
	}

	// aligned calloc
	template <class T>
	T* NiAlignedAlloc(size_t a_count, size_t a_alignment)
	{
		return static_cast<T*>(NiAlignedMalloc(sizeof(T) * a_count, a_alignment));
	}

	template <class T>
	class NiTMallocInterface
	{
	public:
		inline static T* Allocate(size_t a_numElements)
		{
			return static_cast<T*>(NiMalloc(sizeof(T) * a_numElements));
		};

		inline static void Deallocate(T* a_array)
		{
			NiFree(a_array);
		};
	};

	template <class T>
	class NiTNewInterface
	{
	public:
		inline static T* Allocate(size_t a_numElements)
		{
			auto mem = malloc(sizeof(size_t) + sizeof(T) * a_numElements);
			auto head = static_cast<size_t*>(mem);
			*head = a_numElements;
			mem = head + 1;
			return static_cast<T*>(mem);
		};

		inline static void Deallocate(T* a_array)
		{
			if (a_array)
			{
				auto head = (size_t*)((uintptr_t)a_array - sizeof(size_t));
				for (size_t i = 0; i < *head; ++i) 
				{
					a_array[i].~T();
				}

				free(head);
			}
		};
	};
}