#include "../B/BSFixedString.h"

namespace ConsoleRE
{
	namespace detail
	{
		template class BSFixedString<char>;
		static_assert(sizeof(BSFixedString<char>) == 0x8);

		template class BSFixedString<wchar_t_t>;
		static_assert(sizeof(BSFixedString<wchar_t_t>) == 0x8);
	}
}
