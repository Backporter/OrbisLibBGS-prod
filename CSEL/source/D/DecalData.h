#pragma once

#include "../C/Color.h"

#include <stdint.h>

namespace ConsoleRE
{
	struct DECAL_DATA_DATA
	{
	public:
		enum Flag : uint8_t
		{
			kNone = 0,
			kParallax = 1 << 0,
			kAlphaBlending = 1 << 1,
			kAlphaTesting = 1 << 2,
			kNoSubtextures = 1 << 3
		};
	public:
		float			decalMinWidth;
		float			decalMaxWidth;
		float			decalMinHeight;
		float			decalMaxHeight;
		float			depth;
		float			shininess;
		float			parallaxScale;
		int8_t			parallaxPasses;
		Flag			flags;
		uint16_t		pad1E;
		Color			color;
	};
	static_assert(sizeof(DECAL_DATA_DATA) == 0x24);

	struct DecalData
	{
	public:
		DECAL_DATA_DATA data;
	};
	static_assert(sizeof(DecalData) == 0x24);
}