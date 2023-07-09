#pragma once

#include "../U/UserEvents.h"

namespace RE
{
	class UserEventEnabled
	{
	public:
		uint32_t newUserEventFlag;
		uint32_t oldUserEventFlag;
	};
	static_assert(sizeof(UserEventEnabled) == 0x8);
}
