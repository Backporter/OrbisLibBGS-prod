#pragma once

#include "../B/BSTArray.h"
#include "../B/BaseFormComponent.h"
#include "../F/FactionRank.h"

namespace ConsoleRE
{
	class BGSVoiceType;
	class TESActorBase;
	class TESForm;
	class TESLevItem;

	struct ACTOR_BASE_DATA
	{
	public:
		enum class Flag
		{
			kNone = 0,
			kFemale = 1 << 0,
			kEssential = 1 << 1,
			kIsChargenFacePreset = 1 << 2,
			kRespawn = 1 << 3,
			kAutoCalcStats = 1 << 4,
			kUnique = 1 << 5,
			kDoesntAffectStealthMeter = 1 << 6,
			kPCLevelMult = 1 << 7,
			kUsesTemplate = 1 << 8,
			kProtected = 1 << 11,
			kSummonable = 1 << 14,
			kDoesntBleed = 1 << 16,
			kBleedoutOverride = 1 << 18,
			kOppositeGenderanims = 1 << 19,
			kSimpleActor = 1 << 20,
			kLoopedScript = 1 << 21,  // ?
			kLoopedAudio = 1 << 28,   // ?
			kIsGhost = 1 << 29,
			kInvulnerable = 1 << 31
		};

		enum class TEMPLATE_USE_FLAG
		{
			kNone = 0,
			kTraits = 1 << 0,
			kStats = 1 << 1,
			kFactions = 1 << 2,
			kSpells = 1 << 3,
			kAIData = 1 << 4,
			kAIPackages = 1 << 5,
			kUnused = 1 << 6,
			kBaseData = 1 << 7,
			kInventory = 1 << 8,
			kScript = 1 << 9,
			kAIDefPackList = 1 << 10,
			kAttackData = 1 << 11,
			kKeywords = 1 << 12
		};
	public:
		uint32_t									actorBaseFlags;
		int16_t										magickaOffset;
		int16_t										staminaOffset;
		uint16_t									level;
		uint16_t									calcLevelMin;
		uint16_t									calcLevelMax;
		uint16_t									speedMult;
		uint16_t									baseDisposition;
		uint16_t									templateUseFlags;
		int16_t										healthOffset;
		int16_t										bleedoutOverride;
	};
	static_assert(sizeof(ACTOR_BASE_DATA) == 0x18);

	class TESActorBaseData : public BaseFormComponent
	{
	public:
		~TESActorBaseData() override;

		// override (BaseFormComponent)
		void InitializeDataComponent() override;
		void ClearDataComponent() override;
		void CopyComponent(BaseFormComponent* a_rhs) override;

		// add
		virtual void				CopyFromTemplateForms(TESActorBase** a_templateForms);
		virtual bool				GetIsGhost() const;
		virtual bool				GetInvulnerable() const;
		virtual void				Unk_07(void);
		virtual BGSVoiceType*		GetVoiceType(void);
	public:
		ACTOR_BASE_DATA        actorData;
		TESLevItem*            deathItem;
		BGSVoiceType*          voiceType;
		TESForm*               baseTemplateForm;
		TESForm**              templateForms;
		BSTArray<FactionRank>  factions;
	};
	static_assert(sizeof(TESActorBaseData) == 0x50);
}