#pragma once

#include "../B/BSTArray.h"
#include "../B/BSTList.h"
#include "../B/BGSDirectionalAmbientLightingColors.h"
#include "../B/BGSLensFlare.h"
#include "../B/BGSVolumetricLighting.h"
#include "../B/BGSShaderParticleGeometryData.h"
#include "../B/BGSReferenceEffect.h"

#include "../C/Color.h"

#include "../T/TESForm.h"
#include "../T/TESTexture1024.h"
#include "../T/TESImageSpace.h"

namespace ConsoleRE
{
	// 0x8D0
	class TESWeather : public TESForm
	{
	public:
		static constexpr int TypeID = 54;
		TESWeather();
		virtual ~TESWeather();
	public:
		TESTexture1024						cloudTextures[32];
		int8_t								cloudLayerSpeedY[32];
		int8_t								cloudLayerSpeedX[32];
		Color4								cloudColorData[32][4];
		float								cloudAlpha[32][4];
		uint32_t							cloudLayerDisabledBits;

		// ^ = confirmed.
		int8_t								windSpeed;
		int8_t								unk01;
		int8_t								unk02;
		int8_t								transDelta;
		int8_t								sunGlare;
		int8_t								sunDamage;
		int8_t								precipitationBeginFadeIn;
		int8_t								precipitationEndFadeOut;
		int8_t								thunderLightningBeginFadeIn;
		int8_t								thunderLightningEndFadeOut;
		int8_t								thunderLightningFrequency;
		uint8_t								flags;
		Color3								lightningColor;
		int8_t								visualEffectBegin;
		int8_t								visualEffectEnd;
		int8_t								windDirection;
		int8_t								windDirectionRange;
		int8_t								unk13;
		float								dayNear;
		float								dayFar;
		float								nightNear;
		float								nightFar;
		float								dayPower;
		float								nightPower;
		float								dayMax;
		float								nightMax;
		Color								colorData[17][4];
		BSSimpleList<void*>					sounds;
		BSTArray<void*>						skyStatics;
		uint32_t							numCloudLayers;
		uint32_t							pad7CC;
		TESImageSpace*						imageSpaces[4];
		BGSDirectionalAmbientLightingColors directionalAmbientLightingColors[4];
		TESModel                            aurora;
		BGSLensFlare*                       sunGlareLensFlare;
		BGSVolumetricLighting*              volumetricLighting[4];
		BGSShaderParticleGeometryData*      precipitationData;
		BGSReferenceEffect*                 referenceEffect;
	};
	static_assert(offsetof(TESWeather, skyStatics) == 0x7B8, "offsetof(TESWeather, skyStatics) != 0x7B8");
	static_assert(sizeof(TESWeather) == 0x8D0, "TESWeather");
}