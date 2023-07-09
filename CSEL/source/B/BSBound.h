#pragma once
#include "../N/NiExtraData.h"
#include "../N/NiPoint3.h"

namespace ConsoleRE
{
	class BSBound : public NiExtraData
	{
	public:
		BSBound();
		virtual ~BSBound();
	public:
		NiPoint3 center;
		NiPoint3 extents;
	};
	static_assert(sizeof(BSBound) == 0x30, "#####################");
}