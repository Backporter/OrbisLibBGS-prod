#pragma once

// 
#include "../../../OrbisUtil/include/Logger.h"
#include "../../../OrbisUtil/include/std.h"

#include "../B/BSTTuple.h"
#include "../C/CRC.h"

#include <utility>
#include <assert.h>
#include <vector>

namespace ConsoleRE
{
	static constexpr uint8_t BSTScatterTableSentinel[] = { 0xDE, 0xAD, 0xBE, 0xEF };
	using UnkKey = uintptr_t;
	using UnkValue = uintptr_t;

	template <class _Hash, class _KeyEqual, class Traits, template <size_t, size_t> class _Allocator>
	class BSTScatterTable
	{
	public:
		using Key		= typename Traits::Key;
		using T			= typename Traits::Type;
		using Tuple		= typename Traits::Tuple;
		using Hash		= _Hash;
		using KeyEqual	= _KeyEqual;
		using Allocator = _Allocator<sizeof(T), alignof(T)>;

		struct entry_type
		{
		public:
			entry_type()
			{}

			entry_type(const entry_type&) = delete;

			entry_type(entry_type&& a_rhs)
			{
				if (a_rhs.HasValue())
				{
					const auto rnext = a_rhs.m_next;
					emplace(std::move(a_rhs).steal(), rnext);
				}
			}

			~entry_type() noexcept { destroy(); }

			entry_type& operator=(const entry_type&) = delete;

			entry_type& operator=(entry_type&& a_rhs)
			{
				if (this != std::addressof(a_rhs))
				{
					destroy();
					if (a_rhs.HasValue())
					{
						const auto rnext = a_rhs.m_next;
						emplace(std::move(a_rhs).steal(), rnext);
					}
				}
				return *this;
			}

			bool IsFree()	{ return m_next == nullptr; }
			bool HasValue() { return m_next != nullptr; }
			void SetFree()	{ m_next = nullptr; }
			
			void destroy()
			{
				if (HasValue())
				{
					std::destroy_at(std::addressof(m_item));
					SetFree();
				}
				assert(!HasValue());
			}

			template <class Arg>
			void emplace(Arg&& a_value, const entry_type* a_next)
			{
				static_assert(std::is_same_v<std::decay_t<Arg>, Tuple>);
				destroy();
				std::construct_at(std::addressof(m_item), std::forward<Arg>(a_value));
				m_next = const_cast<entry_type*>(a_next);
				assert(HasValue());
			}

			Tuple steal()
			{
				assert(HasValue());
				Tuple val = std::move(m_item);
				destroy();
				assert(IsFree());
				return val;
			}

			// DEBUG:

			void DumpEntry(xUtilty::Log* instance)
			{
				m_item.DumpEntriescSTR(instance);
				instance->Write(xUtilty::Log::logLevel::kNone, "\t\tnext: %08X", m_next);
			}
		public:
			union
			{
				Tuple		m_item;
				uint8_t		buffer[sizeof(Tuple)] { static_cast<uint8_t>(0) };
			};

			entry_type*		m_next { nullptr };
		};
	public:
		uint32_t	free()     { return m_free; }
		uint32_t	capacity() { return m_size; }
		uint32_t	size()	   { return m_size - m_free; }
		bool		empty()    { return size() == 0; }
		entry_type* end()      { return GetEntries() + m_size; }
	public:
		void		operator--(int) { --m_free; }
		
		//
		entry_type* GetEntries() { return static_cast<entry_type*>(m_allocator.GetEntries()); }
		bool		IsKeyEqual(const Key& a_lhs, const Key& a_rhs) { return static_cast<bool>(KeyEqual()(a_lhs, a_rhs)); }
		uint32_t	GetHash(const Key& a_key) { return static_cast<uint32_t>(Hash()(a_key)); }

		BSTScatterTable() = default;
		~BSTScatterTable() { free_resources(); }

