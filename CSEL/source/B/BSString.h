#pragma once

#include <stdint.h>
#include <string>

namespace ConsoleRE
{
	template <class T, uint32_t N>
	class DynamicMemoryManagementPol
	{
	public:
		T* allocate(uint32_t a_num)
		{
			if (a_num > N) 
			{
				return 0;
			}

			auto size = a_num * sizeof(T);
			auto mem = (T*)malloc(size);
			memset(mem, 0, size);
			return mem;
		}

		void deallocate(T* a_ptr) 
		{ 
			free(a_ptr); 
		}
	};

	template <class CharT, uint32_t N, template <class, uint32_t> class _Allocator>
	class BSStringT
	{
	public:
		static constexpr auto MAX = static_cast<uint16_t>(N);
		inline static constexpr CharT EMPTY[]{ 0 };
		using Allocator = _Allocator<CharT, N>;
		using type_traits = std::char_traits<CharT>;
	public:
		BSStringT() { ctor(EMPTY); }
		BSStringT(const CharT* a_rhs) { ctor(a_rhs); }
		BSStringT(const std::basic_string<CharT>& a_rhs) { ctor(a_rhs.data(), a_rhs.size()); }
		~BSStringT()
		{
			deallocate(m_data);
			m_data = nullptr;
		}

		CharT* data() noexcept { return m_data ? m_data : EMPTY; }
		const CharT* data() const noexcept { return m_data ? m_data :EMPTY; }
		const CharT* c_str() const noexcept { return data(); }
		operator std::basic_string<CharT>() const noexcept { std::basic_string<CharT>(data(), size()); }
		uint16_t size() const noexcept { return m_size != MAX ? m_size : static_cast<uint16_t>(type_traits::length(data())); }
		uint16_t length() const noexcept { return size(); }
	private:	
		CharT* allocate(uint32_t a_len)
		{
			return Allocator::allocate(a_len);
		}
		
		void deallocate(CharT* a_ptr)
		{
			return Allocator::deallocate(a_ptr);
		}

		bool ctor(const CharT* a_str, uint32_t a_len = 0)
		{
			auto len = static_cast<uint16_t>(a_len);
			if (m_data == a_str) 
			{
				return true;
			}

			if (len == 0) 
			{
				len = static_cast<uint16_t>(type_traits::length(a_str));
			}

			const uint16_t newSize = len > MAX ? MAX : len;
			++len;
			const uint16_t newCap = len > MAX ? MAX : len;

			if (len <= m_capacity) 
			{
				type_traits::copy(m_data, a_str, len);
				m_size = newSize;
				return true;
			}

			const auto newData = allocate(len);
			if (!newData) 
			{
				return false;
			}

			type_traits::copy(newData, a_str, len);
			if (m_data)
			{
				deallocate(m_data);
			}

			m_data = newData;
			m_size = newSize;
			m_capacity = newCap;
			return true;
		}
	private:
		CharT*		m_data;
		uint16_t	m_size;
		uint16_t	m_capacity;
		uint32_t	pad;
	};

	using BSString = BSStringT<char, static_cast<uint32_t>(-1), DynamicMemoryManagementPol>;
	static_assert(sizeof(BSString) == 0x10);
}