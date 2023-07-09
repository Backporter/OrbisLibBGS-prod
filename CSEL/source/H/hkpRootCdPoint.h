#pragma once

#include "../H/hkContactPoint.h"
#include "../H/hkpShape.h"

#include <stdint.h>

namespace ConsoleRE
{
	class hkpCollidable;

	struct hkpRootCdPoint
	{
		hkContactPoint       contact;
		const hkpCollidable* rootCollidableA;
		uint32_t			 shapeKeyA;
		uint32_t			 pad2C;
		const hkpCollidable* rootCollidableB;
		uint32_t			 shapeKeyB;
		uint32_t			 pad3C;
	};
	static_assert(sizeof(hkpRootCdPoint) == 0x40);
}
