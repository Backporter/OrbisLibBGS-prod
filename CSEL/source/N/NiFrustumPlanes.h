#pragma once

#include "../N/NiPlane.h"

#include <stdint.h>

namespace ConsoleRE
{
	class NiFrustumPlanes
	{
	public:
		NiPlane                                     cullingPlanes[6];
		uint32_t									activePlanes;
		uint32_t									basePlaneStates;
		uint32_t									unk68;
		uint32_t									unk6C;
	};
	static_assert(sizeof(NiFrustumPlanes) == 0x70, "");
}