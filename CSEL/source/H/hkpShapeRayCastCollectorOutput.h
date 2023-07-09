#pragma once
#include "../H/hkVector4.h"

namespace ConsoleRE
{
	class hkpShapeRayCastCollectorOutput
	{
	public:
		hkVector4    normal;
		float        hitFraction{ 1.0F };
		int32_t		 extraInfo{ -1 };
		int32_t		 shapeKey { -1 };
		int32_t		 pad{ 0 };
	};
}