#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class GRefCountImplCore
	{
	public:
		virtual ~GRefCountImplCore() = default;

		uint32_t GetRefCount() 
		{ 
			return Ref; 
		}
	public:
		volatile uint32_t Ref { 1 };
	};
	static_assert(sizeof(GRefCountImplCore) == 0x10);
}