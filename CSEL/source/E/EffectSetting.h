#pragma once

#include "../B/BGSKeywordForm.h"
#include "../B/BGSMenuDisplayObject.h"
#include "../B/BSFixedString.h"
#include "../B/BSTArray.h"
#include "../B/BSTList.h"
#include "../E/EffectArchetypes.h"
#include "../F/FormTypes.h"
#include "../M/MagicSystem.h"
#include "../S/SoundLevels.h"
#include "../T/TESCondition.h"
#include "../T/TESForm.h"
#include "../T/TESFullName.h"

namespace ConsoleRE
{
	class EffectSetting : 
		public TESForm, 
		public TESFullName, 
		public BGSMenuDisplayObject, 
		public BGSKeywordForm
	{
	public:
		static constexpr int TypeID = 18;

		using FilterValidation_t = bool(EffectSetting*, void*);

		struct EffectSettingData
		{
		public:
			enum Flag
			{
				kNone = 0,
				kHostile = 1 << 0,
				kRecover = 1 << 1,
				kDetrimental = 1 << 2,
				kSnapToNavMesh = 1 << 3,
				kNoHitEvent = 1 << 4,
				kDispelWithKeywords = 1 << 8,
				kNoDuration = 1 << 9,
				kNoMagnitude = 1 << 10,
				kNoArea = 1 << 11,
				kFXPersist = 1 << 12,
				kGoryVisuals = 1 << 14,
				kHideInUI = 1 << 15,
				kNoRecast = 1 << 17,
				kPowerAffectsMagnitude = 1 << 21,
				kPowerAffectsDuration = 1 << 22,
				kPainless = 1 << 26,
				kNoHitEffect = 1 << 27,
				kNoDeathDispel = 1 << 28
			};
		public:
			uint32_t							  flags;
			float								  baseCost;
			TESForm*							  associatedForm;
			uint32_t							  associatedSkill;
			uint32_t							  resistVariable;
			uint16_t							  numCounterEffects;
			uint16_t							  pad1A;
			uint32_t							  pad1C;
			TESObjectLIGH*						  light;
			float								  taperWeight;
			uint32_t							  pad2C;
			TESEffectShader*					  effectShader;
			TESEffectShader*					  enchantShader;
			uint32_t							  minimumSkill;
			uint32_t							  spellmakingArea;
			float								  spellmakingChargeTime;
			float								  taperCurve;
			float								  taperDuration;
			uint32_t							  secondAVWeight;
			uint32_t							  archetype;
			uint32_t							  primaryAV;
			BGSProjectile*						  projectileBase;
			BGSExplosion*						  explosion;
			uint32_t							  castingType;
			uint32_t							  delivery;
			uint32_t							  secondaryAV;
			BGSArtObject*						  castingArt;
			BGSArtObject*						  hitEffectArt;
			BGSImpactDataSet*					  impactDataSet;
			float								  skillUsageMult;
			uint32_t							  pad9C;
			BGSDualCastData*					  dualCastData;
			float								  dualCastScale;
			uint32_t							  padAC;
			BGSArtObject*                         enchantEffectArt;
			BGSReferenceEffect*                   hitVisuals;
			BGSReferenceEffect*                   enchantVisuals;
			SpellItem*                            equipAbility;
			TESImageSpaceModifier*                imageSpaceMod;
			BGSPerk*                              perk;
			uint32_t							  castingSoundLevel;
			float								  aiScore;
			float								  aiDelayTimer;
			uint32_t							  padEC;
		};
		static_assert(sizeof(EffectSettingData) == 0xF0);

		struct SoundInfo
		{
			MagicSystem::SoundID	id;
			uint32_t				pad04;
			BGSSoundDescriptorForm* sound;
		};
		static_assert(sizeof(SoundInfo) == 0x10);
	public:
		~EffectSetting() override;
	
		// override (TESForm)
		void        ClearData() override;
		bool        Load(TESFile* a_mod) override;
		void        InitItemImpl() override;
		void        Copy(TESForm* a_srcForm) override;
		const char* GetObjectTypeName() const override;

		// override (BGSKeywordForm)
		bool HasKeyword(const BGSKeyword* a_keyword) const override;
	public:
		FilterValidation_t*					filterValidationFunction;
		void*								filterValidationItem;
		EffectSettingData					data;
		BSSimpleList<EffectSetting*>		counterEffects;
		BSTArray<SoundInfo>					effectSounds;
		BSFixedString						magicItemDescription;
		uint32_t							effectLoadedCount;
		uint32_t							associatedItemLoadedCount;
		TESCondition						conditions;
	};
	static_assert(sizeof(EffectSetting) == 0x190);
}