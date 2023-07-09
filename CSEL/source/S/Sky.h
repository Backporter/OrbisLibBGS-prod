#pragma once

#include "../B/BSTArray.h"
#include "../B/BSSimpleList.h"
#include "../B/BSTextureSet.h"
#include "../N/NiColor.h"
#include "../N/NiPointer.h"
#include "../S/SkyEffectController.h"

namespace ConsoleRE
{
	class Atmosphere;
	class BGSLightingTemplate;
	class BSMultiBoundNode;
	class Clouds;
	class ImageSpaceModifierInstanceForm;
	class Moon;
	class NiNode;
	class NiTexture;
	class Precipitation;
	class ReferenceEffect;
	class SkySound;
	class Stars;
	class Sun;
	class TESClimate;
	class TESRegion;
	class TESWeather;

	class Sky
	{
	public:
		enum class Mode
		{
			kNone = 0,
			kInterior,
			kSkyDomeOnly,
			kFull,
			kTotal
		};

		struct SkyStaticRefData
		{
		public:
		};
	public:
		virtual ~Sky();

		static Sky* GetSingleton()
		{
			Relocation<Sky**> singleton("", 0x3100F38);
			return *singleton;
		}
	public:
		NiPointer<BSMultiBoundNode>           root;
		NiPointer<NiNode>                     moonsRoot;
		NiPointer<NiNode>                     auroraRoot;
		uint64_t							  unk020;
		BGSLightingTemplate*                  extLightingOverride;
		uint32_t							  currentRoom;
		uint32_t							  previousRoom;
		float                                 lightingTransition;
		float                                 lightingTransitionTimer;
		TESClimate*                           currentClimate;
		TESWeather*                           currentWeather;
		TESWeather*                           lastWeather;
		TESWeather*                           defaultWeather;
		TESWeather*                           overrideWeather;
		TESRegion*                            region;
		Atmosphere*                           atmosphere;
		Stars*                                stars;
		Sun*                                  sun;
		Clouds*                               clouds;
		Moon*                                 masser;
		Moon*                                 secunda;
		Precipitation*                        precip;
		NiColor                               skyColor[17];
		uint32_t							  unk174;
		uint64_t							  unk178;
		uint64_t							  unk180;
		uint32_t							  unk188;
		float                                 windSpeed;
		float                                 windAngle;
		uint32_t							  unk194;
		uint64_t							  unk198;
		uint32_t							  unk1A0;
		uint32_t							  unk1A4;
		float                                 unk1A8;
		float                                 unk1AC;
		float                                 currentGameHour;
		float                                 lastWeatherUpdate;
		float                                 currentWeatherPct;
		uint32_t							  mode;
		BSSimpleList<SkySound*>*              skySoundList;
		float                                 flash;
		uint32_t							  pad1CC;
		std::time_t                           flashTime;
		uint32_t							  lastMoonPhaseUpdate;
		uint32_t							  flags;
		ImageSpaceModifierInstanceForm*       currentWeatherImageSpaceMod;
		ImageSpaceModifierInstanceForm*       currentWeatherImageSpaceMod2;
		ImageSpaceModifierInstanceForm*       lastWeatherImageSpaceMod;
		ImageSpaceModifierInstanceForm*       lastWeatherImageSpaceMod2;
		NiColor                               directionalAmbientColors[3][2];
		NiColor                               ambientSpecularTint;
		float                                 ambientSpecularFresnel;
		float                                 auroraInStart;
		float                                 auroraIn;
		float                                 auroraOutStart;
		float                                 auroraOut;
		NiPointer<ReferenceEffect>            currentReferenceEffect;
		NiPointer<ReferenceEffect>            lastReferenceEffect;
		SkyEffectController                   effectController;
		BSTArray<NiPointer<NiTexture>>        storedCloudTextures;
		BSTArray<NiPointer<NiTexture>>        storedWorldMapCloudTextures;
		BSTArray<SkyStaticRefData>            skyStaticRefData;
	};
	static_assert(sizeof(Sky) == 0x2B0);
}