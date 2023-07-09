#pragma once

#include "../N/NiPoint2.h"

#include <stdint.h>
#include <stddef.h>

namespace ConsoleRE
{
	class PlayerControlsData
	{
	public:
		NiPoint2		moveInputVec;
		NiPoint2		lookInputVec;
		NiPoint2		prevMoveVec;
		NiPoint2		prevLookVec;
		uint32_t		unk20;
		bool			autoMove;
		bool			running;
		bool			unk26;
		bool			fovSlideMode;
		bool			povScriptMode;
		bool			povBeastMode;
		bool			unk2A;
		bool			unk2B;
		bool			remapMode;
		uint8_t			unk2D;
		uint16_t		unk2E;
	};
	static_assert(sizeof(PlayerControlsData) == 0x30, "");
}