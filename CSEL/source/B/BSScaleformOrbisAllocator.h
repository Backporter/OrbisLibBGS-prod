#pragma once
#include <stdint.h>

namespace ConsoleRE
{
	class BSScaleformOrbisAllocator
	{
	public:
		virtual ~BSScaleformOrbisAllocator();
		uint8_t pad[0x18];
	private:
	};
	// 0x18
	static_assert(sizeof(BSScaleformOrbisAllocator) != 0, "class size mismatch");
}