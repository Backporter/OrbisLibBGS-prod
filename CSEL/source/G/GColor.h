#pragma once

#include <stdint.h>

namespace ConsoleRE
{
	class GColor
	{
	public:
		struct RGB32
		{
			uint8_t blue;
			uint8_t green;
			uint8_t red;
			uint8_t alpha;
		};
		static_assert(sizeof(RGB32) == 0x4);
		
		union ColorData
		{
			RGB32	 channels;
			uint32_t raw;
		};
		static_assert(sizeof(ColorData) == 0x4);
	public:
		ColorData colorData;
	};
}