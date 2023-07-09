#pragma once

// Relocation
#include "../../../../../OrbisUtil/include/Relocation.h"

#include "../../../../source/G/GFxLoader.h"

namespace GFx
{
	using ctor_t = void(ConsoleRE::GFxLoader*&);
	extern Relocation<ctor_t*> func; // 0x1116350

	void RegisterGFx(ConsoleRE::GFxLoader*& a);
}