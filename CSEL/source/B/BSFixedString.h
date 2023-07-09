#pragma once

#include "../../../OrbisUtil/include/Types.h"
#include "../../../OrbisUtil/include/Macro.h"
#include "../../../OrbisUtil/include/Relocation.h"

#include "../B/BSStringPool.h"
#include "../C/CRC.h"

#include <string>
#include <type_traits>

namespace ConsoleRE
{
	namespace detail
	{
		template <typename CharT>
		class BSFixedString
		{
		public:
			inline static constexpr const CharT EMPTY[]{ 0 };
		public:
			constexpr BSFixedString() noexcept = default;

			inline BSFixedString(const BSFixedString& a_rhs)
			{
				if (a_rhs.m_data)
				{
					//
					const_cast<BSFixedString&>(a_rhs).try_acquire();
				}

				m_data = a_rhs.m_data;
			}

			inline BSFixedString(BSFixedString&& a_rhs) :
				m_data(a_rhs.m_data)
			{
				a_rhs.m_data = nullptr;
			}

			inline BSFixedString(const CharT* a_string)
			{
				if (a_string)
				{
					ctor(a_string);
				}
			}

			inline ~BSFixedString() { try_release(); }

			inline BSFixedString& operator=(const BSFixedString& a_rhs)
			{
				if (this != std::addressof(a_rhs))
				{
					try_release();
					m_data = a_rhs.m_data;
					try_acquire();
				}

				return *this;
			}

			inline BSFixedString& operator=(BSFixedString&& a_rhs)
			{
				if (this != std::addressof(a_rhs))
				{
					try_release();
					m_data = a_rhs.m_data;
					a_rhs.m_data = nullptr;
				}

				return *this;
			}

			inline BSFixedString& operator=(const CharT* a_string)
			{
				try_release();

				if (a_string)
				{
					ctor(a_string);
				}

				return *this;
			}
		public:
			const CharT* data()	const noexcept 
			{ 
				const auto proxy = get_proxy();
				const auto cstr = proxy ? proxy->template data<CharT>() : nullptr;
				return cstr ? cstr : EMPTY;

				// return m_data ? m_data : EMPTY; 
			}

			const CharT* c_str() const noexcept 
			{ 
				return data(); 
			}

			constexpr bool empty() const noexcept { return size() == 0; }

			constexpr uint32_t size() const noexcept
			{
				const auto proxy = get_proxy();
				return proxy ? proxy->size() : 0;
			}

			operator const CharT*() const { return data(); }
			operator std::basic_string<CharT>() { return m_data; }

			bool operator==(const BSFixedString& lhs) const { return m_data == lhs.m_data; }
		private:
			inline void ctor(const char* a_str) { ctor8(a_str); }
			inline void ctor(const wchar_t_t* a_wstr) { ctor16(a_wstr); }

			inline void ctor8(const char* data)
			{
				using func_t = decltype(&BSFixedString::ctor8);
				Relocation<func_t> func("", 0xE4E9B0);
				return func(this, data);
			}

			inline void ctor16(const wchar_t_t* a_data)
			{
				using func_t = decltype(&BSFixedString::ctor16);
				Relocation<func_t> func("", 0xE4FDB0);
				return func(this, a_data);
			}

			// ...
			inline BSStringPool::Entry* get_proxy() noexcept
			{
				return m_data ? reinterpret_cast<BSStringPool::Entry*>(const_cast<CharT*>(m_data)) - 1 : nullptr;
			}

			// ...
			inline const BSStringPool::Entry* get_proxy() const noexcept
			{
				return m_data ? reinterpret_cast<const BSStringPool::Entry*>(m_data) - 1 : nullptr;
			}

			// ...
			inline void try_acquire()
			{
				auto proxy = get_proxy();
				if (proxy)
				{
					proxy->acquire();
				}
			}

			// ...
			inline void try_release() { BSStringPool::Entry::release(m_data); }
		public:
			const CharT* m_data { nullptr };
		};
	
		extern template class BSFixedString<char>;
		extern template class BSFixedString<wchar_t_t>;
	}

	using BSFixedString = detail::BSFixedString<char>;
	using BSFixedStringCI = BSFixedString;
	using BSFixedStringW = detail::BSFixedString<wchar_t_t>;

	template <class CharT>
	struct BSCRC32_<detail::BSFixedString<CharT>>
	{
	public:
		inline uint32_t operator()(const detail::BSFixedString<CharT>& a_key) const noexcept
		{
			return BSCRC32_<const void*>()(a_key.data());
		}
	};
}