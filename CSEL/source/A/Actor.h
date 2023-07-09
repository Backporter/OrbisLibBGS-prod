#pragma once

#include "../A/AITimeStamp.h"
#include "../A/ActiveEffect.h"
#include "../A/ActorState.h"
#include "../A/ActorValueOwner.h"
#include "../A/ActorValues.h"
#include "../B/BGSBipedObjectForm.h"
#include "../B/BGSEntryPointPerkEntry.h"
#include "../B/BSPointerHandle.h"
// #include "../B/BSPointerHandleSmartPointer.h"
#include "../B/BSTArray.h"
#include "../B/BSTEvent.h"
#include "../B/BSTList.h"
#include "../B/BSTSmartPointer.h"
#include "../B/BSTTuple.h"
#include "../D/DetectionPriorities.h"
#include "../F/FormTypes.h"
#include "../I/IPostAnimationChannelUpdateFunctor.h"
#include "../M/MagicSystem.h"
#include "../M/MagicTarget.h"
#include "../N/NiSmartPointer.h"
#include "../T/TESNPC.h"
#include "../T/TESObjectREFR.h"

#include <pthread.h>

namespace ConsoleRE
{
	class ActorMagicCaster;
	class ActorMover;
	class AIProcess;
	class bhkCharacterController;
	class bhkCharacterMoveFinishEvent;
	class BipedAnim;
	class BSTransformDeltaEvent;
	class CombatController;
	class CombatGroup;
	class ExtraDataList;
	class InventoryEntryData;
	class MovementControllerNPC;
	class MovementMessageActorCollision;
	class NiRefObject;
	class PackageLocation;
	class PerkEntryVisitor;
	struct ActorMotionFeedbackData;
	struct ActorMotionFeedbackOutput;

