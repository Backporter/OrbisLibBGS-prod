#pragma once

#include "../B/BSFixedString.h"
#include "../B/BSHandleRefObject.h"
#include "../B/BSTArray.h"
#include "../B/BSTEvent.h"
#include "../B/BSTList.h"
#include "../B/BSTSmartPointer.h"
#include "../E/ExtraDataList.h"
#include "../F/FormTypes.h"
#include "../I/IAnimationGraphManagerHolder.h"
#include "../M/MagicSystem.h"
#include "../N/NiPoint3.h"
#include "../N/NiSmartPointer.h"
#include "../T/TESForm.h"

#include <stdio.h>

namespace ConsoleRE
{
	class Actor;
	class ActorCause;
	class BGSAnimationSequencer;
	class BGSDialogueBranch;
	class BipedAnim;
	class BSAnimNoteReceiver;
	class BSFaceGenAnimationData;
	class BSFaceGenNiNode;
	class BSFlattenedBoneTree;
	class DialogueResponse;
	class Explosion;
	class InventoryChanges;
	class InventoryEntryData;
	class MagicCaster;
	class MagicTarget;
	class NiAVObject;
	class NiControllerManager;
	class NiControllerSequence;
	class NiNode;
	class NiObject;
	class Projectile;
	class TargetEntry;
	class TESActorBase;
	class TESBoundObject;
	class TESContainer;
	class TrapData;
	class TrapEntry;

	struct BGSDecalGroup;
	struct BSAnimationGraphEvent;
	struct BSAnimationUpdateData;
	struct REFR_LOCK;

	enum class ITEM_REMOVE_REASON
	{
		kRemove,
		kSteal,
		kSelling,
		kDropping,
		kStoreInContainer,
		kStoreInTeammate
	};

	struct OBJ_REFR
	{
	public:
		TESBoundObject* objectReference;
		NiPoint3        angle;
		NiPoint3        location;
	};
	static_assert(sizeof(OBJ_REFR) == 0x20);

	struct LOADED_REF_DATA
	{
	public:
		BSTArray<void*>		  Unk00;
		TESWaterForm*         currentWaterType;
		float                 relevantWaterHeight;
		float                 cachedRadius;
		uint16_t              flags;
		int16_t               underwaterCount;
		uint32_t              Unk24;
		uint64_t              Unk28;
		uint64_t              Unk30;
		uint64_t              Unk38;
		uint64_t              Unk40;
		uint64_t              Unk48;
		uint64_t              Unk50;
		uint64_t              Unk58;
		uint64_t			  Unk60;
		NiPointer<NiAVObject> data3D;
		void*                 Unk70;
	};
	static_assert(sizeof(LOADED_REF_DATA) == 0x78);

	class TESObjectREFR : public TESForm, public BSHandleRefObject, public BSTEventSink<BSAnimationGraphEvent>, public IAnimationGraphManagerHolder
	{
	public:
		static constexpr int TypeID = 61;

		enum class MotionType  // hkpMotion::MotionType
		{
			kDynamic = 1,
			kSphereInertia = 2,
			kBoxInertia = 3,
			kKeyframed = 4,
			kFixed = 5,
			kThinBoxInertia = 6,
			kCharacter = 7
		};

		struct ChangeFlags
		{
			enum ChangeFlag : uint32_t
			{
				kMoved = 1 << 1,
				kHavokMoved = 1 << 2,
				kCellChanged = 1 << 3,
				kScale = 1 << 4,
				kInventory = 1 << 5,
				kOwnershipExtra = 1 << 6,
				kBaseObject = 1 << 7,
				kItemExtraData = 1 << 10,
				kAmmoExtra = 1 << 11,
				kLockExtra = 1 << 12,
				kEmpty = 1 << 21,
				kOpenDefaultState = 1 << 22,
				kOpenState = 1 << 23,
				kPromoted = 1 << 25,
				kActivatingChildren = 1 << 26,
				kLeveledInventory = 1 << 27,
				kAnimation = 1 << 28,
				kEncZoneExtra = 1 << 29,
				kCreatedOnlyExtra = 1 << 30,
				kGameOnlyExtra = (uint32_t)1 << 31
			};
		};

