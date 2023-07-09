#pragma once

#include <stdio.h>
#include <cstdio>
#include <assert.h>
#include <stdint.h>

namespace ConsoleRE
{
	template <class T>
	class hkArrayBase
	{
	public:
		using value_type = T;
		using size_type = int32_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = T*;
		using const_iterator = const T*;
	public:
		T& operator[](int32_t a_pos)
		{
			assert(a_pos >= 0 && a_pos < size());
			return data()[a_pos];
		}
		const T& operator[](int32_t a_pos) const
		{
			assert(a_pos >= 0 && a_pos < size());
			return data()[a_pos];
		}

		T* data()
		{
			return m_data;
		}

		const T* data() const
		{
			return m_data;
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
			return empty() ? iterator{} : std::addressof(data()[0]);
		}

		const T* begin() const
		{
			return empty() ? const_iterator{} : std::addressof(data()[0]);
		}


		const T* cbegin() const
		{
			return begin();
		}

		T* end()
		{
			return empty() ? iterator{} : std::addressof(data()[size()]);
		}

		const T* end() const
		{
			return empty() ? const_iterator{} : std::addressof(data()[size()]);
		}

		T* cend() const
		{
			return end();
		}

		bool empty() const
		{
			return size() == 0;
		}

		int32_t size() const noexcept
		{
			return m_size;
		}
	public:
		T*		m_data;
		int32_t	m_size;
		int32_t m_capacity;
	};

	template <typename T, class Allocator = void>
	class hkArray : public hkArrayBase<T>
	{
	public:
	};
	static_assert(sizeof(hkArray<void*>) == 0x10);

	template <class T, size_t N, class Allocator = void>
	class hkInplaceArray : public hkArray<T, Allocator>
	{
	public:
		T storage[N];
	};
}