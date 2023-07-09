#pragma once

#include "../B/BSFixedString.h"
#include "../B/BGSSkinForm.h"
#include "../B/BGSBipedObjectForm.h"
#include "../B/BGSKeywordForm.h"
#include "../B/BGSAttackDataForm.h"
#include "../B/BGSTextureModel.h"
#include "../B/BGSBehaviorGraphModel.h"

#include "../T/TESForm.h"
#include "../T/TESFullName.h"
#include "../T/TESDescription.h"
#include "../T/TESSpellList.h"
#include "../N/NiPoint3.h"
#include "../B/BGSVoiceType.h"
#include "../B/BGSBodyPartData.h"
#include "../A/AttackAnimationArrayMap.h"
#include "../B/BGSMaterialType.h"
#include "../B/BGSImpactDataSet.h"
#include "../B/BGSMovementType.h"
#include "../B/BGSSoundDescriptorForm.h"
#include "../B/BGSArtObject.h"
#include "../B/BSTArray.h"
#include "../T/TESTexture.h"

namespace ConsoleRE
{
	class TESNPC;
	class BGSHeadPart;
	class BGSColorForm;
	
	struct RACE_DATA
	{
	public:
		enum
		{
			kNumSkillBoosts = 7
		};

		enum class Flag
		{
			kNone = 0,
			kPlayable = 1 << 0,
			kFaceGenHead = 1 << 1,
			kChild = 1 << 2,
			kTiltFrontBack = 1 << 3,
			kTiltLeftRight = 1 << 4,
			kNoShadow = 1 << 5,
			kSwims = 1 << 6,
			kFlies = 1 << 7,
			kWalks = 1 << 8,
			kImmobile = 1 << 9,
			kNotPushable = 1 << 10,
			kNoCombatInWater = 1 << 11,
			kNoRotatingToHeadTrack = 1 << 12,
			kDontShowBloodSpray = 1 << 13,
			kDontShowBloodDecal = 1 << 14,
			kUseHeadTrackAnims = 1 << 15,
			kSpellsAlignWithMagicNode = 1 << 16,
			kUseWorldRaycastsForFootIK = 1 << 17,
			kAllowRagdollCollision = 1 << 18,
			kRegenHPInCombat = 1 << 19,
			kCantOpenDoors = 1 << 20,
			kAllowPCDialogue = 1 << 21,
			kNoKnockdowns = 1 << 22,
			kAllowPickpocket = 1 << 23,
			kAlwaysUseProxyController = 1 << 24,
			kDontShowWeaponBlood = 1 << 25,
			kOverlayHeadPartList = 1 << 26,
			kOverrideHeadPartList = 1 << 27,
			kCanPickupItems = 1 << 28,
			kAllowMultipleMembraneShaders = 1 << 29,
			kCanDualWield = 1 << 30,
			kAvoidsRoads = 1 << 31,
		};

		enum class Flag2
		{
			kNone = 0,
			kUseAdvancedAvoidance = 1 << 0,
			kNonHostile = 1 << 1,
			kAllowMountedCombat = 1 << 4
		};

		struct SkillBonus
		{
		public:
			uint8_t skill;
			uint8_t bonus;
		};
		static_assert(sizeof(SkillBonus) == 0x2);
	public:
		SkillBonus					bonuses[kNumSkillBoosts];
		uint16_t					pad0E;
		float						height[2];
		float						weight[2];
		uint32_t					flags;
		float						startingHealth;
		float						startingMagicka;
		float						startingStamina;
		float						baseCarryWeight;
		float						baseMass;
		float						accelerate;
		float						decelerate;
		uint32_t					raceSize;
		uint32_t					headObject;
		uint32_t					hairObject;
		float						injuredHealthPercent;
		uint32_t					shieldObject;
		float						healthRegen;
		float						magickaRegen;
		float						staminaRegen;
		float						unarmedDamage;
		float						unarmedReach;
		uint32_t					bodyObject;
		float						aimAngleTolerance;
		float						flightRadius;
		float						angleAccelerate;
		float						angleTolerance;
		uint32_t					flags2;
		NiPoint3					mountOffset;
		NiPoint3					dismountOffset;
		NiPoint3					mountCameraOffset;
	};

	class TESRace : 
		public TESForm, 
		public TESFullName, 
		public TESDescription, 
		public TESSpellList, 
		public BGSSkinForm, 
		public BGSBipedObjectForm, 
		public BGSKeywordForm, 
		public BGSAttackDataForm
	{
	public:
		enum class EquipmentFlag
		{
			kNone = 0,
			kHandToHandMelee = 1 << 0,
			kOneHandSword = 1 << 1,
			kOneHandDagger = 1 << 2,
			kOneHandAxe = 1 << 3,
			kOneHandMace = 1 << 4,
			kTwoHandSword = 1 << 5,
			kTwoHandAxe = 1 << 6,
			kBow = 1 << 7,
			kStaff = 1 << 8,
			kSpell = 1 << 9,
			kShield = 1 << 10,
			kTorch = 1 << 11,
			kCrossbow = 1 << 12
		};

		struct RecordFlags
		{
			enum RecordFlag : uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kCritter = 1 << 19
			};
		};

