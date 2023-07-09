#pragma once

#include "../../../OrbisUtil/include/MessageHandler.h"
#include "../../../OrbisUtil/include/std.h"
#include "../../../OrbisUtil/include/Logger.h"
#include "../../../OrbisUtil/include/Macro.h"

#include "../M/MemoryManager.h"

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <algorithm>

namespace ConsoleRE
{
	class ScrapHeap;

	class BSTArrayBase
	{
	public:
		class IAllocatorFunctor
		{
		public:
			virtual bool Unk_02(uint32_t a_unk, uint32_t a_unk2) = 0;
			virtual bool Unk_03(uint32_t a_unk, uint32_t a_unk2, uint32_t a_unk3, uint32_t a_unk4, uint32_t a_unk5) = 0;
			virtual void Unk_04() = 0;
			virtual ~IAllocatorFunctor();
		};
		static_assert(sizeof(IAllocatorFunctor) == 0x8, "");
	public:
		using size_type = uint32_t;
		constexpr bool empty() const noexcept { return m_size == 0; }
		constexpr uint32_t size() const noexcept { return m_size; }
	public:
		BSTArrayBase() : m_size(0) { }
		~BSTArrayBase() { m_size = 0; }

		void set_size(uint32_t a_size) { m_size = a_size; }
	public:
		uint32_t m_size{ 0 };
	};
	static_assert(sizeof(BSTArrayBase) == 0x4);

	class BSTArrayHeapAllocator
	{
	public:
		constexpr void* data() noexcept	{ return m_entries; }
		constexpr const void* data() const noexcept { return m_entries; }
		constexpr uint32_t capacity() const noexcept { return m_capacity; }
	public:
		BSTArrayHeapAllocator() : m_entries(0), m_capacity(0)
		{
		}

		~BSTArrayHeapAllocator()
		{
			deallocate(data());
			m_entries = 0;
			m_capacity = 0;
		}

	protected:
		void*	allocate(size_t a_size)
		{
			void* mem = malloc(a_size);
			if (mem)
			{
				memset(mem, 0, a_size);
				return mem;
			}
			else
			{
				xUtilty::KernelPrintOut("%s (%s, %d) failed to allocate memory.", __FUNCTION__, __FILE__, __LINE__);
				assert(false);
				return mem;
			}
		}

		void	deallocate(void* a_ptr) { free(a_ptr); }

		constexpr void set_allocator_traits(void* a_data, uint32_t a_capacity, size_t) noexcept
		{
			m_entries = a_data;
			m_capacity = a_capacity;
		}
	public:
		void*		 m_entries { nullptr };
		uint32_t	 m_capacity { 0 };
	};
	static_assert(sizeof(BSTArrayHeapAllocator) == 0x10);

	template <size_t N>
	class BSTSmallArrayHeapAllocator
	{
	public:
		using size_type = uint32_t;

		union Data
		{
			void* heap;
			char  local[N] { 0 };
		};
	public:
		constexpr void*       data() noexcept { return local() ? m_data.local : m_data.heap; }
		constexpr const void* data() const noexcept { return local() ? m_data.local : m_data.heap; }
		constexpr size_type capacity() const noexcept { return m_capacity; }
		constexpr bool local() const noexcept { return m_local != 0; }
		constexpr void set_allocator_traits(void* a_data, uint32_t a_capacity, size_t a_typeSize) noexcept
		{
			m_capacity = a_capacity;
			if (a_capacity * a_typeSize > N)
			{
				m_local = 0;
				m_data.heap = a_data;
			}
		}
	public:
		BSTSmallArrayHeapAllocator() noexcept : m_capacity(0), m_local(1) { }
		~BSTSmallArrayHeapAllocator() { release(); }
	protected:
		void*	allocate(size_t a_size)
		{
			if (a_size > N)
			{
				const auto mem = malloc(a_size);
				if (mem)
				{
					memset(mem, 0, a_size);
					return mem;
				}
				else
				{
					xUtilty::KernelPrintOut("%s (%s, %d) failed to allocate memory.", __FUNCTION__, __FILE__, __LINE__);
					assert(false);
				}
			}
			else
			{
				return m_data.local;
			}
		}

		void	deallocate(void* a_ptr)
		{
			if (a_ptr != m_data.local)
			{
				free(a_ptr);
			}
		}

		void	release()
		{
			if (!local())
			{
				free(m_data.heap);
			}

			memset(data(), 0, capacity());
			m_capacity = N;
			m_local = 1;
		}
	public:
		uint32_t	  m_capacity : 31;
		uint32_t	  m_local : 1;
		Data          m_data;
	};

