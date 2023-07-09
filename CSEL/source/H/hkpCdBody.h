#pragma once

#include "../H/hkpShape.h"

#include <stdint.h>

namespace ConsoleRE
{
	class hkpShape;
	
	class hkpCdBody
	{
	public:
		const hkpShape*  shape;
		uint32_t         shapeKey;
		uint32_t		 pad0C;
		const void*      motion;
		const hkpCdBody* parent;
	};
}