		entry_type& GetEntryFor(const Key& a_key)
		{
			assert(GetEntries() != nullptr);

			const auto hash = GetHash(a_key);
			const auto idx = hash & (m_size - 1);
			return GetEntries()[idx];
		}

		entry_type& GetFreeEntry() noexcept
		{
			const auto entries = GetEntries();
			while (entries[m_good].HasValue())
			{
				m_good = (m_good + 1) & (m_size - 1);
			}

			return entries[m_good];
		}

		entry_type* find(const Key& a_key)
		{
			if (empty())
			{
				return end();
			}

			auto entry = &GetEntryFor(a_key);
			if (entry->HasValue())
			{
				do
				{
					if (IsKeyEqual(UnwrapKey(entry->m_item), a_key))
					{
						return entry;
					}
					else
					{
						entry = entry->m_next;
					}

				} while (entry != m_sentinel);
			}

			return end();
		}
		
		// will call find(a_key) and check if it returned a vaild entry, if it is, it expands the item and returns T&(casted to T*), should this return a nullptr no entry was found with the a_key
		T*			findT(const Key& a_key)
		{
			auto it = find(a_key);
			if (it && it != end())
			{
				return &it->m_item.second;
			}
			else
			{
				return nullptr;
			}
		}

		template <class P>
		bool		insert(P&& a_value)
		{
			if (const auto it = find(UnwrapKey(a_value)); it != end())
			{
				// already exists
				return false;
			}
			
			if (m_free == 0)
			{
				grow(m_size + 1);
				assert(m_free > 0);
			}
#if __cplusplus < 201703L
			const stl::scope_exit<std::remove_pointer_t<decltype(this)>> decrement(this);
#elif __cplusplus >= 201703L
			const stl::scope_exit decrement { [&]() noexcept { --m_free; } };
#endif
			const auto entry = &GetEntryFor(UnwrapKey(a_value));
			if (entry->HasValue())
			{
				const auto free = &GetFreeEntry();
				const auto wouldve = &GetEntryFor(UnwrapKey(entry->m_item));
				
				if (wouldve == entry)
				{
					// hash collision
					free->emplace(std::forward<P>(a_value), std::exchange(entry->m_next, free));
					return true;
				}
				else
				{
					// how did we get here?
					auto prev = wouldve;
					while (prev->m_next != entry)
					{
						prev = prev->m_next;
					}

					// evict current value and detach from chain
					*free = std::move(*entry);
					prev->m_next = free;
					entry->emplace(std::forward<P>(a_value), m_sentinel);
					return true;
				}

			}
			else
			{
				entry->emplace(std::forward<P>(a_value), m_sentinel);
				return true;
			}
		}

		template <class... Args>
		bool		emplace(Args&&... a_args)
		{
			return insert(Tuple(std::forward<Args>(a_args)...));
		}

		void		grow(uint32_t a_size)
		{
			if (a_size <= m_size)
				return;

			// old data
			const auto oldSize = m_size;
			const auto oldEntries = GetEntries();
			
			// new data
			const auto newSize = oldSize ? 2 * oldSize : 8;
			const auto newEntries = allocate(newSize);
			if (!newEntries)
			{
				// xUtilty::KernelPrintOut("Failed to allocate memory for hashmap.");
				return;
			}

			//
			SetEntires(newEntries);

			//
			m_size = newSize;
			m_free = newSize;
			m_good = 0;

			//
			if (newEntries == oldEntries)
			{
				// TBA
				assert(false);
			}
			else
			{
				std::uninitialized_default_construct_n(newEntries, newSize);

				if (oldEntries)
				{
					for (uint32_t i = 0; i < oldSize; i++)
					{
						auto& entry = oldEntries[i];
						if (entry.HasValue())
						{
							insert(std::move(entry).steal());
						}
					}
					std::destroy_n(oldEntries, oldSize);
					deallocate(oldEntries);
				}
			}
		}