	class BSScrapArrayAllocator
	{
	public:
		using size_type = uint32_t;
	public:
		constexpr void*       data() noexcept { return m_data; }
		constexpr const void* data() const noexcept { return m_data; }
		constexpr uint32_t capacity() const noexcept { return m_capacity; }
		constexpr void set_allocator_traits(void* a_data, uint32_t a_capacity, std::size_t) noexcept
		{
			m_data = a_data;
			m_capacity = a_capacity;
		}
	public:
		BSScrapArrayAllocator() { }
		~BSScrapArrayAllocator() { if (m_data) { deallocate(m_data); } memset(this, 0, sizeof(*this)); }
	protected:
		void* allocate(size_t a_size)
		{
			if (!m_allocator)
			{
				auto heap = MemoryManager::GetSingleton();
				m_allocator = heap ? heap->GetThreadScrapHeap() : nullptr;
			}

			assert(m_allocator);
			auto mem = m_allocator->allocate(a_size, alignof(void*));
			assert(mem != nullptr);
			memset(mem, 0, a_size);
			return mem;
		}
		
		void  deallocate(void* a_ptr)
		{
			if (m_allocator)
			{
				m_allocator->deallocate(a_ptr);
			}
			else
			{
				assert(false);
			}
		}

		bool  resize(uint32_t a_length)
		{
			using func_t = bool(decltype(this), uint32_t);
			Relocation <func_t*> func("", 0xADEB50);
			return func(this, a_length);
		}

	public:
		ScrapHeap* m_allocator{ nullptr };
		void*      m_data{ nullptr };
		uint32_t   m_capacity{ 0 };
	};

	template<typename T, class Allocator = BSTArrayHeapAllocator>
	class BSTArray : public Allocator, public BSTArrayBase
	{
	public:
		static constexpr size_type DF_CAP = 4;           // beth default
		static constexpr float     GROWTH_FACTOR = 2.0;  // not part of native type
	public:
		constexpr T& operator[](uint32_t a_pos) noexcept
		{
			assert(a_pos < size());
			return data() [a_pos];
		}

		constexpr const T& operator[](uint32_t a_pos) const noexcept
		{
			assert(a_pos < size());
			return data() [a_pos];
		}

		constexpr T& front() noexcept
		{
			return operator[](0);
		}

		constexpr const T& front() const noexcept 
		{ 
			return operator[](0); 
		}

		constexpr T&       back() noexcept 
		{ 
			return operator[](size() - 1);
		}

		constexpr const T& back() const noexcept 
		{ 
			return operator[](size() - 1);
		}

		constexpr T* data() noexcept
		{
			return static_cast<T*>(Allocator::data());
		}

		constexpr const T* data() const noexcept
		{
			return static_cast<const T*>(Allocator::data());
		}

		constexpr T* begin() noexcept
		{
			return empty() ? nullptr : data();
		}
		
		constexpr const T* begin() const noexcept
		{
			return empty() ? nullptr : data();
		}

		constexpr const T* cbegin() const noexcept
		{
			return begin();
		}

		constexpr T* end() noexcept
		{
			return empty() ? nullptr : data() + size();
		}

		constexpr const T* end() const noexcept
		{
			return empty() ? nullptr : data() + size();
		}

		constexpr const T* cend() const noexcept
		{
			return end();
		}

		constexpr uint32_t size() const noexcept
		{
			return BSTArrayBase::size();
		}

		constexpr bool empty() const noexcept
		{
			return BSTArrayBase::empty();
		}

		constexpr void set_size(uint32_t a_size) noexcept
		{
			BSTArrayBase::set_size(a_size);
		}

		constexpr uint32_t capacity() const noexcept
		{
			return Allocator::capacity();
		}

		constexpr void set_allocator_traits(void* a_data, uint32_t a_capacity) noexcept
		{
			Allocator::set_allocator_traits(a_data, a_capacity, sizeof(T));
		}
	public:
		BSTArray() = default;

		BSTArray(uint32_t a_count)
		{ 
			if (a_count == 0) 
			{
				return;
			}

			const auto newCapacity = a_count;
			const auto newSize = a_count;
			const auto newData = allocate(newCapacity);
			for (size_type i = 0; i < newSize; ++i) 
			{
				std::construct_at(newData + i);
			}

			set_allocator_traits(newData, newCapacity);
			set_size(newSize);
		}

		~BSTArray() { release(); }
	public:
		inline void push_back(const T& a_value) { emplace_back(a_value); }
		inline void push_back(T&& a_value) { emplace_back(std::move(a_value)); }

		template <class... Args>
		inline T& emplace_back(Args&&... a_args)
		{
			if (size() == capacity()) 
			{
				grow_capacity();
			}

			set_size(size() + 1);
			auto& elem = back();
			std::construct_at(std::addressof(elem), std::forward<Args>(a_args)...);
			return elem;
		}

		template <class... Args>
		void change_size(size_type a_newSize, Args&&... a_args)
		{
			if (a_newSize > capacity())
			{
				grow_capacity(a_newSize);
			}

			const auto oldSize = size();
			if (a_newSize > oldSize)
			{
				for (size_type i = oldSize; i < a_newSize; ++i)
				{
					std::construct_at(data() + i, std::forward<Args>(a_args)...);
				}
			}
			else
			{
				for (size_type i = a_newSize; i < oldSize; ++i) 
				{
					std::destroy_at(data() + i);
				}
			}

			set_size(a_newSize);
		}

