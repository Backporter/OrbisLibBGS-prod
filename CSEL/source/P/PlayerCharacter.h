#pragma once

#include "../B/BSPointerHandle.h"
#include "../B/BSSoundHandle.h"
#include "../B/BSTArray.h"
#include "../B/BSTEvent.h"
#include "../B/BSTHashMap.h"
#include "../B/BSTList.h"
#include "../B/BSTSmartPointer.h"
#include "../B/BSTTuple.h"
#include "../C/Character.h"
#include "../C/Crime.h"
#include "../F/FormTypes.h"
#include "../H/hkRefPtr.h"
#include "../N/NiPoint3.h"
#include "../N/NiSmartPointer.h"
#include "../N/NiTMap.h"
#include "../P/PositionPlayerEvent.h"

namespace ConsoleRE
{
	class Actor;
	class BGSInstancedQuestObjective;
	class BGSLocation;
	class bhkMouseSpringAction;
	class BipedAnim;
	class BSFadeNode;
	class BSLight;
	class CombatGroup;
	class ImageSpaceModifierInstanceDOF;
	class InventoryEntryData;
	class MenuModeChangeEvent;
	class MenuOpenCloseEvent;
	class NiAVObject;
	class NiNode;
	class ObjectListItem;
	class TESObject;
	class TESObjectREFR;
	class TintMask;
	class UserEventEnabledEvent;
	struct BGSActorCellEvent;
	struct BGSActorDeathEvent;
	struct PerkRankData;
	struct PositionPlayerEvent;
	struct TESQuestStageItem;
	struct TESTrackedStatsEvent;

	enum PLAYER_ACTION
	{
		kNone = 0,
		kSwingMeleeWeapon,
		kCastProjectileSpell,
		kShootBow,
		kZKeyObject,
		kJumping,
		kKnockingOverObjects,
		kStandOnTableChair,
		kIronSights,
		kDestroyObject,
		kLockedObject,
		kPickpocket,
		kCastSelfSpell,
		kShout,
		kActorCollision,
		kTotal,
		kInvalidMarker
	};

	struct CrimeGoldStruct
	{
	public:
		float violentCur;
		float nonViolentCur;
		float nonViolentInfamy;
		float violentInfamy;
	};
	static_assert(sizeof(CrimeGoldStruct) == 0x10);

	struct StolenItemValueStruct
	{
	public:
		int32_t unwitnessed;
		int32_t witnessed;
	};
	static_assert(sizeof(StolenItemValueStruct) == 0x8);

	struct FriendshipFactionsStruct
	{
	public:
		uint16_t friendCounts[4];
	};
	static_assert(sizeof(FriendshipFactionsStruct) == 0x8);

	class PLAYER_TARGET_LOC
	{
	public:
		using ArrivalFunc_t = void(int64_t);
	public:
		TESWorldSpace* world;
		TESObjectCELL* interior;
		NiPoint3       location;
		NiPoint3       angle;
		ArrivalFunc_t* arrivalFunc;
		int64_t		   arrivalFuncData;
		uint32_t       furnitureRef;
		uint32_t       fastTravelMarker;
		bool           resetWeather;
		bool           allowAutoSave;
		bool           isValid;
		uint8_t		   pad43;
		uint32_t	   pad44;
	};
	static_assert(sizeof(PLAYER_TARGET_LOC) == 0x48);

	struct PlayerActionObject
	{
	public:
		float       timer;
		uint32_t	refObj;
		uint32_t	next;
	};
	static_assert(sizeof(PlayerActionObject) == 0xC);

