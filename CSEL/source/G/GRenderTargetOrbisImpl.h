#pragma once
#include <stdint.h>

namespace ConsoleRE
{
	class GRenderTargetOrbisImpl
	{
	public:
		virtual ~GRenderTargetOrbisImpl();
		uint8_t pad[0x68];
	private:
	};
	// 0x68
	static_assert(sizeof(GRenderTargetOrbisImpl) != 0, "class size mismatch");
}