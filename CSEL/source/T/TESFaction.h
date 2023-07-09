#pragma once

#include "../A/AITimeStamp.h"
#include "../B/BSFixedString.h"
#include "../B/BSTHashMap.h"
#include "../B/BSTList.h"
#include "../F/FormTypes.h"
#include "../T/TESForm.h"
#include "../T/TESFullName.h"
#include "../T/TESReactionForm.h"
#include "../T/TESTexture.h"

namespace ConsoleRE
{
	class TESCondition;
	class PackageLocation;

	struct FACTION_DATA
	{
		enum Flag : uint32_t
		{
			kNone = 0,
			kHiddenFromNPC = 1 << 0,
			kSpecialCombat = 1 << 1,
			kPlayerIsExpelled = 1 << 2,
			kPlayerIsEnemy = 1 << 3,
			kTrackCrime = 1 << 6,
			kIgnoresCrimes_Murder = 1 << 7,
			kIgnoresCrimes_Assult = 1 << 8,
			kIgnoresCrimes_Stealing = 1 << 9,
			kIngoresCrimes_Trespass = 1 << 10,
			kDoNotReportCrimesAgainstMembers = 1 << 11,
			kCrimeGold_UseDefaults = 1 << 12,
			kIgnoresCrimes_Pickpocket = 1 << 13,
			kVendor = 1 << 14,
			kCanBeOwner = 1 << 15,
			kIgnoresCrimes_Werewolf = 1 << 16
		};
	public:
		uint32_t flags;
	};
	static_assert(sizeof(FACTION_DATA) == 0x4);

	struct FACTION_CRIME_DATA_VALUES
	{
	public:
		bool     arrest;
		bool     attackOnSight;
		uint16_t murderCrimeGold;
		uint16_t assaultCrimeGold;
		uint16_t trespassCrimeGold;
		uint16_t pickpocketCrimeGold;
		uint16_t pad0A;
		float    stealCrimeGoldMult;
		uint16_t escapeCrimeGold;
		uint16_t werewolfCrimeGold;
	};
	static_assert(sizeof(FACTION_CRIME_DATA_VALUES) == 0x14);

	struct FACTION_CRIME_DATA
	{
	public:
		TESObjectREFR*            factionJailMarker;
		TESObjectREFR*            factionWaitMarker;
		TESObjectREFR*            factionStolenContainer;
		TESObjectREFR*            factionPlayerInventoryContainer;
		BGSListForm*              crimeGroup;
		BGSOutfit*                jailOutfit;
		FACTION_CRIME_DATA_VALUES crimevalues;
		uint32_t				  pad44;                          
	};
	static_assert(sizeof(FACTION_CRIME_DATA) == 0x48);

	struct FACTION_VENDOR_DATA_VALUES
	{
	public:
		uint16_t	  startHour;
		uint16_t	  endHour;
		uint32_t	  locationRadius;
		bool          buysStolen;
		bool          notBuySell;
		bool          buysNonStolen;
		uint8_t		  padB;
	};
	static_assert(sizeof(FACTION_VENDOR_DATA_VALUES) == 0xC);

	struct FACTION_VENDOR_DATA
	{
	public:
		FACTION_VENDOR_DATA_VALUES	vendorValues;
		uint32_t					pad0C;
		PackageLocation*			vendorLocation;
		TESCondition*				vendorConditions;
		BGSListForm*				vendorSellBuyList;
		TESObjectREFR*				merchantContainer;
		uint32_t					lastDayReset;
		uint32_t					pad34;
	};
	static_assert(sizeof(FACTION_VENDOR_DATA) == 0x38);

	struct RANK_DATA
	{
	public:
		BSFixedString maleRankTitle;
		BSFixedString femaleRankTitle;
		TESTexture    textureInsignia;
	};
	static_assert(sizeof(RANK_DATA) == 0x20);

	class TESFaction : public TESForm, public TESFullName, public TESReactionForm
	{
	public:
		static constexpr int TypeID = 11;
	public:
		~TESFaction() override;

		// override (TESForm)
		void InitializeData() override;
		void ClearData() override;
		bool Load(TESFile* a_mod) override;
		void SaveGame(BGSSaveFormBuffer* a_buf) override;
		void LoadGame(BGSLoadFormBuffer* a_buf) override;
		void Revert(BGSLoadFormBuffer* a_buf) override;
		void InitItemImpl() override;
	public:
		// ...
		BSTHashMap<uint32_t, TESNPC*>* CrimeGoldMap;
		FACTION_DATA                   data;
		uint32_t					   pad4C;
		FACTION_CRIME_DATA             crimeData;
		FACTION_VENDOR_DATA            vendorData;
		BSSimpleList<RANK_DATA*>       rankData;
		int32_t                        majorCrime;
		int32_t                        minorCrime;
		AITimeStamp                    resistArrestTimeStamp;
		float                          pcEnemyFlagTimeStamp;
	};
	static_assert(sizeof(TESFaction) == 0x100);
}