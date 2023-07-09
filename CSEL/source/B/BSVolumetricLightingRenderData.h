#pragma once

namespace ConsoleRE
{
	class BSVolumetricLightingRenderData
	{
	public:
		struct CustomColor
		{
		public:
			float contribution;
		};
		static_assert(sizeof(CustomColor) == 0x4);

		struct Density
		{
		public:
			float contribution;
			float size;
			float windSpeed;
			float fallingSpeed;
		};
		static_assert(sizeof(Density) == 0x10);

		struct PhaseFunction
		{
		public:
			float contribution;
			float scattering;
		};
		static_assert(sizeof(PhaseFunction) == 0x8);

		struct SamplingRepartition
		{
		public:
			float rangeFactor;
		};
		static_assert(sizeof(SamplingRepartition) == 0x4);
	public:
		float               intensity;
		CustomColor         customColor;
		float               red;
		float               green;
		float               blue;
		Density             density;
		PhaseFunction       phaseFunction;
		SamplingRepartition samplingRepartition;
	};
	static_assert(sizeof(BSVolumetricLightingRenderData) == 0x30);
}