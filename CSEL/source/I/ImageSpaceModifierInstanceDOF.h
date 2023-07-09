#pragma once

#include "../I/ImageSpaceModifierInstanceTemp.h"

namespace ConsoleRE
{
	struct ImageSpaceModData
	{
	public:
		enum
		{
			kFadeAmount = 0,
			kFadeR = 1,
			kFadeG = 2,
			kFadeB = 3,
			kBlurRadius = 4,
			kDoubleVisionStrength = 5,
			kRadialBlurStrength = 6,
			kRadialBlurRampup = 7,
			kRadialBlurStart = 8,
			kRadialBlurRampdown = 9,
			kRadialBlurDownStart = 10,
			kRadialBlurCenterX = 11,
			kRadialBlurCenterY = 12,
			kDOFStrength = 13,
			kDOFDistance = 14,
			kDOFRange = 15,
			kDOFMode = 16,
			kMotionBlurStrength = 17,
			kTotal = 18
		};
	public:
		float data[kTotal];
	};
	static_assert(sizeof(ImageSpaceModData) == 0x48);

	class ImageSpaceModifierInstanceDOF : public ImageSpaceModifierInstanceTemp
	{
	public:
		enum class DepthOfFieldMode
		{
			kFrontBack = 0,
			kFront = 1,
			kBack = 2,
			kNone = 3
		};
	public:
		~ImageSpaceModifierInstanceDOF() override;

		// override (ImageSpaceModifierInstanceTemp)
		void Apply() override;
		void PrintInfo(char* a_dstBuf) override;
	public:
		ImageSpaceModData data;
	};
	static_assert(sizeof(ImageSpaceModifierInstanceDOF) == 0x78);
}