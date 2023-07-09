#pragma once

#include "../B/BSString.h"
#include "../F/FormTypes.h"
#include "../I/ImageSpaceModifierInstanceDOF.h"
#include "../N/NiPoint2.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	class NiColorInterpolator;
	class NiFloatInterpolator;

	struct ImageSpaceModifierData
	{
	public:
		template <typename T>
		struct MultAdd
		{
		public:
			T mult;
			T add;
		};

		template <typename T>
		struct MinMax
		{
		public:
			MultAdd<T> min;
			MultAdd<T> max;
		};

		struct HDR
		{
		public:
			MultAdd<float> eyeAdaptSpeed;
			MultAdd<float> bloomBlurRadius;
			MultAdd<float> bloomThreshold;
			MultAdd<float> bloomScale;
			MinMax<float>  targetLum;
			MultAdd<float> sunlightScale;
			MultAdd<float> skyScale;
			MultAdd<float> empty[6];
		};
		static_assert(sizeof(HDR) == 0x70);

		struct Bloom
		{
		public:
			MultAdd<float> empty[3];
		};
		static_assert(sizeof(Bloom) == 0x18);

		struct Cinematic
		{
		public:
			MultAdd<float> saturation;
			MultAdd<float> brightness;
			MultAdd<float> contrast;
			MultAdd<float> empty;
		};
		static_assert(sizeof(Cinematic) == 0x20);

		struct DOF
		{
		public:
			using Mode = ImageSpaceModifierInstanceDOF::DepthOfFieldMode;
		public:
			uint32_t	strength;
			uint32_t	distance;
			uint32_t	range;
			bool        useTarget;
			uint8_t		flags;
			uint16_t	pad0E;
		};
		static_assert(sizeof(DOF) == 0x10);
	public:
		bool			animatable;
		uint8_t			pad01;
		uint16_t		pad02;
		float			duration;
		HDR				hdr;
		Bloom			bloom;
		Cinematic		cinematic;
		uint32_t		tintColor;
		uint32_t		blurRadius;
		uint32_t		doubleVisionStrength;
		uint32_t		radialBlurStrength;
		uint32_t		radialBlurRampUp;
		uint32_t		radialBlurStart;
		bool			useTargetForRadialBlur;
		uint8_t			padC9;
		uint16_t		padCA;
		NiPoint2		radialBlurCenter;
		DOF				dof;
		uint32_t		radialBlurRampDown;
		uint32_t		radialBlurDownStart;
		uint32_t		fadeColor;
		uint32_t		motionBlurStrength;
	};
	static_assert(sizeof(ImageSpaceModifierData) == 0xF4);

	class TESImageSpaceModifier : public TESForm
	{
	public:
		static constexpr int TypeID = 90;

		template <typename T>
		struct MultAdd
		{
			T mult;
			T add;
		};

		template <typename T>
		struct MinMax
		{
			MultAdd<T> min;
			MultAdd<T> max;
		};

		struct HDR
		{
			MultAdd<NiPointer<NiFloatInterpolator>> eyeAdaptSpeed;
			MultAdd<NiPointer<NiFloatInterpolator>> bloomBlurRadius;
			MultAdd<NiPointer<NiFloatInterpolator>> bloomThreshold; 
			MultAdd<NiPointer<NiFloatInterpolator>> bloomScale;
			MinMax<NiPointer<NiFloatInterpolator>>  targetLum;
			MultAdd<NiPointer<NiFloatInterpolator>> sunlightScale;
			MultAdd<NiPointer<NiFloatInterpolator>> skyScale;
			MultAdd<NiPointer<NiFloatInterpolator>> empty[6];
		};
		static_assert(sizeof(HDR) == 0xE0);

		struct Bloom
		{
			MultAdd<NiPointer<NiFloatInterpolator>> empty[3];
		};
		static_assert(sizeof(Bloom) == 0x30);

		struct Cinematic
		{
			MultAdd<NiPointer<NiFloatInterpolator>> saturation;
			MultAdd<NiPointer<NiFloatInterpolator>> brightness;
			MultAdd<NiPointer<NiFloatInterpolator>> contrast;
			MultAdd<NiPointer<NiFloatInterpolator>> empty;
		};
		static_assert(sizeof(Cinematic) == 0x40);

		struct RadialBlur
		{
			NiPointer<NiFloatInterpolator> strength;
			NiPointer<NiFloatInterpolator> rampUp;
			NiPointer<NiFloatInterpolator> start;
			NiPointer<NiFloatInterpolator> rampDown;
			NiPointer<NiFloatInterpolator> downStart;
		};
		static_assert(sizeof(RadialBlur) == 0x28);

		struct DOF
		{
			NiPointer<NiFloatInterpolator> strength;
			NiPointer<NiFloatInterpolator> distance;
			NiPointer<NiFloatInterpolator> range;
		};
		static_assert(sizeof(DOF) == 0x18);
	public:
		~TESImageSpaceModifier() override;

		// override (TESForm)
		void        InitializeData() override;
		void        ClearData() override;
		bool        Load(TESFile* a_mod) override;
		const char* GetFormEditorID() const override;
		bool        SetFormEditorID(const char* a_str) override;
	public:
		ImageSpaceModifierData			data;
		HDR								hdr;
		Bloom							bloom;
		Cinematic						cinematic;
		NiPointer<NiFloatInterpolator>	blurRadius;
		NiPointer<NiFloatInterpolator>	doubleVisionStrength;
		NiPointer<NiColorInterpolator>	tintColor;
		NiPointer<NiColorInterpolator>	fadeColor;
		RadialBlur						radialBlur;
		DOF								dof;
		NiPointer<NiColorInterpolator>	motionBlurStrength;
		BSString						formEditorID;
	};
	static_assert(sizeof(TESImageSpaceModifier) == 0x2D8);
}