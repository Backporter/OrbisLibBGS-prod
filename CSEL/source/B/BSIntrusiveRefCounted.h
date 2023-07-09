#pragma once

#include <atomic>

namespace ConsoleRE
{
	struct BSIntrusiveRefCounted
	{
	public:
		uint32_t IncRef() const
		{
			return __sync_add_and_fetch(&refcount, 1);
		}

		uint32_t DecRef() const
		{
			return __sync_sub_and_fetch(&refcount, 1);
		}
	public:
		mutable volatile uint32_t refcount { 0 };
	};
	static_assert(sizeof(BSIntrusiveRefCounted) == 0x4);
}