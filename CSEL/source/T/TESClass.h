#pragma once

#include "../T/TESDescription.h"
#include "../T/TESForm.h"
#include "../T/TESFullName.h"
#include "../T/TESTexture.h"

namespace ConsoleRE
{
	struct CLASS_DATA
	{
	public:
		enum class Skill
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
		};

		struct SkillWeights
		{
		public:
			uint8_t oneHanded;
			uint8_t twoHanded;
			uint8_t archery;
			uint8_t block;
			uint8_t smithing;
			uint8_t heavyArmor;
			uint8_t lightArmor; 
			uint8_t pickpocket; 
			uint8_t lockpicking;
			uint8_t sneak;
			uint8_t alchemy;
			uint8_t speech;
			uint8_t alteration;
			uint8_t conjuration;
			uint8_t destruction;
			uint8_t illusion;
			uint8_t restoration;
			uint8_t enchanting;
		};
		static_assert(sizeof(SkillWeights) == 0x12);

		struct AttributeWeights
		{
		public:
			uint8_t health;
			uint8_t magicka;
			uint8_t stamina;
		};
		static_assert(sizeof(AttributeWeights) == 0x3);
	public:
		uint32_t								unk00;
		uint8_t									teaches;
		uint8_t									maximumTrainingLevel;
		SkillWeights							skillWeights;
		float									bleedoutDefault;
		uint32_t								voicePoints;
		AttributeWeights						attributeWeights;
		uint8_t									pad23;
	};
	static_assert(sizeof(CLASS_DATA) == 0x24);

	class TESClass : public TESForm, public TESFullName, public TESDescription, public TESTexture
	{
	public:
		static constexpr int TypeID = 10;
	public:
		~TESClass() override;

		// override (TESForm)
		void InitializeData() override;
		bool Load(TESFile* a_mod) override;
	public:
		CLASS_DATA    data;
	};
	static_assert(sizeof(TESClass) == 0x78);
}