		void		clear()
		{
			if (size() > 0)
			{
				const auto entires = GetEntries();
				assert(entires != nullptr);

				for (int i = 0; i < m_size; i++)
				{
					entires[i].destroy();
				}

				m_free = m_size;
				m_good = 0;
			}

			assert(empty());
		}

		void		free_resources()
		{
			if (m_size > 0)
			{
				auto entries = GetEntries();
				assert(entries != nullptr);
				std::destroy_n(entries, m_size);
				deallocate(entries);
				SetEntires(nullptr);
				m_size = 0;
				m_free = 0;
				m_good = 0;
			}

			assert(GetEntries() == nullptr);
			assert(m_size == 0);
			assert(m_free == 0);
		}

		// Traits
		static const Key& UnwrapKey(const Tuple& a_value) { return Traits::UnwrapKey(a_value); }
		static const T& UnwrapValue(const Tuple& a_value) { return Traits::UnwrapValue(a_value); }

		// _Allocator
		entry_type*	 allocate(size_t a_size)		   { return static_cast<entry_type*>(m_allocator.allocate(sizeof(entry_type) * a_size)); }
		void		 deallocate(entry_type* a_entries) { m_allocator.deallocate(a_entries); }
		void		 SetEntires(entry_type* a_entires) { m_allocator.SetEntires(a_entires); }

		// Debug:
		void DumpHashMap()
		{
			//
			xUtilty::Log* tempLog = new xUtilty::Log();

			//
			tempLog->OpenRelitive(1, (char*)"OSEL/HashMapDump.txt");

			//
			tempLog->Write(xUtilty::Log::logLevel::kNone, "BSTScatterTable:");
			tempLog->Write(xUtilty::Log::logLevel::kNone, "> capacity: %d", capacity());
			tempLog->Write(xUtilty::Log::logLevel::kNone, "> free: %d", free());
			tempLog->Write(xUtilty::Log::logLevel::kNone, "> filled: %d", size());

			if (GetEntries())
			{
				entry_type* p = GetEntries();
				for (uint32_t i = 0; i < m_size; i++, p++)
				{
					tempLog->Write(xUtilty::Log::logLevel::kNone, "* %d %s:", i, p->IsFree() ? "(free)" : "");
					if (!p->IsFree())
					{
						p->DumpEntry(tempLog);
					}
				}
			}


			tempLog->Close();
			delete tempLog;
		}
	public:
		uint32_t			m_size { 0 };
		uint32_t			m_free { 0 };
		uint32_t			m_good { 0 };
		uint32_t			pad0C  { 0 };
		const entry_type*	m_sentinel { reinterpret_cast<const entry_type*>(BSTScatterTableSentinel) };
		Allocator			m_allocator;
	};

	template <typename _Key, typename T>
	class BSTScatterTableTraits
	{
	public:
		using Key = _Key;
		using Type = T;
		using Tuple = BSTTuple<const Key, T>;
	public:
		static const Key& UnwrapKey(const Tuple& a_value) noexcept
		{
			return a_value.first;
		}

		static const Type& UnwrapValue(const Tuple& a_value) noexcept
		{
			return a_value.second;
		}
	};

	template <size_t S, size_t A>
	class BSTScatterTableHeapAllocator
	{
	public:
		static constexpr uint32_t MinSize = 8;
	public:
		void* allocate(size_t a_size)
		{
			assert(a_size % S == 0);
			return malloc(a_size);
		}

		void deallocate(void* a_ptr)
		{
			free(a_ptr);
		}

		void* GetEntries() const noexcept
		{
			return m_entries;
		}

		void SetEntires(void* a_entires) noexcept
		{
			m_entries = static_cast<int8_t*>(a_entires);
		}
	public:
		int8_t* m_entries { nullptr };
	};

	template <class Key, class T, class Hash = BSCRC32<Key>, class KeyEq = std::equal_to<Key>>
	using BSTHashMap = BSTScatterTable<Hash, KeyEq, BSTScatterTableTraits<Key, T>, BSTScatterTableHeapAllocator>;
}