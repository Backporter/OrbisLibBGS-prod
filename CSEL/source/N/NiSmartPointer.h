#pragma once

#include "../../../OrbisUtil/include/type_traits.h"

#include <assert.h>
#include <stddef.h>

namespace ConsoleRE
{
	template <typename T>
	class NiPointer
	{
	public:
		constexpr NiPointer() noexcept = default;

		constexpr NiPointer(std::nullptr_t) noexcept {}

		template <class Y, std::enable_if_t<std::is_convertible_v<Y*, T*>, int> = 0>
		NiPointer(Y* src) :
			T1(src)
		{
			TryLock();
		}

		NiPointer(NiPointer& rhs) :
			T1(rhs.T1)
		{
			TryLock();
		}

		template <class Y, std::enable_if_t<std::is_convertible_v<Y*,T*>,int> = 0>
		NiPointer(NiPointer<Y>& rhs) :
			T1(rhs.T1)
		{
			TryLock();
		}

		NiPointer(NiPointer&& rhs) :
			T1(rhs.T1)
		{
			rhs.T1 = nullptr;
		}

		template <class Y, std::enable_if_t<std::is_convertible_v<Y*, T*>, int> = 0>
		NiPointer(NiPointer<Y>&& a_rhs) :
		T1(a_rhs.T1)
		{
			a_rhs.T1 = nullptr;
		}

		~NiPointer() 
		{ 
			TryLock();
		}

	public:
		T* get() const
		{
			return T1;
		}

		constexpr operator T*() const noexcept
		{
			return T1;
		}

		explicit operator bool() const noexcept
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

		NiPointer& operator=(const NiPointer& a_rhs)
		{
			if (this != std::addressof(a_rhs)) 
			{
				TryUnlock();
				T1 = a_rhs.T1;
				TryLock();
			}

			return *this;
		}

		NiPointer& operator=(T* a_rhs)
		{
			if (T1 != a_rhs)
			{
				TryUnlock();
				T1 = a_rhs;
				TryLock();
			}

			return *this;
		}
	protected:
		void TryLock()
		{
			if (T1)
			{
				T1->IncrementRef();
			}
		}
		
		void TryUnlock()
		{
			if (T1)
			{
				T1->DeincrementRef();
			}
		}

		void reset() { TryUnlock(); }

		template <class Y, typename std::enable_if<std::is_convertible<Y*, T*>::value, int>::type = 0>
		void reset(T* a_newptr)
		{
			if (T1 != a_newptr)
			{
				TryUnlock();
				T1 = a_newptr;
				TryLock();
			}
		}
	public:
		T* T1 { nullptr };
	};

	template <class T, class... Args>
	NiPointer<T> make_nismart(Args&&... a_args)
	{
		return NiPointer<T>{ new T(std::forward<Args>(a_args)...) };
	}

	template <class T1, class T2>
	constexpr bool operator==(const NiPointer<T1>& a_lhs, const NiPointer<T2>& a_rhs)
	{
		return a_lhs.get() == a_rhs.get();
	}

	template <class T1, class T2>
	constexpr bool operator!=(const NiPointer<T1>& a_lhs, const NiPointer<T2>& a_rhs)
	{
		return !(a_lhs == a_rhs);
	}

	template <class T>
	constexpr bool operator==(const NiPointer<T>& a_lhs, std::nullptr_t) noexcept
	{
		return !a_lhs;
	}

	template <class T>
	constexpr bool operator==(std::nullptr_t, const NiPointer<T>& a_rhs) noexcept
	{
		return !a_rhs;
	}

	template <class T>
	constexpr bool operator!=(const NiPointer<T>& a_lhs, std::nullptr_t) noexcept
	{
		return static_cast<bool>(a_lhs);
	}

	template <class T>
	constexpr bool operator!=(std::nullptr_t, const NiPointer<T>& a_rhs) noexcept
	{
		return static_cast<bool>(a_rhs);
	}
}