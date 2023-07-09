#pragma once

#include "../../../OrbisUtil/include/Relocation.h"

#include "NiTDefaultAllocator.h"

#include <stdint.h>

namespace ConsoleRE
{
	template <class Key, class T>
	class NiTMapItem
	{
	public:
		NiTMapItem* next;
		Key			first;
		T			second;
	};
	static_assert(sizeof(NiTMapItem<uint32_t, uint64_t>) == 0x18);

	template <class Allocator, class Key, class T>
	class NiTMapBase
	{
	public:
		struct SafeAllocator : public Allocator
		{
		public:
			SafeAllocator() : Allocator(), size(0) { }
		public:
			size_t size;
		};
	public:
		NiTMapBase(uint32_t a_capacity = 37) : _capacity(a_capacity), _pad0C(0), _data(0), _allocator() 
		{
			static Relocation<NiTMapItem<T, Key>**(*)(uint32_t)> Allocate("", 0xE41E70);
			_data = Allocate(a_capacity);
			memset(_data, 0, sizeof(NiTMapItem<T, Key>*) * a_capacity);
		}
		
		virtual ~NiTMapBase() { }
	public:
		virtual uint32_t			hash_function(Key a_key) { return (a_key % _capacity); }
		virtual bool				key_eq(Key a_lhs, Key a_rhs) { return (a_lhs == a_rhs); }
		
		virtual void				assign_value(NiTMapItem<T, Key>* a_value, Key a_key, T a_map)
		{
			a_value->first = a_key;
			a_value->second = a_map;
		}
		
		virtual void				clear_value(NiTMapItem<T, Key>* a_value) { }
		virtual NiTMapItem<Key, T>* malloc_value() = 0;
		virtual void				free_value(NiTMapItem<Key, T>*) = 0;
	public:
		uint32_t			 _capacity;
		uint32_t			 _pad0C;
		NiTMapItem<T, Key>** _data;
		SafeAllocator		 _allocator;
	};
}