		struct RecordFlags
		{
			enum RecordFlag : uint32_t
			{
				kIsGroundPiece = 1 << 4,
				kCollisionsDisabled = 1 << 4,  // ?

				kDeleted = 1 << 5,
				kHiddenFromLocalMap = 1 << 6,  // TESObjectSTAT
				kTurnOffFire = 1 << 7,

				kInaccessible = 1 << 8,            // TESObjectDOOR
				kLODRespectsEnableState = 1 << 8,  // TESObjectSTAT
				kStartsDead = 1 << 8,              // TESNPC
				kDoesntLightWater = 1 << 8,

				kMotionBlur = 1 << 9,  // TESObjectSTAT
				kPersistent = 1 << 10,
				kInitiallyDisabled = 1 << 11,
				kIgnored = 1 << 12,

				kStartUnconscious = 1 << 13,  // TESNPC
				kSkyMarker = 1 << 13,
				kHarvested = 1 << 13,  // TESObjectTREE

				kIsFullLOD = 1 << 16,   // Actor
				kNeverFades = 1 << 16,  // TESObjectLIGH

				kDoesntLightLandscape = 1 << 17,

				kNoAIAcquire = 1 << 25,
				kCollisionGeometry_Filter = 1 << 26,
				kCollisionGeometry_BoundingBox = 1 << 27,
				kReflectedByAutoWater = 1 << 28,

				kDontHavokSettle = 1 << 29,

				kGround = 1 << 30,
				kRespawns = 1 << 30,

				kMultibound = (uint32_t)1 << 31
			};
		};
	public:
		~TESObjectREFR() override;

		// override (TESForm)
		void                 InitializeData() override;
		void                 ClearData() override;
		bool                 Load(TESFile* a_mod) override;
		TESForm*             CreateDuplicateForm(bool a_createEditorID, void* a_arg2) override;
		bool                 CheckSaveGame(BGSSaveFormBuffer* a_buf) override;
		void                 SaveGame(BGSSaveFormBuffer* a_buf) override;
		void                 LoadGame(BGSLoadFormBuffer* a_buf) override;
		void                 InitLoadGame(BGSLoadFormBuffer* a_buf) override;
		void                 FinishLoadGame(BGSLoadFormBuffer* a_buf) override;
		void                 Revert(BGSLoadFormBuffer* a_buf) override;
		void                 InitItemImpl() override;
		uint8_t              GetSavedFormType() const override;
		void                 GetFormDetailedString(char* a_buf, uint32_t a_bufLen) override;
		bool                 GetRandomAnim() const override;
		bool                 IsHeadingMarker() const override;
		bool                 GetDangerous() const override;
		bool                 GetObstacle() const override;
		bool                 GetOnLocalMap() const override;
		bool                 GetMustUpdate() const override;
		void                 SetOnLocalMap(bool a_set) override;
		bool                 GetIgnoredBySandbox() const override;
		void                 SetDelete(bool a_set) override;
		void                 SetAltered(bool a_set) override;
		bool                 IsWater() const override;
		TESObjectREFR*       AsReference1() override;
		const TESObjectREFR* AsReference2() const override;
		bool                 BelongsInGroup(FORM* a_form, bool a_allowParentGroups, bool a_currentOnly) override;
		void                 CreateGroupData(FORM* a_form, FORM_GROUP* a_group) override;
		const char*          GetFormEditorID() const override;

