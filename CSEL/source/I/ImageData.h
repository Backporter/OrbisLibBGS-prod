#pragma once

#include "../B/BSFixedString.h"

namespace ConsoleRE
{
	class ImageData
	{
	public:
		void*         Unk00;
		uint64_t	  Unk08;
		BSFixedString Unk10;
	};
	static_assert(sizeof(ImageData) == 0x18);
}