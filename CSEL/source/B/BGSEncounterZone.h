#pragma once

#include "../T/TESForm.h"

namespace ConsoleRE
{
	struct ENCOUNTER_ZONE_DATA
	{
	public:
		enum class Flag
		{
			kNone = 0,
			kNeverResets = 1 << 0,
			kMatchPCBelowMinimumLevel = 1 << 1,
			kDisableCombatBoundary = 1 << 2
		};
	public:
		TESFaction*                          zoneOwner;
		BGSLocation*                         location;
		int8_t								 ownerRank;
		int8_t								 minLevel;
		uint8_t								 flags;
		int8_t								 maxLevel;
		uint32_t							 pad14;
	};
	static_assert(sizeof(ENCOUNTER_ZONE_DATA) == 0x18);

	struct ENCOUNTER_ZONE_GAME_DATA
	{
	public:
		uint32_t detachTime;
		uint32_t attachTime;
		uint32_t resetTime;
		uint16_t zoneLevel;
		uint16_t pad0D;
	};
	static_assert(sizeof(ENCOUNTER_ZONE_GAME_DATA) == 0x10);

	class BGSEncounterZone : public TESForm
	{
	public:
		static constexpr int TypeID = 103;
		
		~BGSEncounterZone() override;
	public:
		ENCOUNTER_ZONE_DATA      data;
		ENCOUNTER_ZONE_GAME_DATA gameData;
	};
}