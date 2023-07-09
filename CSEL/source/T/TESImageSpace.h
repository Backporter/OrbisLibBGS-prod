#pragma once

#include "../T/TESForm.h"

namespace ConsoleRE
{
	struct ImageSpaceBaseData
	{
		struct HDR
		{
		public:
			float eyeAdaptSpeed;
			float bloomBlurRadius;
			float bloomThreshold;
			float bloomScale;
			float receiveBloomThreshold;
			float white;
			float sunlightScale;
			float skyScale;
			float eyeAdaptStrength;
		};
		static_assert(sizeof(HDR) == 0x24);

		struct Cinematic
		{
		public:
			float saturation;
			float brightness;
			float contrast;
		};
		static_assert(sizeof(Cinematic) == 0xC);

		struct Tint
		{
		public:
			struct ColorF
			{
			public:
				float red;
				float green;
				float blue;
			};
			static_assert(sizeof(ColorF) == 0xC);
		public:
			float  amount;
			ColorF color;
		};
		static_assert(sizeof(Tint) == 0x10);

		struct DepthOfField
		{
		public:
			enum class SkyBlurRadius
			{
				kRadius0 = 16384,
				kRadius1 = 16672,
				kRadius2 = 16784,
				kRadius3 = 16848,
				kRadius4 = 16904,
				kRadius5 = 16936,
				kRadius6 = 16968,
				kRadius7 = 17000,
				kNoSky_Radius0 = 16576,
				kNoSky_Radius1 = 16736,
				kNoSky_Radius2 = 16816,
				kNoSky_Radius3 = 16880,
				kNoSky_Radius4 = 16920,
				kNoSky_Radius5 = 16952,
				kNoSky_Radius6 = 16984,
				kNoSky_Radius7 = 17016
			};
		public:
			float											strength;
			float											distance;
			float											range;
			uint16_t										unk0C;
			uint16_t										skyBlurRadius;
		};
		static_assert(sizeof(DepthOfField) == 0x10);
	public:
		HDR          hdr;
		Cinematic    cinematic;
		Tint         tint;
		DepthOfField depthOfField;
	};
	static_assert(sizeof(ImageSpaceBaseData) == 0x50);

	class TESImageSpace : public TESForm
	{
	public:
		static constexpr int TypeID = 89;
		
		~TESImageSpace() override;
	public:
		ImageSpaceBaseData data;
	};
}