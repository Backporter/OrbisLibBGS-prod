#pragma once

#include "../B/BSTHashMap.h"
#include "../B/BGSMusicType.h"
#include "../B/BSTArray.h"
#include "../B/BSString.h"
#include "../N/NiPoint2.h"
#include "../T/TESObjectCELL.h"
#include "../T/TESForm.h"
#include "../T/TESFullName.h"
#include "../T/TESModel.h"
#include "../T/TESClimate.h"
#include "../T/TESTexture.h"

namespace ConsoleRE
{
	class BGSTerrainManager;
	class BGSMusicType;
	class BGSEncounterZone;
	class BGSLocation;
	class BGSLightingTemplate;
	class TESWaterForm;

	struct WORLD_MAP_DATA
	{
	public:
		struct CameraData
		{
			float minHeight;
			float maxHeight;
			float initialPitch;
		};
		static_assert(sizeof(CameraData) == 0xC);
	public:
		uint32_t	usableWidth;
		uint32_t	usableHeight;
		int16_t		nwCellX;
		int16_t		nwCellY;
		int16_t		seCellX;
		int16_t		seCellY;
		CameraData  cameraData;
	};
	static_assert(sizeof(WORLD_MAP_DATA) == 0x1C);

	struct WORLD_MAP_OFFSET_DATA
	{
	public:
		float mapScale;
		float mapOffsetX;
		float mapOffsetY;
		float mapOffsetZ;
	};
	static_assert(sizeof(WORLD_MAP_OFFSET_DATA) == 0x10);

	class BGSLargeRefData
	{
	public:
		BSTHashMap<UnkKey, UnkKey>			cellFormIDMap;
		BSTHashMap<UnkKey, UnkKey>			formIDCellMap;
		BSTHashMap<UnkKey, UnkKey>			cellFormIDMapFiltered;
	};

	// 0x2C8
	class TESWorldSpace :  public TESForm, public TESFullName, public TESModel
	{
	public:
		static constexpr int TypeID = 71;
	
		struct ShortPoint
		{
		public:
			int16_t x;
			int16_t y;
		};
		static_assert(sizeof(ShortPoint) == 0x4);
	public:
		~TESWorldSpace() override;
	public:
		BSTHashMap<UnkValue, UnkValue>		cellMap;
		TESObjectCELL*                      persistentCell;
		BGSTerrainManager*                  terrainManager;
		TESClimate*                         climate;
		uint8_t								flags;
		uint8_t								Unk91;
		uint16_t							parentUseFlags;
		ShortPoint                          fixedCenter;
		BSTHashMap<UnkValue, UnkValue>		fixedPersistentRefMap;
		BSTArray<NiPointer<TESObjectREFR>>	mobilePersistentRefs;
		void*								UnkC8;
		TESObjectCELL*						skyCell;
		BSTHashMap<UnkValue, UnkValue>		locationMap;
		void*								UnkF8; 
		void*								Unk100;
		void*								Unk108;
		void*								Unk110;
		void*								Unk118;
		TESWorldSpace*						parentWorld;
		BGSLightingTemplate*				lightingTemplate;
		TESWaterForm*						worldWater;
		TESWaterForm*						lodWater;
		float								lodWaterHeight;
		uint32_t							Unk144;
		uint64_t							Unk148;
		WORLD_MAP_DATA                      worldMapData;
		WORLD_MAP_OFFSET_DATA               worldMapOffsetData;
		uint32_t							Unk17C;
		BGSMusicType*						musicType;
		NiPoint2							minimumCoords;
		NiPoint2							maximumCoords;
		BSTHashMap<UnkKey, UnkValue>		Unk198;
		BSString							editorID;
		float								defaultLandHeight;
		float								defaultWaterHeight;
		float								distantLODMult;
		uint32_t							Unk1D4;
		BGSEncounterZone*					encounterZone;
		BGSLocation*						location;
		TESTexture							canopyShadowTexture;
		TESTexture							waterEnvMap;
		BGSLargeRefData						largeRefData;
		uint64_t							Unk268;
		uint32_t							Unk270;
		uint32_t							Unk274;
		BSTHashMap<UnkKey, UnkKey>			Unk278;
		BSTHashMap<UnkKey, UnkKey>			Unk298;
		float								northRotation;
		uint32_t							Unk2BC;
		int8_t*								maxHeightData;
	};
	static_assert(sizeof(TESWorldSpace) == 0x2C8);
}