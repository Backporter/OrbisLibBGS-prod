#pragma once

#include "../B/BGSDirectionalAmbientLightingColors.h"
#include "../C/Color.h"

namespace ConsoleRE
{
	struct INTERIOR_DATA
	{
	public:
		enum class Inherit
		{
			kAmbientColor = 1 << 0,
			kDirectionalColor = 1 << 1,
			kFogColor = 1 << 2,
			kFogNear = 1 << 3,
			kFogFar = 1 << 4,
			kDirectionalRotation = 1 << 5,
			kDirectionalFade = 1 << 6,
			kClipDistance = 1 << 7,
			kFogPower = 1 << 8,
			kFogMax = 1 << 9,
			kLightFadeDistances = 1 << 10
		};
	public:
		Color                                    ambient;
		Color                                    directional;
		Color                                    fogColorNear;
		float                                    fogNear;
		float                                    fogFar;
		uint32_t								 directionalXY;
		uint32_t								 directionalZ;
		float                                    directionalFade;
		float                                    clipDist;
		float                                    fogPower;
		BGSDirectionalAmbientLightingColors      directionalAmbientLightingColors;
		Color                                    fogColorFar;
		float                                    fogClamp;
		float                                    lightFadeStart;
		float                                    lightFadeEnd;
		uint32_t								 lightingTemplateInheritanceFlags;
		uint32_t								 unk5C;
	};
	static_assert(sizeof(INTERIOR_DATA) == 0x60);
}