		// add
		virtual void								Predestroy();
		virtual bool								GetEditorLocation(NiPoint3& a_outPos, NiPoint3& a_outRot, TESForm*& a_outWorldOrCell, TESObjectCELL* a_fallback);
		virtual void								ForceEditorLocation(BGSLocation* a_location);
		virtual void								Update3DPosition(bool a_warp);
		virtual void								UpdateSoundCallBack(bool a_endSceneAction);
		virtual bool								SetDialogueWithPlayer(bool a_flag, bool a_forceGreet, TESTopicInfo* a_topic);
		virtual void								TESObjectREFR_Unk_8();
		virtual bool								GetFullLODRef();
		virtual void								SetFullLODRef(bool);
		virtual BGSAnimationSequencer*				GetSequencer();
		virtual bool								QCanUpdateSync();
		virtual bool								GetAllowPromoteToPersistent() const;
		virtual bool								HasKeywordHelper(const BGSKeyword*) const;
		virtual TESPackage*							CheckForCurrentAliasPackage();
		virtual BGSScene*							GetCurrentScene();
		virtual void								SetCurrentScene(BGSScene* a_scene);
		virtual bool								UpdateInDialogue(DialogueResponse* a_response, bool a_unused);
		virtual BGSDialogueBranch*					GetExclusiveBranch();
		virtual void								SetExclusiveBranch(BGSDialogueBranch* a_branch);
		virtual void								PauseCurrentDialogue();
		virtual void								SetActorCause(ActorCause* a_cause);
		virtual ActorCause*							GetActorCause() const;
		virtual NiPoint3							GetStartingAngle();
		virtual NiPoint3							GetStartingLocation();
		virtual void								SetStartingPosition(const NiPoint3& a_pos);
		virtual void								UpdateRefLight();
		virtual uint32_t*							RemoveItem(TESBoundObject* a_item, int32_t a_count, ITEM_REMOVE_REASON a_reason, ExtraDataList* a_extraList, TESObjectREFR* a_moveToRef, const NiPoint3* a_dropLoc = 0, const NiPoint3* a_rotate = 0);
		virtual bool								AddWornItem(TESBoundObject* a_item, int32_t a_count, bool a_forceEquip, uint32_t a_arg4, uint32_t a_arg5);
		virtual void								DoTrap1(TrapData& a_data);
		virtual void								DoTrap2(TrapEntry* a_trap, TargetEntry* a_target);
		virtual void								AddObjectToContainer(TESBoundObject* a_object, ExtraDataList* a_extraList, int32_t a_count, TESObjectREFR* a_fromRefr);
		virtual NiPoint3							GetLookingAtLocation();
		virtual MagicCaster*						GetMagicCaster(MagicSystem::CastingSource);
		virtual MagicTarget*						GetMagicTarget();
		virtual bool								IsChild();
		virtual TESActorBase*						GetTemplateActorBase();
		virtual void								SetTemplateActorBase(TESActorBase*);
		virtual BSFaceGenNiNode*					GetFaceGenNiNode();
		virtual BSFaceGenNiNode*					GetFaceNode();
		virtual BSFaceGenAnimationData*				GetFaceGenAnimationData();
		virtual bool								ClampToGround();
		virtual bool								DetachHavok(NiAVObject*);
		virtual void								InitHavok();
		virtual void								TESObjectREFR_Unk_45();
		virtual void								TESObjectREFR_Unk_46();
		virtual void								TESObjectREFR_Unk_47();
		virtual NiAVObject*							Load3D(bool);
		virtual void								Release3DRelatedData();
		virtual void								Set3D(NiAVObject*, bool a_queue3DTasks = true);
		virtual bool								ShouldBackgroundClone();
		virtual void								TESObjectREFR_Unk_52();
		virtual NiAVObject*							Get3D1();
		virtual NiAVObject*							Get3D2(bool);
		virtual bool								Is3rdPersonVisible();
		virtual bool								PopulateGraphProjectsToLoad();
		virtual NiPoint3							GetBoundMin();
		virtual NiPoint3							GetBoundMax();
		BSEventNotifyControl						ProcessEvent(const BSAnimationGraphEvent*, BSTEventSource<BSAnimationGraphEvent>*) override;
		virtual void								TESObjectREFR_Unk_60();
		virtual bool								InitNonNPCAnimation(NiNode&);
		virtual void								CheckAndFixSkinAndBoneOrder(NiNode&);
		virtual void								TESObjectREFR_Unk_63();
		bool										PopulateGraphNodesToTarget(BSScrapArray<NiAVObject*>& a_nodes) override;
		bool										ConstructAnimationGraph(BSTSmartPointer<BShkbAnimationGraph>& a_out) override;
		void										PostChangeAnimationManager(const BSTSmartPointer<BShkbAnimationGraph>& a_arg1, const BSTSmartPointer<BShkbAnimationGraph>& a_arg2) override;
		bool										SetAnimationGraphManagerImpl(BSTSmartPointer<BSAnimationGraphManager>& a_in) override;
		bool										GetAnimationGraphManagerImpl(BSTSmartPointer<BSAnimationGraphManager>& a_out) const override;
		bool										SetupAnimEventSinks(const BSTSmartPointer<BShkbAnimationGraph>& a_animGraph) override;
		virtual void								TESObjectREFR_Unk_70();
		virtual void								ModifyAnimationUpdateData(BSAnimationUpdateData& a_data);
		virtual bool								ShouldSaveAnimationOnUnloading();
		virtual bool								ShouldSaveAnimationOnSaving();
		virtual bool								ShouldPerformRevert();
		virtual void								UpdateAnimation(float);
		virtual const BSTSmartPointer<BipedAnim>&	GetBiped2();
		virtual const BSTSmartPointer<BipedAnim>&	GetBiped1(bool a_firstPerson);
		virtual const BSTSmartPointer<BipedAnim>&	GetCurrentBiped();
		virtual void								SetBiped(const BSTSmartPointer<BipedAnim>& a_biped);
		virtual void								TESObjectREFR_Unk_80();
		virtual void								TESObjectREFR_Unk_81();
		virtual void								SetObjectReference(TESBoundObject* a_object);
		virtual void								MoveHavok(bool a_forceRec);
		virtual void								GetLinearVelocity(NiPoint3& a_velocity) const;
		virtual void								SetActionComplete(bool);
		virtual void								SetMovementComplete(bool);
		virtual void								Disable();
		virtual void								ResetInventory(bool);
		virtual void								TESObjectREFR_Unk_89();
		virtual void								TESObjectREFR_Unk_90();
		virtual NiAVObject*							Get3D3();
		virtual Explosion*							AsExplosion();
		virtual Projectile*							AsProjectile();
		virtual bool								OnAddCellPerformQueueReference(TESObjectCELL&) const;
		virtual void								DoMoveToHigh();
		virtual void								TryMoveToMiddleLow();
		virtual bool								TryChangeSkyCellActorsProcessLevel();
		virtual void								TESObjectREFR_Unk_98();
		virtual void								TESObjectREFR_Unk_99();	
		virtual void								TESObjectREFR_Unk_100();
		virtual void								TESObjectREFR_Unk_101();
		virtual TESObjectCELL*						GetSaveParentCell();
		virtual void								SetParentCell(TESObjectCELL* a_cell);
		virtual bool								IsDead(bool a_bool = true);
		virtual BSAnimNoteReceiver*					CreateAnimNoteReceiver();
		virtual BSAnimNoteReceiver*					GetAnimNoteReceiver();
		virtual void								TESObjectREFR_Unk_107();
		virtual void								TESObjectREFR_Unk_108();
		virtual TESAmmo* 							GetCurrentAmmo();
		virtual BGSDecalGroup*						GetDecalGroup();
		virtual void								TESObjectREFR_Unk_111();
		virtual void								UnequipItem(uint64_t a_arg1, TESBoundObject* a_object);

