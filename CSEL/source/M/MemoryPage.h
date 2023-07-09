#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	namespace BSScript
	{
		struct MemoryPage
		{
		public:
			template <typename T>
			T*	  Get() { return reinterpret_cast<T*>(m_pages); }
			void* Head() { return m_pages; }
			void* Tail() { return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(Head()) + m_pageSize); }
			bool  Range(const void* a_ptr) { return Head() <= a_ptr && a_ptr < Tail(); }
		public:
			uint32_t m_pageSize;
			char	 m_pages[0];
		};
	}
}