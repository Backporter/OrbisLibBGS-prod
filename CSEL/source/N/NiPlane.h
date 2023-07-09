#pragma once
#include "NiPoint3.h"

namespace ConsoleRE
{
	class NiPlane
	{
	public:
		NiPoint3 normal;
		float    constant;
	};
}