#pragma once

#include "../B/BSIntrusiveRefCounted.h"

namespace ConsoleRE
{
	class IMessageBoxCallback : public BSIntrusiveRefCounted
	{
	public:
		virtual ~IMessageBoxCallback() = default;
		
		// add
		virtual void Run(uint32_t) = 0;
	public:
		uint32_t pad0C;
	};
	static_assert(sizeof(IMessageBoxCallback) == 0x10);
}