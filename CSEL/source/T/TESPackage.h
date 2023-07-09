#pragma once

#include "../T/TESForm.h"

namespace ConsoleRE
{
	class BGSIdleCollection;
	class PackageLocation;
	class TESPackageData;

	struct PACKAGE_DATA
	{
	public:
		enum class GeneralFlag
		{
			kNone = 0,
			kOffersServices = 1 << 0,
			kMustComplete = 1 << 2,
			kMaintainSpeedAtGoal = 1 << 3,
			kUnlocksDoorsAtPackageStart = 1 << 6,
			kUnlocksDoorsAtPackageEnd = 1 << 7,
			kContinueIfPCNear = 1 << 9,
			kOncePerDay = 1 << 10,
			kPreferredSpeed = 1 << 13,
			kAlwaysSneak = 1 << 17,
			kAllowSwimming = 1 << 18,
			kIgnoreCombat = 1 << 20,
			kWeaponsUnequipped = 1 << 21,
			kWeaponDrawn = 1 << 23,
			kNoCombatAlert = 1 << 27,
			kWearSleepOutfit = 1 << 29
		};

		enum class PreferredSpeed
		{
			kWalk = 0,
			kJog = 1,
			kRun = 2,
			kFastWalk = 3
		};

		enum class InterruptFlag
		{
			kNone = 0,
			kHellosToPlayer = 1 << 0,
			kRandomConversations = 1 << 1,
			kObserveCombatBehaviour = 1 << 2,
			kGreetCorpseBehaviour = 1 << 3,
			kReactionToPlayerActions = 1 << 4,
			kFriendlyFireComments = 1 << 5,
			kAggroRadiusBehavior = 1 << 6,
			kAllowIdleChatter = 1 << 7,
			kWorldInteractions = 1 << 9
		};
	public:
		uint32_t			packFlags;
		uint8_t				packType;
		uint8_t				interruptOverrideType;
		uint8_t				maxSpeed;
		uint8_t             pad7;
		uint16_t			foBehaviorFlags;
		uint16_t            packageSpecificFlags;
	};
	static_assert(sizeof(PACKAGE_DATA) == 0xC);

	class PackageTarget
	{
	public:
		union Target
		{
		public:
			Target() : object(nullptr) {}
			~Target() = default;
		public:
			uint32_t												handle;
			TESForm*												object;
			TESForm*												refOrObj;
			uint32_t												objType;
			uint32_t												aliasID;
			uint32_t												interruptTarg;
		};
		static_assert(sizeof(Target) == 0x8);
	public:
		int8_t   targType;
		uint8_t  pad01;
		uint16_t pad02;
		Target   target;
		int32_t  value;
		uint32_t pad14;
	};
	static_assert(sizeof(PackageTarget) == 0x18);

	struct PACK_SCHED_DATA
	{
	public:
		enum class DayOfWeek
		{
			kAny = -1,
			kSunday = 0,
			kMonday = 1,
			kTuesday = 2,
			kWednesday = 3,
			kThursday = 4,
			kFriday = 5,
			kSaturday = 6,
			kWeekdays = 7,
			kWeekends = 8,
			kMondayWednesdayFriday = 9,
			kTuesdayThursday = 10
		};
	public:
		int8_t                              month;
		int8_t								dayOfWeek;
		int8_t                              date;
		int8_t                              hour;
		int8_t                              minute;
		uint8_t                             pad5;
		uint8_t                             pad6;
		uint8_t                             pad7;
		int32_t                             duration;
	};
	static_assert(sizeof(PACK_SCHED_DATA) == 0xC);

	class PackageSchedule
	{
	public:
		PACK_SCHED_DATA psData;
	};
	static_assert(sizeof(PackageSchedule) == 0xC);

	class PackageEventAction
	{
	public:
		struct TopicData
		{
		public:
			enum class Type
			{
				kTopicRef = 0,
				kTopicSubtype = 1
			};
		public:
			uint32_t	type;
			uint32_t    pad04;
			TESTopic*   topic;
		};
		static_assert(sizeof(TopicData) == 0x10);
	public:
		TESIdleForm*                                            idle;
		uint32_t												type;
		uint32_t												pad0C;
		TopicData                                               topic;
	};
	static_assert(sizeof(PackageEventAction) == 0x20);

	class TESPackage : public TESForm
	{
	public:
		static constexpr int TypeID = 79;
	public:
		~TESPackage() override;

		// override (TESForm)
		void                      InitializeData() override;
		void                      ClearData() override;
		bool                      Load(TESFile* a_mod) override;
		void                      SaveGame(BGSSaveFormBuffer* a_buf) override;
		void                      LoadGame(BGSLoadFormBuffer* a_buf) override;
		void                      Revert(BGSLoadFormBuffer* a_buf) override;
		void                      InitItemImpl() override;
		uint32_t				  GetRefCount() const override;
		const char*				  GetObjectTypeName() const override;

		// add
		virtual bool IsActorAtLocation(Actor* a_actor, bool a_arg2, float a_arg3, bool a_arg4);
		virtual bool IsActorAtSecondLocation(Actor* a_arg1, Actor* a_arg2, bool a_arg3, float a_arg4, bool a_arg5);
		virtual bool IsActorAtRefTarget(Actor* a_actor, int32_t a_arg2);
		virtual bool IsTargetAtLocation(Actor* a_actor, int32_t a_arg2);
		virtual bool IsPackageOwner(Actor* a_actor);
	public:
		PACKAGE_DATA                                            packData;
		uint32_t												pad2C;
		TESPackageData*                                         data;
		PackageLocation*                                        packLoc;
		PackageTarget*                                          packTarg;
		BGSIdleCollection*                                      idleCollection;
		PackageSchedule                                         packSched;
		uint32_t												pad5C;
		TESCondition                                            packConditions;
		TESCombatStyle*                                         combatStyle;
		TESQuest*                                               ownerQuest;
		PackageEventAction                                      onBegin;
		PackageEventAction                                      onEnd;
		PackageEventAction                                      onChange;
		uint32_t												procedureType;
		volatile uint32_t										refCount;
	};
}