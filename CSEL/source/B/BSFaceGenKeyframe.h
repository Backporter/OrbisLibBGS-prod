#pragma once
#include <stdint.h>

namespace ConsoleRE
{
	class BSFaceGenKeyframe
	{
	public:
		BSFaceGenKeyframe();
		virtual ~BSFaceGenKeyframe();
	public:
		uint32_t Unk08;
		float	 Unk0C;
	};
	static_assert(sizeof(BSFaceGenKeyframe) == 0x10, "");
}