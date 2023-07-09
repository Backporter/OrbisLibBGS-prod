//

#include "../B/BSStringPool.h"

namespace ConsoleRE
{
	void BSStringPool::Entry::release8(const char*& a_entry)
	{
		using func_t = decltype(&Entry::release8);
		Relocation<func_t> func("", 0xE4E730);
		return func(a_entry);
	}

	void BSStringPool::Entry::release16(const wchar_t_t*& a_entry)
	{
		using func_t = decltype(&Entry::release16);
		Relocation<func_t> func("", 0xE4FB30);
		return func(a_entry);
	}

	void BSStringPool::Entry::acquire()
	{
		bool s_break;
		uint16_t expected = _flags;
		do
		{
			if ((expected & kRefCountMask) == kRefCountMask)
			{
				break;
			}

			auto ret = __sync_val_compare_and_swap(&_flags, expected, static_cast<uint16_t>(expected + 1));

			if (expected == ret)
				ret = expected;

			s_break = ret == expected;
			expected = ret;

		} while (!s_break);
	}
}