	class Actor : 
		public TESObjectREFR, 
		public MagicTarget, 
		public ActorValueOwner, 
		public ActorState,
		public BSTEventSink<BSTransformDeltaEvent>, 
		public BSTEventSink<bhkCharacterMoveFinishEvent>, 
		public IPostAnimationChannelUpdateFunctor
	{
	public:
		struct SlotTypes
		{
			enum
			{
				kLeftHand = 0,
				kRightHand,
				kUnknown,
				kPowerOrShout,
				kTotal
			};
		};

		struct BOOL_BITS
		{
			enum
			{
				kNone = 0,
				kDelayUpdateScenegraph = 1 << 0,
				kProcessMe = 1 << 1,
				kMurderAlarm = 1 << 2,
				kHasSceneExtra = 1 << 3,
				kHeadingFixed = 1 << 4,
				kSpeakingDone = 1 << 5,
				kIgnoreChangeAnimationCall = 1 << 6,
				kSoundFileDone = 1 << 7,
				kVoiceFileDone = 1 << 8,
				kInTempChangeList = 1 << 9,
				kDoNotRunSayToCallback = 1 << 10,
				kDead = 1 << 11,
				kForceGreetingPlayer = 1 << 12,
				kForceUpdateQuestTarget = 1 << 13,
				kSearchingInCombat = 1 << 14,
				kAttackOnNextTheft = 1 << 15,
				kEvpBuffered = 1 << 16,
				kResetAI = 1 << 17,
				kInWater = 1 << 18,
				kSwimming = 1 << 19,
				kVoicePausedByScript = 1 << 20,
				kWasInFrustrum = 1 << 21,
				kShouldRotateToTrack = 1 << 22,
				kSetOnDeath = 1 << 23,
				kDoNotPadVoice = 1 << 24,
				kFootIKInRange = 1 << 25,
				kPlayerTeammate = 1 << 26,
				kGivePlayerXP = 1 << 27,
				kSoundCallbackSuccess = 1 << 28,
				kUseEmotion = 1 << 29,
				kGuard = 1 << 30,
				kParalyzed = 1 << 31
			};
		};

		struct BOOL_FLAGS
		{
			enum
			{
				kNone = 0,
				kScenePackage = 1 << 0,
				kIsAMount = 1 << 1,
				kMountPointClear = 1 << 2,
				kGettingOnOffMount = 1 << 3,
				kInRandomScene = 1 << 4,
				kNoBleedoutRecovery = 1 << 5,
				kInBleedoutAnimation = 1 << 6,
				kCanDoFavor = 1 << 7,
				kShouldAnimGraphUpdate = 1 << 8,
				kCanSpeakToEssentialDown = 1 << 9,
				kBribedByPlayer = 1 << 10,
				kAngryWithPlayer = 1 << 11,
				kIsTrespassing = 1 << 12,
				kCanSpeak = 1 << 13,
				kIsInKillMove = 1 << 14,
				kAttackOnSight = 1 << 15,
				kIsCommandedActor = 1 << 16,
				kForceOneAnimgraphUpdate = 1 << 17,
				kEssential = 1 << 18,
				kProtected = 1 << 19,
				kAttackingDisabled = 1 << 20,
				kCastingDisabled = 1 << 21,
				kSceneHeadTrackRotation = 1 << 22,
				kForceIncMinBoneUpdate = 1 << 23,
				kCrimeSearch = 1 << 24,
				kMovingIntoLoadedArea = 1 << 25,
				kDoNotShowOnStealthMeter = 1 << 26,
				kMovementBlocked = 1 << 27,
				kAllowInstantFurniturePopInPlayerCell = 1 << 28,
				kForceAnimGraphUpdate = 1 << 29,
				kCheckAddEffectDualCast = 1 << 30,
				kUnderwater = 1 << 31
			};
		};

		struct Modifiers
		{
		public:
			float modifiers[3];
		};
		static_assert(sizeof(Modifiers) == 0xC);

		struct ActorValuesStorage
		{
		public:
			template <typename T>
			struct Entry
			{
			public:
				BSFixedString value;
				T* entries;
			};
		public:
			Entry<float> base;
			Entry<Modifiers> modifiers;
		};
		static_assert(sizeof(ActorValuesStorage) == 0x20);
	public:
		static constexpr int TypeID = 62;
	public:
		~Actor() override;

		// override (TESObjectREFR)
		void                    Predestroy() override;
		bool					GetEditorLocation(NiPoint3& a_outPos, NiPoint3& a_outRot, TESForm*& a_outWorldOrCell, TESObjectCELL* a_fallback) override;
		void                    ForceEditorLocation(BGSLocation* a_location) override;
		void                    Update3DPosition(bool a_warp) override;
		void                    UpdateSoundCallBack(bool a_endSceneAction) override;
		bool                    SetDialogueWithPlayer(bool a_flag, bool a_forceGreet, TESTopicInfo* a_topic) override;
		BGSAnimationSequencer*  GetSequencer(void) override;
		bool                    HasKeywordHelper(const BGSKeyword* a_keyword) const override;
		TESPackage*             CheckForCurrentAliasPackage() override;
		BGSScene*               GetCurrentScene() override;
		void                    SetCurrentScene(BGSScene* a_scene) override;
		bool                    UpdateInDialogue(DialogueResponse* a_response, bool a_unused) override;
		BGSDialogueBranch*      GetExclusiveBranch() override; 
		void                    SetExclusiveBranch(BGSDialogueBranch* a_branch) override;
		void                    PauseCurrentDialogue(void) override;
		NiPoint3                GetStartingAngle() override;
		NiPoint3                GetStartingLocation() override;
		uint32_t*				RemoveItem(TESBoundObject* a_item, int32_t a_count, ITEM_REMOVE_REASON a_reason, ExtraDataList* a_extraList, TESObjectREFR* a_moveToRef, const NiPoint3* a_dropLoc = 0, const NiPoint3* a_rotate = 0) override;
		bool                    AddWornItem(TESBoundObject* a_item, int32_t a_count, bool a_forceEquip, uint32_t a_arg4, uint32_t a_arg5) override;
		void                    DoTrap1(TrapData& a_data) override;
		void                    DoTrap2(TrapEntry* a_trap, TargetEntry* a_target) override;
		void                    AddObjectToContainer(TESBoundObject* a_object, ExtraDataList* a_extraList, int32_t a_count, TESObjectREFR* a_fromRefr) override;
		NiPoint3                GetLookingAtLocation() override;
		MagicCaster*            GetMagicCaster(MagicSystem::CastingSource a_source) override;
		MagicTarget*            GetMagicTarget() override;
		bool                    IsChild() override;
		BSFaceGenAnimationData* GetFaceGenAnimationData() override;
		bool                    DetachHavok(NiAVObject* a_obj3D) override;
		void                    InitHavok() override;
		void					TESObjectREFR_Unk_45() override;
		void					TESObjectREFR_Unk_46() override;
		void					TESObjectREFR_Unk_47() override;
		NiAVObject*             Load3D(bool a_arg1) override;
		void                    Set3D(NiAVObject* a_object, bool a_queue3DTasks = true) override;
		bool                    PopulateGraphProjectsToLoad(void) override;
		NiPoint3                GetBoundMin() override;
		NiPoint3                GetBoundMax() override;
		BSEventNotifyControl	ProcessEvent(const BSAnimationGraphEvent*, BSTEventSource<BSAnimationGraphEvent>*) override;
		void                    ModifyAnimationUpdateData(BSAnimationUpdateData& a_data) override;
		bool					ShouldSaveAnimationOnUnloading() override;
		bool					ShouldSaveAnimationOnSaving() override;
		bool					ShouldPerformRevert() override;
		void					UpdateAnimation(float a_delta) override;
		void					TESObjectREFR_Unk_80() override;
		void					SetObjectReference(TESBoundObject* a_object) override;
		void					MoveHavok(bool a_forceRec) override;
		void					GetLinearVelocity(NiPoint3& a_velocity) const override;
		void					SetActionComplete(bool a_set) override;
		void					Disable() override;
		void					ResetInventory(bool a_leveledOnly) override;
		void					TESObjectREFR_Unk_89() override;
		void					TESObjectREFR_Unk_90() override;
		bool					OnAddCellPerformQueueReference(TESObjectCELL& a_cell) const override;
		void					DoMoveToHigh() override;
		void					TryMoveToMiddleLow() override;
		bool					TryChangeSkyCellActorsProcessLevel() override;
		void					TESObjectREFR_Unk_99() override;
		void					TESObjectREFR_Unk_100() override;
		void					TESObjectREFR_Unk_101() override;
		void					SetParentCell(TESObjectCELL* a_cell) override;
		bool					IsDead(bool a_notEssential = true) override;
		void					TESObjectREFR_Unk_107() override;
		void					TESObjectREFR_Unk_108() override;
		TESAmmo*				GetCurrentAmmo() override;
		void					UnequipItem(uint64_t a_arg1, TESBoundObject* a_object) override;

		// add
		virtual void			Actor_Unk_02();
		virtual void			PlayPickUpSound(TESBoundObject* a_object, bool a_pickup, bool a_use);
		virtual float			GetHeading(bool a_ignoreRaceSettings) const;
		virtual void			SetAvoidanceDisabled(bool a_set);
		virtual void			DrawWeaponMagicHands(bool a_draw);
		virtual void			Actor_Unk_07();
		virtual void			Actor_Unk_08();
		virtual void            SetPosition(const NiPoint3& a_pos, bool a_updateCharController);
		virtual void            KillDying();
		virtual void            Resurrect(bool a_resetInventory, bool a_attach3D);
		virtual bool            PutActorOnMountQuick();
		virtual void            Update(float a_delta);
		virtual void            UpdateNoAI(float a_delta);
		virtual void            UpdateCharacterControllerSimulationSettings(bhkCharacterController& a_controller);
		virtual void            PotentiallyFixRagdollState();
		virtual void            UpdateNonRenderSafe(float a_delta);
		virtual void            OnItemEquipped(bool a_playAnim);
		virtual void			Actor_Unk_19();
		virtual void			Actor_Unk_20();
		virtual void            SetCrimeGoldValue(TESFaction* a_faction, bool a_violent, uint32_t a_amount);
		virtual void            ModCrimeGoldValue(TESFaction* a_faction, bool a_violent, int32_t a_amount);
		virtual void            RemoveCrimeGoldValue(TESFaction* a_faction, int32_t a_amount, bool a_violent);
		virtual uint32_t		CrimeGoldValue(const TESFaction* a_faction) const;
		virtual void            GoToPrison(TESFaction* a_faction, bool a_removeInventory, bool a_realJail);
		virtual void            ServePrisonTime();
		virtual void            PayFine(TESFaction* a_faction, bool a_goToJail, bool a_removeStolenItems);
		virtual bool            GetCannibal();
		virtual void            SetCannibal(bool a_set);
		virtual bool            GetVampireFeed();
		virtual void            SetVampireFeed(bool a_set);
		virtual void            InitiateVampireFeedPackage(Actor* a_target, TESObjectREFR* a_furniture);
		virtual void            InitiateCannibalPackage(Actor* a_target);
		virtual void            GetEyeVector(NiPoint3& a_origin, NiPoint3& a_direction, bool a_includeCameraOffset);
		virtual void            SetRefraction(bool a_enable, float a_refraction);
		virtual void			Actor_Unk_36();
		virtual void			Actor_Unk_37();
		virtual void			Actor_Unk_38() = 0;
		virtual float           GetAcrobatics() const;
		virtual void			Actor_Unk_40();
		virtual void			Actor_Unk_41();
		virtual void            OnArmorActorValueChanged();
		virtual uint32_t*		pObject(const TESBoundObject* a_object, ExtraDataList* a_extraList, int32_t a_count, const NiPoint3* a_dropLoc = 0, const NiPoint3* a_rotate = 0);
		virtual void            PickUpObject(TESObjectREFR* a_object, int32_t a_count, bool a_arg3 = false, bool a_playSound = true);
		virtual void            AttachArrow(const BSTSmartPointer<BipedAnim>& a_biped);
		virtual void            DetachArrow(const BSTSmartPointer<BipedAnim>& a_biped);
		virtual bool            AddShout(TESShout* a_shout);
		virtual void			Actor_Unk_48();
		virtual void			Actor_Unk_49();
		virtual uint32_t        UseAmmo(uint32_t a_shotCount);
		virtual bool            CalculateCachedOwnerIsInCombatantFaction() const;
		virtual CombatGroup*    GetCombatGroup() const;
		virtual void            SetCombatGroup(CombatGroup* a_group);
		virtual bool            CheckValidTarget(TESObjectREFR& a_target);
		virtual void			Actor_Unk_55();
		virtual void            InitiateDialogue(Actor* a_target, PackageLocation* a_loc1, PackageLocation* a_loc2);
		virtual void			Actor_Unk_57();
		virtual void            EndDialogue();
		virtual Actor*          SetUpTalkingActivatorActor(Actor* a_target, Actor*& a_activator);
		virtual void			Actor_Unk_60();
		virtual void            InitiateFlee(TESObjectREFR* a_fleeRef, bool a_runOnce, bool a_knows, bool a_combatMode, TESObjectCELL* a_cell, TESObjectREFR* a_ref, float a_fleeFromDist, float a_fleeToDist);
		virtual void            InitiateGetUpPackage();
		virtual void            PutCreatedPackage(TESPackage* a_package, bool a_tempPackage, bool a_createdPackage, bool a_allowFromFurniture);
		virtual void            UpdateAlpha();
		virtual void            SetAlpha(float a_alpha = 1.0);
		virtual float           GetAlpha();
		virtual bool            IsInCombat() const;
		virtual void            UpdateCombat();
		virtual void            StopCombat();

		void					SwapHeadPart(BGSHeadPart* a_old, BGSHeadPart* a_new);
		void					EvaluatePackage(bool a_immediate, bool a_resetAI);
		void					DoReset3D(bool a_updateWeight);
		bool					IsOnMount();
		bool					IsAMount();
		bool					IsEssential();
		bool                    IsHostileToActor(Actor* a_actor);
		bhkCharacterController*	GetCharController();
		bool					IsAnimationDriven();
		void					InterruptCast(bool a_restoreMagicka);
		bool					IsBlocking();
		bool					IsCasting(MagicItem* a_spell);
		bool					HasPerk(BGSPerk* a_perk);
		bool					HasLineOfSight(TESObjectREFR* a_ref, bool& a_arg2);

		void					StealAlarm(TESObjectREFR* a_ref, TESForm* a_object, int32_t a_num, int32_t a_total, TESForm* a_owner, bool a_allowWarning);
		int32_t					RequestDetectionLevel(Actor* a_target, uint32_t a_priority);
		void					UpdateWeaponAbility(TESForm* a_weapon, ExtraDataList* a_extraData, bool a_leftHand);
		void					UpdateArmorAbility(TESForm* a_armor, ExtraDataList* a_extraData);
		void					SetRotationZ(float a_angle);
		void					SetRotationX(float a_angle);
		bool					AddSpell(SpellItem* a_spell);
		bool					RemoveSpell(SpellItem* a_spell);
		TESNPC*					GetActorBase();
		const TESNPC*			GetActorBase() const;
		TESRace*				GetRace();
		bool					AddAnimationGraphEventSink(BSTEventSink<BSAnimationGraphEvent>* a_sink);
		TESForm*				GetEquippedObject(bool a_left);
		void					UpdateHairColor();
		void					UpdateSkinColor();
		bool					VisitFactions(std::function<bool(TESFaction*, int8_t)> a_visitor);
	public:
		uint32_t					boolBits;
		float						updateTargetTimer;
		uint32_t					criticalStage;
		uint32_t					UnkFC;
		AIProcess*					currentProcess;
		uint32_t					dialogueItemTarget;
		uint32_t					currentCombatTarget;
		uint32_t					myKiller;
		float						checkMyDeadBodyTimer;
		float						voiceTimer;
		float						underWaterTimer;
		uint32_t					thiefCrimeStamp;
		uint32_t					actionValue;
		float						timerOnAction;
		uint32_t					Unk12C;
		NiPoint3                    editorLocCoord;
		float						editorLocRot;
		TESForm*                    editorLocForm;
		BGSLocation*				editorLocation;
		ActorMover*					actorMover;
		MovementControllerNPC*		movementController;
		void*						Unk160;
		CombatController*			combatController;
		TESFaction*					vendorFaction;
		float						calculateVendorFactionTimer;
		uint32_t					Unk17C;
		uint32_t					Unk180;
		uint32_t					Unk184;
		uint32_t					Unk188;
		uint32_t					intimidateBribeDayStamp;
		uint64_t					Unk190;
		BSTSmallArray<SpellItem*>   addedSpells;
		ActorMagicCaster*			magicCasters[4];
		SpellItem*					selectedSpells[4];
		TESForm*					selectedPower;
		uint32_t					Unk1F8;
		uint32_t					Unk1FC;
		TESRace*					race;
		uint32_t					Unk218;
		uint32_t					boolFlags;
		ActorValuesStorage			avStorage;
		BGSDialogueBranch*          exclusiveBranch;
		Modifiers					modifiers[4];
		float						lastUpdate;
		uint32_t                    lastSeenTime;
		void*						biped;
		float                       armorRating;
		float                       armorBaseFactorSum;
		int8_t                      soundCallBackSet;
		uint8_t                     unk281;
		uint8_t                     unk282;
		uint8_t                     unk283;
		uint32_t                    unk284;
		uint64_t                    unk288;
		uint64_t                    unk290;
		pthread_mutex_t             unk298;
		uint64_t					Unk2A0;
	};
	static_assert(offsetof(Actor, magicCasters)   == 0x1B0);
	static_assert(offsetof(Actor, addedSpells)    == 0x198);
	static_assert(offsetof(Actor, actorMover)     == 0x150);
	static_assert(offsetof(Actor, currentProcess) == 0x100);
	static_assert(sizeof(Actor) == 0x2A8);
}