		// add
		TESNPC*										GetActorOwner();
		NiPoint3									GetAngle();
		float										GetAngleX();
		float										GetAngleY();
		float										GetAngleZ();
		TESBoundObject*								GetBaseObject();
		const TESBoundObject*						GetBaseObject() const;
		const char*									GetDisplayFullName();
		TESBoundObject*								GetObjectReference() const noexcept;
		TESForm*									GetOwner();
		TESObjectCELL*								GetParentCell();
		NiPoint3									GetPosition();
		float										GetPositionX();
		float										GetPositionY();
		float										GetPositionZ();
		uint32_t									GetStealValue(const InventoryEntryData* a_entryData, uint32_t a_numItems, bool a_useMult);
		float										GetWeight();
		TESWorldSpace*								GetWorldSpace();
		bool										IsDisabled();
		bool										IsMarkedForDeletion();
		void										UpdateHarvestModel(NiAVObject* a_node);
		float										GetScale();
		bool										IsCrimeToActivate();
		bool										IsOffLimits();
	public:
		OBJ_REFR				 data;
		TESObjectCELL*			 parentCell;
		LOADED_REF_DATA*		 loadedData;
		ExtraDataList			 extraList;
		uint64_t				 Unk90;
		uint32_t				 Unk98;
		uint32_t				 Unk9C;
		uint16_t				 refScale;
		int8_t					 modelState;
		int8_t					 preDestroyed;
		uint32_t				 UnkA4;
	};
	static_assert(sizeof(TESObjectREFR) == 0xA8);
}