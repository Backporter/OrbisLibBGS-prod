#pragma once

#include "../H/hkVector4.h"
#include <stdint.h>

namespace ConsoleRE
{
	struct hkpSurfaceInfo
	{
	public:
		enum class SupportedState
		{
			kUnsupported = 0,
			kSliding = 1,
			kSupported = 2
		};
	public:
		uint32_t										supportedState;
		uint32_t										Unk04;
		uint64_t										Unk08;
		hkVector4                                       surfaceNormal;
		hkVector4                                       surfaceVelocity;
		float                                           surfaceDistanceExcess;
		bool                                            surfaceIsDynamic;
		uint8_t											Unk35;
		uint16_t										Unk36;
		uint64_t										Unk38;
	};
	static_assert(sizeof(hkpSurfaceInfo) == 0x40, "");
}