#pragma once

#include "../../../OrbisUtil/include/type_traits.h"

namespace ConsoleRE
{
	template <typename T>
	class GPtr
	{
	public:
		inline constexpr GPtr() noexcept : 
			T1(nullptr)
		{}

		inline constexpr GPtr(std::nullptr_t) noexcept :
			T1(nullptr)
		{}
		
		template <class Y, std::enable_if_t<std::is_convertible_v<Y*,T*>,int> = 0>
		GPtr(Y* a_rhs) : T1(a_rhs)
		{ 
			TryAttach();
		}
		
		GPtr(const GPtr& a_rhs) : T1(a_rhs.T1)
		{
			TryAttach();
		}


		template <class Y, std::enable_if_t<std::is_convertible_v<Y*,T*>,int> = 0>
		GPtr(const GPtr<Y>& a_rhs) : T1(a_rhs.T1)
		{
			TryAttach();
		}

		GPtr(GPtr&& a_rhs) noexcept : T1(std::move(a_rhs.T1))
		{
			a_rhs.T1 = nullptr;
		}

		template <class Y, std::enable_if_t<std::is_convertible_v<Y*, T*>, int> = 0> 
		GPtr(GPtr<Y>&& a_rhs) noexcept : T1(std::move(a_rhs.T1))
		{
			a_rhs.T1 = nullptr;
		}

		~GPtr()
		{
			TryDetach();
		}

		GPtr& operator=(const GPtr& a_rhs)
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
		GPtr& operator=(const GPtr<Y>& a_rhs)
		{
			TryDetach();
			T1 = a_rhs.T1;
			TryAttach();

			return *this;
		}

		GPtr& operator=(GPtr&& a_rhs)
		{
			if (this != std::addressof(a_rhs)) 
			{
				TryDetach();
				T1 = std::move(a_rhs.T1);
				a_rhs.T1 = nullptr;
			}

			return *this;
		}

		template <class Y, std::enable_if_t<std::is_convertible_v<Y*, T*>, int> = 0>
		GPtr& operator=(GPtr<Y>&& a_rhs)
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
	public:
		operator T*() const noexcept
		{
			return T1;
		}

		T* get() const noexcept
		{
			return T1;
		}

		operator bool() const noexcept
		{
			return static_cast<bool>(T1);
		}

		T& operator*() const noexcept
		{
			assert(static_cast<bool>(*this));
			return *T1;
		}

		T* operator->() const noexcept
		{
			assert(static_cast<bool>(*this));
			return T1;
		}
	public:
		void TryAttach()
		{
			if (T1)
			{
				T1->IncremntRef();
			}
		}

		void TryDetach()
		{
			if (T1)
			{
				T1->Release();
				T1 = nullptr;
			}
		}
	public:
		T* T1;
	};

	template <class T, class... Args>
	inline GPtr<T> make_gptr(Args&&... a_args)
	{
		auto ptr = GPtr<T>{ new T(std::forward<Args>(a_args)...) };
		if (ptr) 
		{
			ptr->Release();
		}

		return ptr;
	}

	template <class T1, class T2>
	constexpr bool operator==(const GPtr<T1>& a_lhs, const GPtr<T2>& a_rhs)
	{
		return a_lhs.get() == a_rhs.get();
	}

	template <class T1, class T2>
	constexpr bool operator!=(const GPtr<T1>& a_lhs, const GPtr<T2>& a_rhs)
	{
		return !(a_lhs == a_rhs);
	}

	template <class T>
	constexpr bool operator==(const GPtr<T>& a_lhs, std::nullptr_t) noexcept
	{
		return !a_lhs;
	}

	template <class T>
	constexpr bool operator==(std::nullptr_t, const GPtr<T>& a_rhs) noexcept
	{
		return !a_rhs;
	}

	template <class T>
	constexpr bool operator!=(const GPtr<T>& a_lhs, std::nullptr_t) noexcept
	{
		return static_cast<bool>(a_lhs);
	}

	template <class T>
	constexpr bool operator!=(std::nullptr_t, const GPtr<T>& a_rhs) noexcept
	{
		return static_cast<bool>(a_rhs);
	}
}