		void change_capacity(size_type a_newCapacity)
		{
			const auto newData = a_newCapacity > 0 ? allocate(a_newCapacity) : nullptr;
			const auto oldData = data();

			if (oldData) 
			{
				const auto oldCapacity = capacity();
				if (newData) 
				{
					const auto bytesToCopy = std::min(oldCapacity, a_newCapacity) * sizeof(T);
					std::memcpy(newData, oldData, bytesToCopy);
				}

				deallocate(oldData);
			}

			set_allocator_traits(newData, a_newCapacity);
		}

		void grow_capacity(size_type a_hint)
		{
			auto cap = a_hint;
			cap = cap > 0 ? static_cast<size_type>(ceil(static_cast<float>(cap) * GROWTH_FACTOR)) : DF_CAP;
			change_capacity(cap);
		}

		void grow_capacity() { grow_capacity(capacity()); }

		void reserve(uint32_t a_newCap)
		{
			if (a_newCap > capacity())
			{
				change_capacity(a_newCap);
			}
		}

		void clear()
		{
			if (!empty()) 
			{
				change_size(0);
			}
		}

		void release()
		{
			clear();
			change_capacity(0);
		}

		void resize(uint32_t a_count)
		{
			if (a_count != size()) 
			{
				change_size(a_count);
			}
		}

		void resize(uint32_t a_count, T& a_value)
		{
			if (a_count != size()) 
			{
				change_size(a_count, a_value);
			}
		}

		inline void pop_back()
		{
			assert(!empty());
			std::destroy_at(std::addressof(back()));
			set_size(size() - 1);
		}

		//void		release()
		//{
		//	if (Allocator::m_entries)
		//	{
		//		for (int i = 0; i < size(); i++)
		//		{
		//			operator[](i).~T(); // Allocator::m_entries[i].~T();
		//		}
		//
		//		deallocate((void*)Allocator::m_entries);
		//	}
		//
		//	set_allocator_traits(nullptr, 0);
		//	set_size(0);
		//}
		//
		//bool		CreateArray(uint32_t a_size)
		//{
		//	Allocator::m_entries = static_cast<T*>(allocate(a_size));
		//
		//	if (!Allocator::m_entries)
		//	{
		//		Log::Log::GetSingleton()->Write("Failed to alloc for BSTArray");
		//		return false;
		//	}
		//
		//	for (int i = 0; i < a_size; i++)
		//	{
		//		new (&static_cast<T*>(Allocator::m_entries)[i]) T;
		//	}
		//
		//
		//	set_allocator_traits(Allocator::m_entries, a_size);
		//	set_size(a_size);
		//
		//	return true;
		//}
		//
		//bool		resize(size_t a_newsize)
		//{
		//	if (!Allocator::m_entries)
		//		CreateArray(a_newsize);
		//
		//	T* newdata = static_cast<T*>(allocate(a_newsize));
		//	if (!newdata)
		//	{
		//		MessageHandler::KernelPrintOut("Failed To Allocate Memory for BSTArray<T, T>::Resize");
		//		return false;
		//	}
		//
		//	memcpy(newdata, Allocator::m_entries, sizeof(T) * m_size);
		//	release();
		//
		//	set_allocator_traits(Allocator::m_entries, a_newsize);
		//	set_size(a_newsize);
		//	
		//	return true;
		//}
	public:
		T*			Get(uint32_t a_idx)
		{
			if (a_idx <= size())
				return &operator[](a_idx);

			return nullptr;
		}

		int			Get(T& op)
		{
			for (int i = 0; i < size(); i++)
			{
				T& pI = operator[](i); // Allocator::m_entries[i];
				if (pI == op)
					return i;
			}

			return -1;
		}

		bool		Get(int i, T& out)
		{
			if (i < size())
			{
				out = operator[](i); // Allocator::m_entries[i];
				return true;
			}

			return false;
		}

		bool		GetSortIndex(T& elem, int32_t& indexOut)
		{
			uint32_t count = size();
			if (count == 0)
			{
				indexOut = 0;
				return false;
			}

			int32_t leftIdx = 0;
			int32_t rightIdx = count - 1;

			while (true)
			{
				uint32_t pivotIdx = leftIdx + ((rightIdx - leftIdx) / 2);

				T& p = operator[](pivotIdx);

				if (elem == p)
				{
					indexOut = pivotIdx;
					return true;
				}
				else if (elem > p)
				{
					leftIdx = pivotIdx + 1;
				}
				else
				{
					rightIdx = pivotIdx - 1;
				}

				if (leftIdx > rightIdx)
				{
					indexOut = leftIdx;
					return false;
				}
			}
		}
	protected:
		T*			allocate(uint32_t a_num)
		{
			return static_cast<T*>(Allocator::allocate(a_num * sizeof(T)));
		}

		void		deallocate(void* a_ptr)
		{
			Allocator::deallocate(a_ptr);
		}
	};

	template <class T, uint32_t N = 1>
	using BSTSmallArray = BSTArray<T, BSTSmallArrayHeapAllocator<sizeof(T) * N>>;

	template <class T>
	using BSScrapArray = BSTArray<T, BSScrapArrayAllocator>;
}