#pragma once

#include "../../../OrbisUtil/include/std.h"
#include "../N/NiSmartPointer.h"

#include "../C/CRC.h"

#include <stdint.h>

namespace ConsoleRE
{
	class Actor;
	class HandleManager;
	class Projectile;
	class TESObjectREFR;

	template <uint32_t = 20, uint32_t = 6>
	class BSUntypedPointerHandle;

	template <class, class = BSUntypedPointerHandle<>>
	class BSPointerHandle;

	template <class, class = HandleManager>
	class BSPointerHandleManagerInterface;

	template <uint32_t FREE_LIST_BITS, uint32_t AGE_SHIFT>
	class BSUntypedPointerHandle
	{
	public:
		enum : uint32_t
		{
			kFreeListBits = FREE_LIST_BITS,
			kAgeShift = AGE_SHIFT,
		};
	public:
		BSUntypedPointerHandle() noexcept = default;
		BSUntypedPointerHandle(const BSUntypedPointerHandle&) noexcept = default;

		BSUntypedPointerHandle(BSUntypedPointerHandle&& a_rhs) noexcept :
		_handle(a_rhs._handle)
		{
			a_rhs.reset();
		}

		BSUntypedPointerHandle(uint32_t a_handle) noexcept : 
			_handle(a_handle) 
		{}

		~BSUntypedPointerHandle() noexcept { reset(); }

		BSUntypedPointerHandle& operator=(const BSUntypedPointerHandle&) noexcept = default;

		BSUntypedPointerHandle& operator=(BSUntypedPointerHandle&& a_rhs) noexcept
		{
			if (this != std::addressof(a_rhs))
			{
				_handle = a_rhs._handle;
				a_rhs.reset();
			}

			return *this;
		}

		BSUntypedPointerHandle& operator=(uint32_t a_rhs) noexcept
		{
			_handle = a_rhs;
			return *this;
		}
	public:
		operator bool() { return has_value(); }

		bool		has_value() { return _handle != 0; }

		uint32_t	value() { return _handle; }

		void		reset() { _handle = 0; }

		friend bool operator==(const BSUntypedPointerHandle& a_lhs, const BSUntypedPointerHandle& a_rhs) noexcept
		{
			return a_lhs.value() == a_rhs.value();
		}

		friend bool operator!=(const BSUntypedPointerHandle& a_lhs, const BSUntypedPointerHandle& a_rhs) noexcept
		{
			return !(a_lhs == a_rhs);
		}
	public:
		uint32_t _handle{ 0 };
	};

	extern template class BSUntypedPointerHandle<>;

	template <class T, class Handle>
	class BSPointerHandle
	{
	public:
		BSPointerHandle() noexcept = default;
		BSPointerHandle(const BSPointerHandle&) noexcept = default;
		BSPointerHandle(BSPointerHandle&&) noexcept = default;

		template <class Y, std::enable_if_t<std::is_convertible_v<Y*, T*>, int> = 0>
		explicit BSPointerHandle(Y* a_rhs)
		{
			get_handle(a_rhs);
		}

		template <class Y, std::enable_if_t<std::is_convertible_v<Y*, T*>, int> = 0>
		BSPointerHandle(const BSPointerHandle<Y, Handle>& a_rhs) noexcept :
			_handle(a_rhs._handle)
		{}
		
		BSPointerHandle& operator=(const BSPointerHandle&) noexcept = default;
		BSPointerHandle& operator=(BSPointerHandle&&) noexcept = default;
		
		template <class Y, std::enable_if_t<std::is_convertible_v<Y*, T*>, int> = 0>
		BSPointerHandle& operator=(Y* a_rhs)
		{
			get_handle(a_rhs);
			return *this;
		}

		template <class Y, std::enable_if_t<std::is_convertible_v<Y*, T*>, int> = 0>
		BSPointerHandle& operator=(const BSPointerHandle<Y, Handle>& a_rhs) noexcept
		{
			_handle = a_rhs._handle;
			return *this;
		}

		~BSPointerHandle() noexcept = default;

		void reset() noexcept { return _handle.reset(); }

		NiPointer<T> get() const
		{
			NiPointer<T> ret;
			get_smartptr(ret);
			return ret;
		}

		uint32_t native_handle() { return _handle.value(); }

		explicit operator bool() const noexcept { return _handle.has_value(); }

		friend bool operator==(const BSPointerHandle& a_lhs, const BSPointerHandle& a_rhs) noexcept
		{
			return a_lhs._handle == a_rhs._handle;
		}

		friend bool operator!=(const BSPointerHandle& a_lhs, const BSPointerHandle& a_rhs) noexcept
		{
			return !(a_lhs == a_rhs);
		}
	public:
		Handle _handle;
	private:
		void get_handle(T* a_ptr);
		bool get_smartptr(NiPointer<T>& a_smartPointerOut) const;
	};
	
	extern template class BSPointerHandle<Actor>;
	extern template class BSPointerHandle<Projectile>;
	extern template class BSPointerHandle<TESObjectREFR>;

	using ActorHandle = BSPointerHandle<Actor>;
	using ProjectileHandle = BSPointerHandle<Projectile>;
	using ObjectRefHandle = BSPointerHandle<TESObjectREFR>;

	template <class T>
	struct BSCRC32<BSPointerHandle<T>>
	{
	public:
		uint32_t operator()(const BSPointerHandle<T>& a_handle) const noexcept
		{
			return BSCRC32<uint32_t>()(a_handle.native_handle());
		}
	};

	template <class T, class Manager>
	class BSPointerHandleManagerInterface
	{
	public:
		using value_type = T;

		static BSPointerHandle<T> GetHandle(T* a_ptr)
		{
			assert(false);
			
			using func_t = decltype(&BSPointerHandleManagerInterface<T, Manager>::GetHandle);
			REL::Relocation<func_t> func{ REL::ID<0>(16212) };
			return func(a_ptr);
		}

		static bool GetSmartPointer(const BSPointerHandle<T>& a_handle, NiPointer<T>& a_smartPointerOut)
		{
			assert(false);

			using func_t = decltype(&BSPointerHandleManagerInterface<T, Manager>::GetSmartPointer);
			REL::Relocation<func_t> func{ REL::ID<0>(12332) };
			return func(a_handle, a_smartPointerOut);
		}
	};

	template <class T, class Handle>
	void BSPointerHandle<T, Handle>::get_handle(T* a_ptr)
	{
		*this = BSPointerHandleManagerInterface<T>::GetHandle(a_ptr);
	}

	template <class T, class Handle>
	bool BSPointerHandle<T, Handle>::get_smartptr(NiPointer<T>& a_smartPointerOut) const
	{
		return BSPointerHandleManagerInterface<T>::GetSmartPointer(*this, a_smartPointerOut);
	}

}