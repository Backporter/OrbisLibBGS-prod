#pragma once

#include "../B/BGSBodyPartDefs.h"
#include "../B/BGSPreloadable.h"
#include "../B/BSFixedString.h"
#include "../N/NiPoint3.h"
#include "../T/TESForm.h"
#include "../T/TESModel.h"
#include "../T/TESModelPSA.h"

namespace ConsoleRE
{
	class BGSRagdoll;
	class BGSImpactDataSet;
	class BGSExplosion;
	class BGSDebris;

	struct PART_DATA
	{
	public:
		float														damageMult;
		uint8_t														flags;
		uint8_t														type;
		int8_t														healthPercent;
		uint8_t														actorValue;
		int8_t														toHitChance;
		int8_t														explosionChance;
		int8_t														explosionGenericDebrisCount;
		uint8_t														pad0B;
		uint32_t													pad0C;
		BGSDebris*													explosionGenericDebris;
		BGSExplosion*												explosion;
		float														trackingMaxAngle;
		float														explosionGenericDebrisScale;
		int8_t														dismemberGenericDebrisCount;
		int8_t														unk29;
		uint16_t													unk2A;
		uint32_t													unk2C;
		BGSDebris*													dismemberGenericDebris;
		BGSExplosion*												dismemberExplosion;
		float														dismemberGenericDebrisScale;
		NiPoint3													goreTranslate;
		NiPoint3													goreRotate;
		uint32_t													pad5C;
		BGSImpactDataSet*											dismemberImpactDataSet;
		BGSImpactDataSet*											explosionImpactDataSet;
		int8_t														dismemberDecalCount;
		int8_t														explosionDecalCount;
		uint16_t													pad72;
		float														explosionSpecialDebrisScale;
		uint32_t													pad78;
	};
	static_assert(sizeof(PART_DATA) == 0x80);

	class BGSBodyPart
	{
	public:
		BSFixedString nodeName;
		BSFixedString targetName;
		BSFixedString hitReactionVariablePrefix;
		BSFixedString partName;
		BSFixedString goreObjectName;
		TESModel      explosionSpecialDebris;
		TESModelPSA   poseMatching; 
		PART_DATA     data;
	};

	class BGSBodyPartData : public TESForm, public TESModel, public BGSPreloadable
	{
	public:
		static constexpr int TypeID = 93;
		
		~BGSBodyPartData() override;
	public:
		BGSBodyPart* parts[BGSBodyPartDefs::LIMB_ENUM::kTotal];
		BGSRagdoll*  ragdoll;
	};
	static_assert(sizeof(BGSBodyPartData) == 0x88);
}