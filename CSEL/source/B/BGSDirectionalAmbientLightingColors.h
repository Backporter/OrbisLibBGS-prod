#pragma once

#include "../C/Color.h"

namespace ConsoleRE
{
	// based on CLSSE.
	class BGSDirectionalAmbientLightingColors
	{
	public:
		struct Directional
		{
		public:
			template <class T>
			struct MaxMin
			{
			public:
				T max;
				T min;
			};
			static_assert(sizeof(MaxMin<Color>) == 0x8);
		public:
			MaxMin<Color> x;
			MaxMin<Color> y;
			MaxMin<Color> z;
		};
		static_assert(sizeof(Directional) == 0x18);
	public:
		Directional directional;
		Color       specular;
		float       fresnelPower;
	};
	static_assert(sizeof(BGSDirectionalAmbientLightingColors) == 0x20);
}