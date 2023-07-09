#include "../B/BSXFlags.h"

namespace ConsoleRE
{
	uint32_t BSXFlags::GetFlags() const
	{
		return value;
	}

	void BSXFlags::SetFlags(uint32_t a_flags)
	{
		value = a_flags;
	}
}