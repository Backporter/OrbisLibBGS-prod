#pragma once

#include "../T/TESObjectSTAT.h"

#include "../B/BGSBlockBashData.h"
#include "../B/BGSDestructibleObjectForm.h"
#include "../B/BGSEquipType.h"
#include "../B/BGSKeywordForm.h"
#include "../B/BGSPickupPutdownSounds.h"
#include "../B/BGSPreloadable.h"
#include "../T/TESAttackDamageForm.h"
#include "../T/TESBoundObject.h"
#include "../T/TESDescription.h"
#include "../T/TESEnchantableForm.h"
#include "../T/TESFullName.h"

#include "../T/TESModel.h"
#include "../T/TESModelTextureSwap.h"
#include "../T/TESValueForm.h"
#include "../T/TESWeightForm.h"

namespace ConsoleRE
{
	class SpellItem;
	class BGSSoundDescriptorForm;

	enum class WEAPON_TYPE
	{
		kHandToHandMelee = 0,
		kOneHandSword = 1,
		kOneHandDagger = 2,
		kOneHandAxe = 3,
		kOneHandMace = 4,
		kTwoHandSword = 5,
		kTwoHandAxe = 6,
		kBow = 7,
		kStaff = 8,
		kCrossbow = 9
	};

	class TESObjectWEAP : 
		public TESBoundObject, 
		public TESFullName, 
		public TESModelTextureSwap, 
		public TESEnchantableForm, 
		public TESValueForm, 
		public TESWeightForm, 
		public TESAttackDamageForm, 
		public BGSDestructibleObjectForm, 
		public BGSEquipType, 
		public BGSPreloadable, 
		public BGSPickupPutdownSounds, 
		public BGSBlockBashData, 
		public BGSKeywordForm, 
		public TESDescription
	{
	public:
		struct RangedData
		{
		public:
			float													sightFOV;
			float													Unk04;
			float													firingRumbleLeftMotorStrength;
			float													firingRumbleRightMotorStrength;
			float													firingRumbleDuration;
			uint32_t												rumblePattern;
			int8_t													numProjectiles;
			uint8_t													pad19;
			uint16_t												pad1A;
		};
		static_assert(sizeof(RangedData) == 0x1C);

		struct Data
		{
		public:
			enum class Flag2
			{
				kNone = 0,
				kPlayerOnly = 1 << 0,
				kNPCsUseAmmo = 1 << 1,
				kNoJamAfterReload = 1 << 2,
				kMinorCrime = 1 << 4,
				kRangeFixed = 1 << 5,
				kNotUsedInNormalCombat = 1 << 6,
				kDontUse3rdPersonISAnim = 1 << 8,
				kBurstShot = 1 << 9,
				kRumbleAlternate = 1 << 10,
				kLongBursts = 1 << 11,
				kNonHostile = 1 << 12,
				kBoundWeapon = 1 << 13
			};

			enum class AttackAnimation
			{
				kAttackLeft = 26,
				kAttackRight = 32,
				kAttack3 = 38,
				kAttack4 = 44,
				kAttack5 = 50,
				kAttack7 = 62,
				kAttack8 = 68,
				kAttackLoop = 74,
				kAttackSpin = 80,
				kAttackSpin2 = 86,
				kPlaceMine = 97,
				kPlaceMine2 = 103,
				kAttackThrow = 109,
				kAttackThrow2 = 115,
				kAttackThrow3 = 121,
				kAttackThrow4 = 127,
				kAttackThrow5 = 133,
				kDefault = 255
			};

			enum class Flag
			{
				kNone = 0,
				kIgnoresNormalWeaponResistance = 1 << 0,
				kAutomatic = 1 << 1,
				kHasScope = 1 << 2,
				kCantDrop = 1 << 3,
				kHideBackpack = 1 << 4,
				kEmbeddedWeapon = 1 << 5,
				kDontUseFirstPersonISAnim = 1 << 6,
				kNonPlayable = 1 << 7
			};

		public:
			RangedData*		rangedData;
			float			speed;
			float			reach;
			float			minRange;
			float			maxRange;
			float			animationAttackMult;
			float			animationAttackShotsPerSecond;
			float			staggerValue;
			uint32_t		hitBehavior;
			uint32_t		skill;
			uint32_t		resistance;
			uint16_t		flags2;
			uint8_t			baseVATSToHitChance;
			uint8_t			attackAnimation;
			uint8_t			embeddedWeaponAV;
			uint8_t			animationType;
			uint8_t			flags;
			uint8_t			Unk37;
		};
		static_assert(sizeof(Data) == 0x38);

		struct CriticalData
		{
		public:
			enum Flag
			{
				kNone = 0,
				kOnDeath = 1 << 0
			};

		public:
			float                           prcntMult;
			uint32_t                        pad04;
			SpellItem*                      effect;
			uint16_t                        damage;
			uint8_t							flags;
			uint8_t                         pad13;
			uint32_t                        pad14;
		};
		// static_assert(sizeof(CriticalData) == 0x18);
	public:
		static constexpr int TypeID = 41;

		virtual ~TESObjectWEAP();
	public:
		bool          IsBound() const			{ return (weaponData.flags & 8192) == 8192;		}
		bool          IsMelee() const			{ return (weaponData.animationType <= 6);		}
		bool          IsRanged() const			{ return (weaponData.animationType - 7) <= 2;	}
		bool          IsHandToHandMelee() const { return (weaponData.animationType == 0);		}
		bool          IsOneHandedSword() const  { return (weaponData.animationType == 1);		}
		bool          IsOneHandedDagger() const { return (weaponData.animationType == 2);		}
		bool          IsOneHandedAxe() const	{ return (weaponData.animationType == 3);		}
		bool          IsOneHandedMace() const	{ return (weaponData.animationType == 4);		}
		bool          IsTwoHandedSword() const	{ return (weaponData.animationType == 5);		}
		bool          IsTwoHandedAxe() const	{ return (weaponData.animationType == 6);		}
		bool          IsBow() const				{ return (weaponData.animationType == 7);		}
		bool          IsStaff() const			{ return (weaponData.animationType == 8);		}
		bool          IsCrossbow() const		{ return (weaponData.animationType == 9);		}
	public:
		Data						weaponData;
		CriticalData				criticalData;
		void*						UNK4;
		BGSSoundDescriptorForm*		attackSound;
		BGSSoundDescriptorForm*		attackSound2D;
		BGSSoundDescriptorForm*		attackLoopSound;
		BGSSoundDescriptorForm*		attackFailSound;
		BGSSoundDescriptorForm*		idleSound;
		BGSSoundDescriptorForm*		equipSound;
		BGSSoundDescriptorForm*		unequipSound;
		BGSImpactDataSet*			impactDataSet;
		TESObjectSTAT*				firstPersonModelObject;
		TESObjectWEAP*				templateWeapon;
		BSFixedString				embeddedNode;
		uint32_t					soundLevel;
	};
	static_assert(sizeof(TESObjectWEAP) == 0x1F0);
}