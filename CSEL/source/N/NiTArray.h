#pragma once

#include <stdint.h>
#include <assert.h>

#include "../N/NiTCollection.h"

namespace ConsoleRE
{
	class TESForm;

	template <class T, class Allocator>
	class NiTArray
	{
	public:
		T& operator[](uint16_t a_pos)
		{
			assert(a_pos < size());
			return m_data[a_pos];
		}

		const T& operator[](uint16_t a_pos) const
		{
			assert(a_pos < size());
			return m_data[a_pos];
		}

		T& front() 
		{ 
			return operator[](0); 
		}

		const T& front() const 
		{ 
			return operator[](0); 
		}

		T& back() 
		{ 
			return operator[](size() - 1); 
		}

		const T& back() const
		{ 
			return operator[](size() - 1); 
		}

		T* begin() 
		{ 
			return m_data;
		}

		const T* begin() const 
		{ 
			return m_data; 
		}

		const T* cbegin() const 
		{ 
			return m_data; 
		}

		T* end() 
		{ 
			return m_data + m_size; 
		}

		const T* end() const 
		{ 
			return m_data + m_size; 
		}

		const T* cend() const 
		{ 
			return m_data + m_size; 
		}

		bool empty() const 
		{ 
			return m_capacity == 0; 
		}

		uint16_t size() const 
		{ 
			return m_size;
		}

		uint16_t capacity() const
		{
			return m_capacity; 
		}
	public:
		NiTArray(uint32_t a_capacity = 0, uint32_t a_growthfactor = 1) : m_data(nullptr), m_capacity(a_capacity), m_freeidx(0), m_size(0), m_growthfactor(a_growthfactor)
		{
			if (m_capacity > 0)
				m_data = Allocator::Allocate(m_capacity);
		}
		
		virtual ~NiTArray()
		{
			Allocator::Deallocate(m_data);
		}
	public:
		T*			m_data;
		uint16_t	m_capacity;
		uint16_t	m_freeidx;
		uint16_t	m_size;
		uint16_t	m_growthfactor;
	};

	template <class T>
	class NiTObjectArray : public NiTArray<T, NiTNewInterface<T>>
	{
	public:
		NiTObjectArray(uint32_t a_capacity = 0, uint32_t a_growthfactor = 1) :
			NiTArray<T, NiTNewInterface<T>>(a_capacity, a_growthfactor)
		{
		}
	};
	static_assert(sizeof(NiTObjectArray<void*>) == 0x18, "");

	template <class T>
	class NiTPrimitiveArray : public NiTArray<T, NiTMallocInterface<T>>
	{
	public:
		NiTPrimitiveArray(uint32_t a_capacity = 0, uint32_t a_growthfactor = 1) :
			NiTArray<T, NiTMallocInterface<T>>(a_capacity, a_growthfactor)
		{
		}
	};
	static_assert(sizeof(NiTPrimitiveArray<void*>) == 0x18, "");

	template <class T, class Allocator>
	class NiTLargeArray
	{
	public:
		NiTLargeArray(uint32_t a_capacity = 0, uint32_t a_growthfactor = 1) : 
			m_data(0), m_capacity(a_capacity), m_freeIdx(0), m_size(0), m_growthfactor(a_growthfactor)
		{
			if (m_capacity > 0) 
			{
				m_data = Allocator::Allocate(m_capacity);
			}
		}

		virtual ~NiTLargeArray()
		{
			Allocator::Deallocate(m_data);
		}

		T& operator[](uint32_t a_pos)
		{
			assert(a_pos < size());
			return m_data[a_pos];
		}

		const T& operator[](uint32_t a_pos) const
		{
			assert(a_pos < size());
			return m_data[a_pos];
		}

		T& front()
		{
			return operator[](0);
		}

		const T& front() const
		{
			return operator[](0);
		}

		T& back()
		{
			return operator[](size() - 1);
		}

		const T& back() const
		{
			return operator[](size() - 1);
		}

		T* begin()
		{
			return m_data;
		}

		const T* begin() const
		{
			return m_data;
		}

		const T* cbegin() const
		{
			return m_data;
		}

		T* end()
		{
			return m_data + m_size;
		}

		const T* end() const
		{
			return m_data + m_size;
		}

		const T* cend() const
		{
			return m_data + m_size;
		}

		bool empty() const
		{
			return m_capacity == 0;
		}

		uint32_t size() const
		{
			return m_size;
		}

		uint32_t capacity() const
		{
			return m_capacity;
		}

	public:
		T*            m_data;
		uint32_t	  m_capacity;
		uint32_t	  m_freeIdx;
		uint32_t	  m_size;
		uint32_t	  m_growthfactor;
	};
	static_assert(sizeof(NiTLargeArray<void*, NiTMallocInterface<void*>>) == 0x20, "");

	template <class T>
	class NiTLargeObjectArray : public NiTLargeArray<T, NiTNewInterface<T>>
	{
	public:
		NiTLargeObjectArray(uint32_t a_capacity = 0, uint32_t a_growthfactor = 1) :
			NiTLargeArray<T, NiTNewInterface<T>>(a_capacity, a_growthfactor)
		{}
	};
	static_assert(sizeof(NiTLargeObjectArray<void*>) == 0x20, "");

	template <class T>
	class NiTLargePrimitiveArray : public NiTLargeArray<T, NiTMallocInterface<T>>
	{
	public:
		NiTLargePrimitiveArray(uint32_t a_maxSize = 0, uint32_t m_growthfactor = 1) :
			NiTLargeArray<T, NiTMallocInterface<T>>(a_maxSize, m_growthfactor)
		{
		}
	};
	static_assert(sizeof(NiTLargePrimitiveArray<void*>) == 0x20, "");

	class NiFormArray : public NiTLargePrimitiveArray<TESForm*>
	{
	public:
	};
	static_assert(sizeof(NiFormArray) == 0x20, "");
}