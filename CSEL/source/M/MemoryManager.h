#pragma once

#include "../../../OrbisUtil/include/Relocation.h"
#include "../../../OrbisUtil/include/std.h"

#include "../S/ScrapHeap.h"

#include <stdint.h>
#include <memory>

namespace ConsoleRE
{
	class BSSmallBlockAllocator;
	class IMemoryHeap;

	namespace CompactingStore 
	{
		class Store; 
	}

	class MemoryManager
	{
	public:
		struct ThreadScrapHeap
		{
		public:
			ScrapHeap        heap;
			ThreadScrapHeap* next;
			uint32_t		 owningThread;
			uint32_t		 pad;
		};
		static_assert(sizeof(ThreadScrapHeap) == 0xA0, "");
	public:
		static MemoryManager* GetSingleton()
		{
			Relocation<uint32_t*>					g_mem		("", 0x20BEC08);
			Relocation<MemoryManager*>				singleton	("", 0x20BE780);

			assert(*g_mem.get() == 2);

			if ((*g_mem) != 2)
			{
				singleton->Ctor();
			}

			return singleton.get();
		}

		void* Allocate(size_t a_size, int32_t a_alignment, bool a_alignmentRequired)
		{
			using func_t = void*(decltype(this), size_t, int32_t, bool);
			Relocation<func_t*> func("", 0xE26860);
			return func(this, a_size, a_alignment, a_alignmentRequired);
		}

		void  Deallocate(void* a_mem, bool a_alignmentRequired)
		{
			using func_t = void(decltype(this), void*, bool);
			Relocation<func_t*> func("", 0xE26CC0);
			return func(this, a_mem, a_alignmentRequired);
		}

		ScrapHeap* GetThreadScrapHeap()
		{
			using func_t = ScrapHeap*(decltype(this));
			Relocation<func_t*> func("", 0xE278B0);
			return func(this);
		}

		void* Reallocate(void* a_oldMem, size_t a_newSize, int32_t a_alignment, bool a_aligned)
		{
			using func_t = void*(decltype(this), void*, size_t, int32_t, bool);
			Relocation<func_t*> func("", 0xE26EE0);
			return func(this, a_oldMem, a_newSize, a_alignment, a_aligned);
		}
		
		void RegisterMemoryManager()
		{
			using func_t = void(decltype(this));
			Relocation<func_t*> func("", 0x68CE70);
			return func(this);
		}

		void Ctor()
		{
			using func_t = decltype(&MemoryManager::Ctor);
			REL::Relocation<func_t> func("", 0xE261D0);
			return func(this);
		}
	private:
		bool                    initialized{ false };
		uint16_t				numHeaps{ 0 };
		uint16_t				numPhysicalHeaps{ 0 };
		IMemoryHeap**           heaps{ nullptr };
		bool*                   allowOtherContextAllocs{ nullptr };
		IMemoryHeap*            heapsByContext[127]{ nullptr };
		ThreadScrapHeap*        threadScrapHeap{ nullptr };
		IMemoryHeap**           physicalHeaps{ nullptr };
		IMemoryHeap*            bigAllocHeap{ nullptr };
		IMemoryHeap*            emergencyHeap{ nullptr };
		BSSmallBlockAllocator*  smallBlockAllocator{ nullptr };
		CompactingStore::Store* compactingStore{ nullptr };
		IMemoryHeap*            externalHavokAllocator{ nullptr };
		bool                    specialHeaps{ false };
		bool                    allowPoolUse{ true };
		uint32_t				sysAllocBytes{ 0 };
		uint32_t				mallocBytes{ 0 };
		uint32_t				alignmentForPools{ 4 };
		uint32_t				mainThreadMemoryProblemPassSignal{ 0 };
		size_t					failedAllocationSize{ 0 };
		uint32_t				numMemoryProblemPassesRun{ 0 };
		size_t					timeOfLastMemoryProblemPass{ 0 };
		IMemoryHeap*            defaultHeap{ nullptr };
	};
	static_assert(sizeof(MemoryManager) == 0x480);

	template <typename T>
	class SimpleArray
	{
	public:
		T&			operator[](size_t a_pos) noexcept 
		{
			assert(a_pos < size());
			return m_data[a_pos]; 
		}

		const T&	operator[](size_t a_pos) const noexcept
		{
			assert(a_pos < size());
			return m_data[a_pos]; 
		}

		T&			front() noexcept { return operator[](0); }
		const T&	front() const noexcept { return operator[](0); }
		T&			back() noexcept { return operator[](size() - 1); }
		const T&	back() const noexcept { return operator[](size() - 1); }
		T*			data() noexcept { return m_data; }
		const T*	data() const noexcept { return m_data; }
		T*			begin() noexcept { return m_data; }
		const T*	begin() const noexcept { return m_data; }
		const T*	cbegin() const noexcept { return begin(); }
		T*			end() noexcept { return m_data ? m_data + size() : nullptr; }
		const T*	end() const noexcept { return m_data ? m_data + size() : nullptr; }
		const T*	cend() const noexcept { return end(); }
		bool		empty() const noexcept { return size() == 0; }
		size_t		size() const noexcept { return m_data ? *static_cast<const size_t*>(head()) : 0; }
	public:
		constexpr SimpleArray() noexcept = default;

		explicit SimpleArray(size_t a_count) { resize(a_count); }

		~SimpleArray()
		{
			static_assert(!std::is_trivially_destructible<T>::value);
			clear();
		}

		void clear()
		{
			if (m_data)
			{
				std::destroy_n(data(), size());
				free(head());
				m_data = nullptr;
			}
		}

		void resize(size_t a_count)
		{
			const auto oldSize = size();
			if (oldSize == a_count)
			{
				return;
			}

			const auto newData = [=]()
			{
				auto bytes = sizeof(T) * a_count;
				if constexpr (alignof(T) > alignof(size_t))
				{
					bytes += sizeof(T);
				}
				else
				{
					bytes += sizeof(size_t);
				}

				const auto data = (size_t*)malloc(bytes);
				*data = a_count;

				if constexpr (alignof(T) > alignof(size_t)) 
				{
					return reinterpret_cast<T*>(data) + 1;
				}
				else 
				{
					return reinterpret_cast<T*>(data + 1);
				}
			}();

			if (a_count < oldSize) 
			{ 
				// shrink
				std::uninitialized_move_n(data(), a_count, newData);
			}
			else
			{  
				// grow
				std::uninitialized_move_n(data(), oldSize, newData);
				std::uninitialized_default_construct_n(newData + oldSize, a_count - oldSize);
			}

			clear();
			m_data = newData;
		}
	protected:
		void* head() noexcept
		{
			if constexpr (alignof(T) > alignof(size_t))
			{
				return m_data - 1;
			}
			else
			{
				return reinterpret_cast<size_t*>(m_data) - 1;
			}
		}

		const void* head() const noexcept
		{
			if constexpr (alignof(T) > alignof(size_t))
			{
				return m_data - 1;
			}
			else
			{
				return reinterpret_cast<const size_t*>(m_data) - 1;
			}
		}
	public:
		T* m_data { nullptr };
	};
}