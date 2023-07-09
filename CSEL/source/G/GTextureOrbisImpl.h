#pragma once
#include <stdint.h>

namespace ConsoleRE
{
	class GTextureOrbisImpl
	{
	public:
		virtual ~GTextureOrbisImpl();
		uint8_t pad[0xE0];
	private:
	};

	// 0xE0
	static_assert(sizeof(GTextureOrbisImpl) != 0, "class size mismatch");
}