		struct MovementTypes
		{
			enum
			{
				kWalk = 0,
				kRun,
				kSwim,
				kFly,
				kSneak,
				kSprint,
				kTotal
			};
		};

		struct FaceRelatedData
		{
			enum
			{
				kNose = 0,
				kBrows,
				kEyes,
				kLips,
				kNumVariants
			};

			struct Morph
			{
			public:
				uint32_t morphFlags;
				uint32_t unk04;
				uint32_t unk08;
				uint32_t unk0C;
				uint32_t unk10;
				uint32_t unk14;
				uint32_t unk18;
				uint32_t unk1C;
			};
			static_assert(sizeof(Morph) == 0x20);

			struct TintAsset
			{
			public:
				struct TintLayer
				{
				public:
					enum class SkinTone
					{
						kNone = 0,
						kLipColor = 1,
						kCheekColor = 2,
						kEyeliner = 3,
						kEyeSocketUpper = 4,
						kEyeSocketLower = 5,
						kSkinTone = 6,
						kPaint = 7,
						kLaughLines = 8,
						kCheekColorLower = 9,
						kNose = 10,
						kChin = 11,
						kNeck = 12,
						kForehead = 13,
						kDirt = 14,
					};
				public:
					uint16_t                            index;
					uint8_t								skinTone;
					TESTexture                          file;
					BGSColorForm*                       presetDefault;
				};
				static_assert(sizeof(TintLayer) == 0x20);

				struct Presets
				{
				public:
					BSTArray<BGSColorForm*> colors;
					BSTArray<float>         defaultValues;
					BSTArray<uint16_t>		indices;
				};
				static_assert(sizeof(Presets) == 0x30);
			public:
				TintLayer texture;
				Presets   presets;
			};
			static_assert(sizeof(TintAsset) == 0x50);
		public:
			Morph                     availableMorphs[kNumVariants];
			uint32_t				  numFlagsSet[kNumVariants];
			BSTArray<TintAsset*>*     tintMasks;
			BSTArray<BGSTextureSet*>* faceDetailsTextureSets;
			BGSTextureSet*            defaultFaceDetailsTextureSet;
			BSTArray<TESNPC*>*        presetNPCs;
			BSTArray<BGSColorForm*>*  availableHairColors;
			BGSColorForm*             defaultHairColor;
			BSTArray<BGSHeadPart*>*   headParts;
		};
		static_assert(sizeof(FaceRelatedData) == 0xC8);
	public:
		static constexpr int TypeID = 14;
		
		~TESRace() override;

		// override (TESForm)
		void        InitializeData() override;
		void        ClearData() override;
		bool        Load(TESFile* a_mod) override;
		void        InitItemImpl() override;
		bool        GetPlayable() const override;
		const char* GetFormEditorID() const override;
		bool        SetFormEditorID(const char* a_str) override;
	public:
		TESModel					skeletonModels[2];
		RACE_DATA                   data;
		float						clampFaceGeoValue;
		float						clampFaceGeoValue2;
		uint32_t					pad194;
		BGSTextureModel				bodyTextureModels[2];
		BGSBehaviorGraphModel		behaviorGraphs[2];
		BSFixedString				rootBehaviorGraphNames[2];
		BSFixedString				behaviorGraphProjectNames[2];
		BGSVoiceType*				defaultVoiceTypes[2];
		BGSBodyPartData*			bodyPartData;
		TESObjectARMO*              decapitateArmors[2];
		uint8_t						Unk280[0x10];
		uint8_t						Unk290[0x10];
		uint64_t					Unk2A0;
		uint64_t					Unk2A8;
		uint64_t					Unk2B0;
		uint64_t					Unk2B8;
		AttackAnimationArrayMap*	AttackAnimationArrayMap[2];
		BSFixedString               formEditorID;
		BGSMaterialType*            bloodImpactMaterial;
		BGSImpactDataSet*           impactDataSet;
		BGSArtObject*               dismemberBlood;
		BGSSoundDescriptorForm*     corpseOpenSound;
		BGSSoundDescriptorForm*     corpseCloseSound;
		BSFixedString               bipedObjectNameA[32];
		BSTArray<BGSEquipSlot*>     equipSlots;
		uint32_t					validEquipTypes;
		uint32_t					Unk414;
		BGSEquipSlot*               unarmedEquipSlot;
		TESRace*                    morphRace;
		TESRace*                    armorParentRace;
		uint8_t						Unk430[0x10];
		BSTArray<BSFixedString>     phonemeTargets;
		BGSMovementType*            baseMoveTypes[MovementTypes::kTotal];
		FaceRelatedData*			faceRelatedData[2];
	};
	static_assert(sizeof(TESRace) == 0x490);
}