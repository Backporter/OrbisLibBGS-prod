#pragma once

#include "NiTMapBase.h"

namespace ConsoleRE
{
	template <typename Key, typename T>
	class NiTMap : public NiTMapBase<DFALL<NiTMapItem<Key, T>>, Key, T>
	{
	public:
		NiTMap(uint32_t	a_hashSize = 37) {}

		~NiTMap() override 
		{}

		NiTMapItem<Key, T>* malloc_value() override { return this->_allocator.Allocate(); }
		void				free_value(NiTMapItem<Key, T>* a_ptr) override { return this->_allocator.Release(a_ptr); }
	public:
	};
}