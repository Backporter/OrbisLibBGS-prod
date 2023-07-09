#pragma once

#include "../B/BGSHeadPart.h"
#include "../B/BGSOverridePackCollection.h"
#include "../B/BSFixedString.h"
#include "../B/BSTArray.h"
#include "../B/BSTEvent.h"
#include "../C/Color.h"
#include "../F/FormTypes.h"
#include "../T/TESActorBase.h"
#include "../T/TESRaceForm.h"

namespace ConsoleRE
{
	class BSFaceGenNiNode;
	class MenuOpenCloseEvent;
	class NiColorA;
	class TintMask;

	class TESRace;
	class TESFaction;

	class CreatureSounds
	{
	public:
		BSTArray<void*>* unk00[8];
	};
	static_assert(sizeof(CreatureSounds) == 0x40);

	class TESNPC : public TESActorBase, public TESRaceForm, public BGSOverridePackCollection, public BSTEventSink<MenuOpenCloseEvent>
	{
	public:
		struct Skills
		{
		public:
			enum
			{
				kOneHanded = 0,
				kTwoHanded = 1,
				kMarksman = 2,
				kBlock = 3,
				kSmithing = 4,
				kHeavyArmor = 5,
				kLightArmor = 6,
				kPickpocket = 7,
				kLockpicking = 8,
				kSneak = 9,
				kAlchemy = 10,
				kSpecchcraft = 11,
				kAlteration = 12,
				kConjuration = 13,
				kDestruction = 14,
				kIllusion = 15,
				kRestoration = 16,
				kEnchanting = 17,
				kTotal
			};
		public:
			uint8_t			values[kTotal];
			uint8_t			offsets[kTotal];
			uint16_t		health;
			uint16_t		magicka;
			uint16_t		stamina;
			uint16_t		pad2A;
			float			farawayModelDistance;
		};
		static_assert(sizeof(Skills) == 0x30);

		struct HeadRelatedData
		{
		public:
			HeadRelatedData() = default;
			~HeadRelatedData() = default;
		public:
			BGSColorForm*  hairColor { 0 };
			BGSTextureSet* faceDetails { 0 };
		};
		static_assert(sizeof(HeadRelatedData) == 0x10);

		union Sounds
		{
			TESNPC*         soundCreature;
			CreatureSounds* creatureSounds;
		};
		static_assert(sizeof(Sounds) == 0x8);

		struct FaceData
		{
		public:
			struct Morphs
			{
				enum
				{
					kNose_LongShort = 0,
					kNose_UpDown = 1,
					kJaw_UpDown = 2,
					kJaw_NarrowWide = 3,
					kJaw_ForwardBack = 4,
					kCheeks_UpDown = 5,
					kCheeks_ForwardBack = 6,
					kEyes_UpDown = 7,
					kEyes_InOut = 8,
					kBrows_UpDown = 9,
					kBrows_InOut = 10,
					kBrows_ForwardBack = 11,
					kLips_UpDown = 12,
					kLips_InOut = 13,
					kChin_NarrowWide = 14,
					kChin_UpDown = 15,
					kChin_UnderbiteOverbite = 16,
					kEyes_ForwardBack = 17,
					kUnk = 18,

					kTotal = 19
				};
			};

			struct Parts
			{
				enum
				{
					kNose = 0,
					kUnknown = 1,
					kEyes = 2,
					kMouth = 3,

					kTotal = 4
				};
			};

			enum
			{
				kDefault = 0x7F7FFFFF,
				kTotalPresets = 4
			};
		public:
			float        morphs[Morphs::kTotal];
			int32_t		 parts[Parts::kTotal];
		};
		static_assert(sizeof(FaceData) == 0x5C);
	public:
		static constexpr int TypeID = 43;
	public:
		~TESNPC() override;