	class PlayerCharacter : 
		public Character, 
		public BSTEventSource<BGSActorCellEvent>, 
		public BSTEventSource<BGSActorDeathEvent>, 
		public BSTEventSource<PositionPlayerEvent>, 
		public BSTEventSink<MenuOpenCloseEvent>, 
		public BSTEventSink<MenuModeChangeEvent>, 
		public BSTEventSink<UserEventEnabledEvent>, 
		public BSTEventSink<TESTrackedStatsEvent>
	{
	public:
		static constexpr int TypeID = 62;

		enum class EventType
		{
			kThief = 3,
			kContainer = 5,
			kDeadBody = 6
		};

		enum class GrabbingType
		{
			kNone = 0,
			kNormal,
			kTelekinesis,
		};

		enum class ByCharGenFlag
		{
			kNone = 0,
			kHandsBound = 1 << 2
		};

		enum class FlagBD9
		{
			kNone = 0,
			kIsSleeping = 1 << 2,
			kGreetingPlayer = 1 << 6
		};

		enum class FlagBDB
		{
			kNone = 0,
			kIsInCombat = 1 << 5
		};

		enum class FlagBDC
		{
			kNone = 0,
			kHealthTutorialShown = 1 << 3,
			kMagickaTutorialShown = 1 << 4,
			kStaminaTutorialShown = 1 << 5,
			kGoToJailQueued = 1 << 6
		};

		enum class FlagBDD
		{
			kNone = 0,
			kSprinting = 1 << 0,
			kDragonRideTargetLocked = 1 << 2,
			kEverModded = 1 << 3,
			kServingJailTime = 1 << 4
		};

		struct Data860
		{
		public:
			BSTArray<UnkValue> unk00;
			BSTArray<UnkValue> unk10;
			uint64_t		   unk20;
			uint64_t		   unk28;
			uint64_t		   unk30;
		};
		static_assert(sizeof(Data860) == 0x38);

		struct PlayerSkills
		{
		public:
			struct Data
			{
			public:
				enum Skill : uint32_t
				{
					kOneHanded = 0,
					kTwoHanded = 1,
					kArchery = 2,
					kBlock = 3,
					kSmithing = 4,
					kHeavyArmor = 5,
					kLightArmor = 6,
					kPickpocket = 7,
					kLockpicking = 8,
					kSneak = 9,
					kAlchemy = 10,
					kSpeech = 11,
					kAlteration = 12,
					kConjuration = 13,
					kDestruction = 14,
					kIllusion = 15,
					kRestoration = 16,
					kEnchanting = 17,
					kTotal
				};
			
				struct SkillData
				{
				public:
					float level;
					float xp;
					float levelThreshold;
				};
				static_assert(sizeof(SkillData) == 0xC);
			public:
				float		xp;
				float		levelThreshold;
				SkillData   skills[Skill::kTotal];
				uint32_t	legendaryLevels[Skill::kTotal];
			};
			static_assert(sizeof(Data) == 0x128);
		public:
			int32_t		ResolveAdvancedSkillId(int32_t a_value);
			float		GetSkillPoints(BSFixedString a_value, bool a_legendary = false);
			void		SetSkillPoints(BSFixedString a_actorValue, float a_value, bool a_legendary = false);
			void		SetLevel(uint32_t a_level);
			void		IncrementLegendary(uint32_t a_actorvalue);
			uint32_t	GetSkillData(uint32_t a_actorvalue, float& a_unk3, float& a_unk4, float& a_unk5, float& a_unk6);
		public:
			Data* data;
		};
		static_assert(sizeof(PlayerSkills) == 0x8);
	public:
		~PlayerCharacter() override;
		
		static PlayerCharacter*  GetSingleton();

		void                     ActivatePickRef();
		void					 AddSkillExperience(uint32_t a_actorValue, float a_points);
		bool                     AttemptPickpocket(TESObjectREFR* a_containerRef, InventoryEntryData* a_entry, int32_t a_number, bool a_fromContainer = true);
		bool					 CenterOnCell(const char* a_cellName);
		bool					 CenterOnCell(TESObjectCELL* a_cell);
		NiPointer<Actor>         GetActorDoingPlayerCommand() const;
		float					 GetArmorValue(InventoryEntryData* a_form);
		float					 GetDamage(InventoryEntryData* a_form);
		NiPointer<TESObjectREFR> GetGrabbedRef();
		uint32_t				 GetNumTints(uint32_t a_tintType);
		TintMask*				 GetOverlayTintMask(TintMask* a_original);
		BSTArray<TintMask*>&	 GetTintList();
		TintMask*				 GetTintMask(uint32_t a_tintType, uint32_t a_index);
		bool					 HasActorDoingCommand();
		bool					 IsGrabbing();
		void					 PlayPickupEvent(TESForm* a_item, TESForm* a_containerOwner, TESObjectREFR* a_containerRef, uint32_t a_eventType);
		void					 StartGrabObject();
	
		//
		static uint32_t			 UpdatePlayerTints();
	protected:
		bool CenterOnCell_Impl(const char* a_cellName, TESObjectCELL* a_cell);
	public:
		void*													 Unk3A0;
		uint32_t												 Unk3A8;
		uint32_t												 Unk3AC;
		BSTHashMap<const TESFaction*, CrimeGoldStruct>			 Unk3B0;
		BSTHashMap<const TESFaction*, StolenItemValueStruct>     Unk3D0;
		uint32_t												 Unk3F0;
		uint32_t												 Unk3F4;
		BSTHashMap<const TESFaction*, FriendshipFactionsStruct>	 Unk3F8;
		NiPoint3												 lastKnownGoodPosition;
		NiPoint3												 bulletAutoAim;
		NiPoint3												 cachedVelocity;
		float													 Unk43C;
		void*													 Unk440;
		void*													 Unk448;
		BSTArray<void*>											 addedPerks;
		BSTArray<BGSPerk*>										 perks;
		BSTArray<BGSPerk*>										 standingStonePerks;
		BSTArray<uint32_t>										 currentMapMarkers;
		BSTArray<BSTTuple<NiPoint3, AITimeStamp>>				 velocityArray;
		BSTArray<uint32_t>										 runesCast;
		BSTArray<void*>											 imageSpaceModifierAnims1;
		BSTArray<void*>											 imageSpaceModifierAnims2;
		BSSimpleList<TESQuestStageItem*>						 questlog;
		BSTArray<void*>											 objectives;
		BSTHashMap<UnkValue, UnkKey>							 Unk4F0;
		BSTHashMap<UnkValue, UnkKey>							 Unk510;
		BSSimpleList<uint32_t>									 droppedRefList;
		NiTMap<uint32_t, uint8_t>								 randomDoorSpaceMap;
		TESWorldSpace*											 cachedWorldSpace;
		NiPoint3												 exteriorPosition;
		uint32_t												 Unk574;
		PLAYER_TARGET_LOC										 queuedTargetLoc;
		BSSoundHandle											 Unk5C0;
		BSSoundHandle											 Unk5CC;
		BSSoundHandle											 Unk5D8;
		uint32_t												 Unk5E4;
		void*													 Unk5E8;
		uint32_t												 Unk5F0;
		uint32_t												 Unk5F4;
		void*													 Unk5F8;
		uint32_t												 Unk600;
		float													 Unk604;
		int32_t													 Unk608;
		float													 Unk60C;
		float													 Unk610;
		int32_t													 Unk614;
		ImageSpaceModifierInstanceDOF*							 Unk618;
		ImageSpaceModifierInstanceDOF*							 Unk620;
		ImageSpaceModifierInstanceDOF*							 Unk628;
		float													 Unk630;
		bool													 Unk634;
		uint8_t													 Unk635;
		uint16_t												 Unk636;
		NiPoint3												 dynamicDOFLastAngle;
		NiPoint3												 dynamicDOFLastPosition;
		void*													 Unk650;
		int32_t													 Unk658;
		int32_t													 Unk65C;
		void*													 Unk660;
		uint8_t													 Unk668[0xA0];
		int32_t													 Unk708;
		int32_t													 Unk70C;
		int32_t													 Unk710;
		PlayerActionObject										 Unk714[15];
		int32_t													 Unk7C8;
		int32_t													 Unk7CC;
		uint8_t													 Unk7D0[0x30];
		int32_t													 Unk800;
		float													 Unk804;
		float													 Unk808;
		float													 Unk80C;
		uint64_t												 Unk810;
		uint32_t												 Unk818;
		uint32_t												 Unk81C;
		BSTSmartPointer<BipedAnim>								 Unk820;
		NiPointer<NiNode>										 Unk828;
		float													 Unk830;
		float													 Unk834;
		float													 Unk838;
		float													 Unk83C;
		int32_t													 Unk840;
		int32_t													 Unk844;
		int32_t													 Unk848;
		int32_t													 Unk84C;
		int32_t													 Unk850;
		float													 Unk854;
		float													 Unk858;
		int32_t													 Unk85C;
		Data860*												 Unk860;
		int32_t													 Unk864;
		int32_t													 Unk868;
		void*													 Unk870;
		void*													 Unk878;
		uint32_t												 Unk880[7];
		uint32_t												 Unk89C;
		AlchemyItem*											 Unk8A0;
		int64_t													 Unk8A8;
		int64_t													 Unk8B0;
		uint64_t												 Unk8B8;
		TESForm*												 Unk8C0;
		uint32_t												 Unk8C8;
		uint32_t												 Unk8CC;
		void*													 Unk8D0;
		void*													 Unk8D8;
		float													 Unk8E0;
		float													 Unk8E4;
		PlayerSkills*											 Unk8E8;
		int32_t													 Unk8F0;
		int32_t													 Unk8F4;
		void*													 Unk8F8;
		void*													 Unk900;
		void*													 Unk908;
		BSTArray<void*>											 Unk910;
		void*													 Unk920;
		TESBoundObject*											 Unk928[2];
		uint32_t												 Unk938;
		float													 Unk93C;
		float													 Unk940;
		float													 Unk944;
		float													 Unk948;
		uint32_t												 Unk94C;
		uint8_t													 Unk950[0xA0];
		uint32_t												 Unk9F0;
		uint32_t												 Unk9F4;
		BGSLocation*											 Unk9F8;
		float													 UnkA00;
		float													 UnkA04;
		float													 UnkA08;
		uint32_t												 UnkA0C;
		void*													 UnkA10;
		uint32_t												 UnkA18;
		uint32_t												 UnkA1C;
		uint32_t												 UnkA20;
		uint32_t												 UnkA24;
		uint32_t												 UnkA28;
		uint32_t												 UnkA2C;
		uint8_t													 UnkA30;
		uint8_t													 UnkA31; // perk points
		uint8_t													 UnkA32;
		uint8_t													 UnkA33;
		uint32_t												 UnkA34;
		void*													 UnkA38;
		BSTArray<TintMask*>										 UnkA40;
		BSTArray<TintMask*>*									 UnkA50;
		BGSTextureSet*											 UnkA58;
		TESRace*												 UnkA60;
		TESRace*												 UnkA68;
		int32_t													 UnkA70;
		int32_t													 UnkA74;
		BSTArray<void*>											 UnkA78;
		void*													 UnkA88;
		void*													 UnkA90;
		void*													 UnkA98;
		void*													 UnkAA0;
		int32_t													 UnkAA8;
		int32_t													 UnkAAC;
		void*													 UnkAB0;
		void*													 UnkAB8;
		BSTSmallArray<void*, 4>									 UnkAC0;
		void*													 UnkAF0;
		uint32_t												 UnkAF8;
		uint8_t													 UnkAFC;
		uint8_t													 UnkAFD;
		uint8_t													 UnkAFE;
		uint8_t													 UnkAFF;
	};
	static_assert(offsetof(PlayerCharacter, Unk8E8) == 0x8E8);
	static_assert(offsetof(PlayerCharacter, UnkA31) == 0xA31);
	static_assert(offsetof(PlayerCharacter, Unk920) == 0x920);
	static_assert(offsetof(PlayerCharacter, Unk910) == 0x910);
	static_assert(offsetof(PlayerCharacter, Unk714) == 0x714);
	static_assert(sizeof(PlayerCharacter) == 0xB00);
}