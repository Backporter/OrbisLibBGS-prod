#pragma once

#include "../../../OrbisUtil/include/type_traits.h"

#include <type_traits>

#include <assert.h>

namespace ConsoleRE
{
	template <class T>
	struct BSTSmartPointerIntrusiveRefCount
	{
	public:
		static void A(T* T1)
		{
			T1->IncRef();
		}

		static void R(T* T1)
		{
			if (T1->DecRef() == 0)
				delete T1;
		}
	};

	template <class T>
	struct BSTSmartPointerAutoPtr
	{
	public:
		static void A(T* T1)
		{
			return;
		}

		static void R(T* T1)
		{
			delete T1;
		}
	};

	template <class T, template <class> class RefManager = BSTSmartPointerIntrusiveRefCount>
	class BSTSmartPointer
	{
	public:
		constexpr BSTSmartPointer() noexcept : 
			T1(nullptr)
		{}

		constexpr BSTSmartPointer(std::nullptr_t) noexcept : 
			T1(nullptr) 
		{}

		template <class Y, std::enable_if_t<std::is_convertible_v<Y*, T*>, int> = 0>
		BSTSmartPointer(Y* a_ptr) : T1(a_ptr)
		{
			TryAttach();
		}

		BSTSmartPointer(const BSTSmartPointer& rhs) : T1(rhs.T1)
		{
			TryAttach();
		}

		template <class Y, std::enable_if_t<std::is_convertible_v<Y*, T*>, int> = 0>
		BSTSmartPointer(const BSTSmartPointer<Y>& a_rhs) : T1(a_rhs.T1)
		{
			TryAttach();
		}

		BSTSmartPointer(BSTSmartPointer&& a_rhs) noexcept : T1(std::move(a_rhs.T1))
		{
			a_rhs.T1 = nullptr;
		}

		template <class Y, std::enable_if_t<std::is_convertible_v<Y*, T*>, int> = 0>
		BSTSmartPointer(BSTSmartPointer<Y>&& a_rhs) noexcept : T1(std::move(a_rhs.T1))
		{
			a_rhs.T1 = nullptr;
		}

		~BSTSmartPointer()
		{
			TryDetach();
		}

		BSTSmartPointer& operator=(const BSTSmartPointer& a_rhs)
		{
			if (this != std::addressof(a_rhs))
			{
				TryDetach();
				T1 = a_rhs.T1;
				TryAttach();
			}
			return *this;
		}

		template <class Y, std::enable_if_t<std::is_convertible_v<Y*, T*>, int> = 0>
		BSTSmartPointer& operator=(const BSTSmartPointer<Y>& a_rhs)
		{
			TryDetach();
			T1 = a_rhs.T1;
			TryAttach();
			return *this;
		}

		BSTSmartPointer& operator=(BSTSmartPointer&& a_rhs)
		{
			if (this != std::addressof(a_rhs)) {
				TryDetach();
				T1 = std::move(a_rhs.T1);
				a_rhs.T1 = nullptr;
			}
			return *this;
		}

		template <class Y, std::enable_if_t<std::is_convertible_v<Y*, T*>, int> = 0>
		BSTSmartPointer& operator=(BSTSmartPointer<Y>&& a_rhs)
		{
			TryDetach();
			T1 = std::move(a_rhs.T1);
			a_rhs.T1 = nullptr;
			return *this;
		}

		void reset()
		{
			TryDetach();
		}

		template <class Y, std::enable_if_t<std::is_convertible_v<Y*, T*>, int> = 0>
		void reset(Y* a_ptr)
		{
			if (T1 != a_ptr)
			{
				TryDetach();
				T1 = a_ptr;
				TryAttach();
			}
		}

		constexpr T* get() const noexcept
		{
			return T1;
		}

		explicit constexpr operator bool() const noexcept
		{
			return static_cast<bool>(T1);
		}

		constexpr T& operator*() const noexcept
		{
			assert(static_cast<bool>(*this));
			return *T1;
		}

		constexpr T* operator->() const noexcept
		{
			assert(static_cast<bool>(*this));
			return T1;
		}
	public:
		inline void TryAttach()
		{
			if (T1)
			{
				RefManager<T>::A(T1);
			}
		}

		inline void TryDetach()
		{
			if (T1)
			{
				RefManager<T>::R(T1);
				T1 = nullptr;
			}
		}

	public:
		T* T1;
	};
	static_assert(sizeof(BSTSmartPointer<void*>) == 0x8, "");

	template <class T1, class T2>
	constexpr bool operator==(const BSTSmartPointer<T1>& a_lhs, const BSTSmartPointer<T2>& a_rhs)
	{
		return a_lhs.get() == a_rhs.get();
	}

	template <class T1, class T2>
	constexpr bool operator!=(const BSTSmartPointer<T1>& a_lhs, const BSTSmartPointer<T2>& a_rhs)
	{
		return !(a_lhs == a_rhs);
	}

	template <class T>
	constexpr bool operator==(const BSTSmartPointer<T>& a_lhs, std::nullptr_t) noexcept
	{
		return !a_lhs;
	}

	template <class T>
	constexpr bool operator==(std::nullptr_t, const BSTSmartPointer<T>& a_rhs) noexcept
	{
		return !a_rhs;
	}

	template <class T>
	constexpr bool operator!=(const BSTSmartPointer<T>& a_lhs, std::nullptr_t) noexcept
	{
		return static_cast<bool>(a_lhs);
	}

	template <class T>
	constexpr bool operator!=(std::nullptr_t, const BSTSmartPointer<T>& a_rhs) noexcept
	{
		return static_cast<bool>(a_rhs);
	}

	template <typename T>
	using BSTAutoPointer = BSTSmartPointer<T, BSTSmartPointerAutoPtr>;
}