		// override (TESActorBase)
		void            InitializeData() override;
		void            ClearData() override;
		bool            Load(TESFile* a_mod) override;
		bool            FindInFileFast(TESFile* a_mod) override;
		void            SaveGame(BGSSaveFormBuffer* a_buf) override;
		void            LoadGame(BGSLoadFormBuffer* a_buf) override;
		void            Revert(BGSLoadFormBuffer* a_buf) override;
		void            InitItemImpl() override;
		const char*     GetTextForParsedSubTag(const BSFixedString& a_tag) const override;
		void            Copy(TESForm* a_srcForm) override;
		bool            Activate(TESObjectREFR* a_targetRef, TESObjectREFR* a_activatorRef, uint8_t a_arg3, TESBoundObject* a_object, int32_t a_targetCount) override;
		void            UnClone3D(TESObjectREFR* a_ref) override;
		void            SetObjectVoiceType(BGSVoiceType* a_voiceType) override;
		BGSVoiceType*   GetObjectVoiceType() const override;
		NiAVObject*     Clone3D(TESObjectREFR* a_ref) override;
		bool            GetActivateText(TESObjectREFR* a_activator, BSString& a_dst) override;
		bool            CalculateDoFavor(Actor* a_activator, bool a_arg2, TESObjectREFR* a_toActivate, float a_arg3) override;
		TESCombatStyle* GetCombatStyle() override;
		void            SetCombatStyle(TESCombatStyle* a_combatStyle) override;

		// override (TESActorBaseData)
		void CopyFromTemplateForms(TESActorBase** a_templateForms) override;

		// override ActorValueOwner
		float GetActorValue(uint32_t a_akValue) override;
		void  SetActorValue(uint32_t a_akValue, float a_value) override;

		// override BSTEventSink<MenuOpenCloseEvent>
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent* a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override;
	public:
		uint32_t		GetNumActorBaseOverlays();
		void			ChangeHeadPart(BGSHeadPart* a_target);
		BGSHeadPart**	GetBaseOverlays();
		BGSHeadPart*	GetCurrentHeadPartByType(uint32_t a_type);
		BGSHeadPart*	GetHeadPartByType(uint32_t a_type);
		BGSHeadPart*	GetHeadPartOverlayByType(uint32_t a_type);
		TESNPC*         GetRootFaceNPC();
		const TESNPC*	GetRootFaceNPC() const;
		int				GetSex();
		bool			HasOverlays();
		void			SetFaceTexture(BGSTextureSet* a_textureSet);
		void            SetHairColor(BGSColorForm* a_hairColor);
		void			SetSkinFromTint(NiColorA* a_result, TintMask* a_tintMask, bool a_fromTint);
		void			UpdateNeck(BSFaceGenNiNode* a_faceNode);
	public:
		Skills              playerSkills;
		TESClass*	        npcClass;
		HeadRelatedData*	headRelatedData;
		BGSListForm*        giftFilter;
		TESCombatStyle*     combatStyle;
		uint32_t            fileOffset;
		uint32_t            Unk1D4;
		TESRace*            originalRace;
		TESNPC*             faceNPC;
		float               height;
		float               weight;
		Sounds*			    sounds;
		BSFixedString       shortName;
		TESObjectARMO*      farSkin;
		BGSOutfit*          defaultOutfit;
		BGSOutfit*          sleepOutfit;
		BGSListForm*        defaultPackList;
		TESFaction*         crimeFaction;
		BGSHeadPart**       headParts;
		int8_t			    numHeadParts;
		int8_t		        Unk231;
		int8_t		        Unk232;
		int8_t		        Unk233;
		int8_t		        Unk234;
		int8_t		        soundLevel;
		Color			    bodyTintColor;
		uint16_t            Unk23A;
		uint32_t            Unk23C;
		BSTArray<void*>*	relationships;
		FaceData*		    faceData;
		BSTArray<void*>*    tintLayers;
	};
	static_assert(sizeof(TESNPC) == 0x258);
}