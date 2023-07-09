#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class GRendererOrbisImpl
	{
	public:
		virtual ~GRendererOrbisImpl();
		uint8_t pad[0x4128];
	private:
	};
	// 0x4128
	static_assert(sizeof(GRendererOrbisImpl) != 0, "class size mismatch");
}