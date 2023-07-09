#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	// 0x10, ctor is inlined.
	class StandardDetectionListener
	{
	public:
		StandardDetectionListener();
		virtual ~StandardDetectionListener();
	public:
		// _InterlockedAnd
		int32_t _InterlockedAnd(int32_t a_value)
		{
			return __sync_fetch_and_and(&refcount, a_value);
		}

		// _InterlockedExchangeAdd
		int32_t InterlockedExchangeAdd(int32_t a_value = 1)
		{
			return __sync_fetch_and_add(&refcount, a_value);
		}

		// InterlockedExchange
		int32_t InterlockedExchange(int32_t a_value)
		{
			return __sync_lock_test_and_set(&refcount, a_value);
		}

		// InterlockedIncrement
		int32_t IncrementRef()
		{
			return __sync_add_and_fetch(&refcount, 1);
		}

		// InterlockedDecrement
		int32_t DeincrementRef()
		{
			return __sync_sub_and_fetch(&refcount, 1);
		}
	public:
		volatile int32_t refcount;
		int32_t pad0C;;
	};
	static_assert(sizeof(StandardDetectionListener) == 0x10, "");
}