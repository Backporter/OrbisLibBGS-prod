#pragma once

#include "../../../OrbisUtil/include/type_traits.h"

#include <type_traits>
#include <stddef.h>
#include <assert.h>

namespace ConsoleRE
{
	template <typename T>
	class hkRefPtr
	{
	public:
		inline hkRefPtr& operator=(const hkRefPtr& a_rhs)
		{
			if (this != std::addressof(a_rhs)) 
			{
				TryDetach();
				m_pointer = a_rhs.m_pointer;
				TryAttach();
			}
			return *this;
		}

		template <class Y, std::enable_if_t<std::is_convertible_v<Y*, T*>, int> = 0>
		hkRefPtr& operator=(const hkRefPtr<Y>& a_rhs)
		{
			TryDetach();
			m_pointer = a_rhs.m_pointer;
			TryAttach();
			return *this;
		}

		inline hkRefPtr& operator=(hkRefPtr&& a_rhs)
		{
			if (this != std::addressof(a_rhs)) 
			{
				TryDetach();
				m_pointer = std::move(a_rhs.m_pointer);
				a_rhs.m_pointer = nullptr;
			}
			return *this;
		}

		template <class Y, std::enable_if_t<std::is_convertible_v<Y*, T*>, int> = 0>
		inline hkRefPtr& operator=(hkRefPtr<Y>&& a_rhs)
		{
			TryDetach();
			m_pointer = std::move(a_rhs.m_pointer);
			a_rhs.m_pointer = nullptr;
			return *this;
		}
	public:
		constexpr hkRefPtr() noexcept : m_pointer(nullptr)
		{}

		constexpr hkRefPtr(nullptr_t) noexcept : m_pointer(nullptr)
		{}

		template <class Y, std::enable_if_t<std::is_convertible_v<Y*, T*>, int> = 0>
		explicit hkRefPtr(Y* a_rhs) : m_pointer(a_rhs)
		{
			TryAttach();
		}

		hkRefPtr(const hkRefPtr& a_rhs) : m_pointer(a_rhs.m_pointer)
		{
			TryAttach();
		}

		template <class Y, std::enable_if_t<std::is_convertible_v<Y*, T*>, int> = 0>
		hkRefPtr(const hkRefPtr<Y>& a_rhs) : m_pointer(a_rhs.m_pointer)
		{
			TryAttach();
		}

		hkRefPtr(hkRefPtr&& a_rhs) noexcept : m_pointer(std::move(a_rhs.m_pointer))
		{
			a_rhs.m_pointer = nullptr;
		}

		template <class Y, std::enable_if_t<std::is_convertible_v<Y*, T*>, int> = 0>
		hkRefPtr(hkRefPtr<Y>&& a_rhs) noexcept : m_pointer(std::move(a_rhs.m_pointer))
		{
			a_rhs.m_pointer = nullptr;
		}
		
		~hkRefPtr()
		{
			TryDetach();
		}

		//
		void reset()
		{
			TryDetach();
		}

		template <class Y, std::enable_if_t<std::is_convertible_v<Y*, T*>, int> = 0>
		inline void reset(Y* a_ptr)
		{
			if (m_pointer != a_ptr) 
			{
				TryDetach();
				m_pointer = a_ptr;
				TryAttach();
			}
		}

		constexpr T* get() const noexcept
		{
			return m_pointer;
		}

		explicit constexpr operator bool() const noexcept
		{
			return static_cast<bool>(m_pointer);
		}

		constexpr T& operator*() const noexcept
		{
			assert(static_cast<bool>(*this));
			return *m_pointer;
		}

		constexpr T* operator->() const noexcept
		{
			assert(static_cast<bool>(*this));
			return m_pointer;
		}
	protected:
		void TryAttach()
		{
			if (m_pointer)
			{
				m_pointer->AddReference();
			}
		}

		void TryDetach()
		{
			if (m_pointer)
			{
				m_pointer->RemoveReference();
				m_pointer = nullptr;
			}
		}
	public:
		T* m_pointer;
	};

	template <class T, class... Args>
	inline hkRefPtr<T> make_hkref(Args&&... a_args)
	{
		return hkRefPtr<T>{ new T(std::forward<Args>(a_args)...) };
	}

	template <class T1, class T2>
	constexpr bool operator==(const hkRefPtr<T1>& a_lhs, const hkRefPtr<T2>& a_rhs)
	{
		return a_lhs.get() == a_rhs.get();
	}

	template <class T1, class T2>
	constexpr bool operator!=(const hkRefPtr<T1>& a_lhs, const hkRefPtr<T2>& a_rhs)
	{
		return !(a_lhs == a_rhs);
	}

	template <class T>
	constexpr bool operator==(const hkRefPtr<T>& a_lhs, nullptr_t) noexcept
	{
		return !a_lhs;
	}

	template <class T>
	constexpr bool operator==(nullptr_t, const hkRefPtr<T>& a_rhs) noexcept
	{
		return !a_rhs;
	}

	template <class T>
	constexpr bool operator!=(const hkRefPtr<T>& a_lhs, nullptr_t) noexcept
	{
		return static_cast<bool>(a_lhs);
	}

	template <class T>
	constexpr bool operator!=(nullptr_t, const hkRefPtr<T>& a_rhs) noexcept
	{
		return static_cast<bool>(a_rhs);
	}
}