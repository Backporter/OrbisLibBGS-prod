#pragma once

#include "../B/BSIntrusiveRefCounted.h"

namespace ConsoleRE
{
	class BSPathingCell : public BSIntrusiveRefCounted
	{
	public:
		virtual ~BSPathingCell();
	public:
		uint32_t unk0C;
	};
	static_assert(sizeof(BSPathingCell) == 0x10);
}