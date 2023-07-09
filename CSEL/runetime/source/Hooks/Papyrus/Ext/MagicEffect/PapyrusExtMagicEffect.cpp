#include "../MagicEffect/PapyrusExtMagicEffect.h"

#include "../../../../../../source/A/ActorValueList.h"
#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/B/BGSProjectile.h"
#include "../../../../../../source/B/BGSArtObject.h"
#include "../../../../../../source/B/BGSExplosion.h"

#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/E/EffectSetting.h"
#include "../../../../../../source/T/TESSound.h"
#include "../../../../../../source/S/SpellItem.h"
#include "../../../../../../source/B/BGSImpactDataSet.h"
#include "../../../../../../source/T/TESImageSpaceModifier.h"
#include "../../../../../../source/B/BGSSoundDescriptorForm.h"

#include "../../../../../../source/T/TESObjectLIGH.h"
#include "../../../../../../source/T/TESEffectShader.h"
#include "../../../../../../source/P/PackUnpackImpl.h"

namespace PapyrusExtMagicEffect
{
	// I really hate doing this...
	using namespace ConsoleRE;
	
	std::vector<BGSSoundDescriptorForm*> GetSounds(EffectSetting* thisEffect)
	{
		std::vector<BGSSoundDescriptorForm*> sounds;
		sounds.resize(6, NULL);
	
		if (thisEffect)
		{
			for (uint32_t i = 0; i < thisEffect->effectSounds.size(); i++)
			{
				EffectSetting::SoundInfo sInfo;
				thisEffect->effectSounds.Get(i, sInfo);
	
				if (std::underlying_type_t<MagicSystem::SoundID>(sInfo.id) < sounds.size())
				{
					sounds.at(std::underlying_type_t<MagicSystem::SoundID>(sInfo.id)) = sInfo.sound;
				}
			}
		}
	
		return sounds;
	}

	bool IsEffectFlagSet(EffectSetting* thisEffect, uint32_t flag)
	{
		return (thisEffect) ? (thisEffect->data.flags & flag) == flag : false;
	}

	void SetEffectFlag(EffectSetting* thisEffect, uint32_t flag)
	{
		if (thisEffect)
			thisEffect->data.flags |= flag;
	}

	void ClearEffectFlag(EffectSetting* thisEffect, uint32_t flag)
	{
		if (thisEffect)
			thisEffect->data.flags &= ~flag;
	}

	float GetCastTime(EffectSetting* thisEffect)
	{
		return (thisEffect) ? thisEffect->data.spellmakingChargeTime : 0.0;
	}

	void SetCastTime(EffectSetting* thisEffect, float castTime)
	{
		if (thisEffect)
			thisEffect->data.spellmakingChargeTime = castTime;
	}

	uint32_t GetSkillLevel(EffectSetting* thisEffect)
	{
		return (thisEffect) ? thisEffect->data.minimumSkill : 0;
	}

	void SetSkillLevel(EffectSetting* thisEffect, uint32_t level)
	{
		if (thisEffect)
			thisEffect->data.minimumSkill = level;
	}

	uint32_t GetArea(EffectSetting* thisEffect)
	{
		return (thisEffect) ? thisEffect->data.spellmakingArea : 0;
	}

	void SetArea(EffectSetting* thisEffect, uint32_t area)
	{
		if (thisEffect)
			thisEffect->data.spellmakingArea = area;
	}

	float GetSkillUsageMult(EffectSetting* thisEffect)
	{
		return (thisEffect) ? thisEffect->data.skillUsageMult : 0.0;
	}

	void SetSkillUsageMult(EffectSetting* thisEffect, float skillMult)
	{
		if (thisEffect)
			thisEffect->data.skillUsageMult = skillMult;
	}

	float GetBaseCost(EffectSetting* thisEffect)
	{
		return (thisEffect) ? thisEffect->data.baseCost : 0.0;
	}

	void SetBaseCost(EffectSetting* thisEffect, float baseCost)
	{
		if (thisEffect)
			thisEffect->data.baseCost = baseCost;
	}

	TESObjectLIGH* GetLight(EffectSetting* thisEffect)
	{
		return (thisEffect) ? thisEffect->data.light : NULL;
	}

	void SetLight(EffectSetting* thisEffect, TESObjectLIGH * obj)
	{
		if (thisEffect)
			thisEffect->data.light = obj;
	}

	TESEffectShader* GetHitShader(EffectSetting* thisEffect)
	{
		return (thisEffect) ? thisEffect->data.effectShader : NULL;
	}

	void SetHitShader(EffectSetting* thisEffect, TESEffectShader * obj)
	{
		if (thisEffect)
			thisEffect->data.effectShader = obj;
	}

	TESEffectShader* GetEnchantShader(EffectSetting* thisEffect)
	{
		return (thisEffect) ? thisEffect->data.enchantShader : NULL;
	}

	void SetEnchantShader(EffectSetting* thisEffect, TESEffectShader * obj)
	{
		if (thisEffect)
			thisEffect->data.enchantShader = obj;
	}

	BGSProjectile* GetProjectile(EffectSetting* thisEffect)
	{
		return (thisEffect) ? thisEffect->data.projectileBase : NULL;
	}

	void SetProjectile(EffectSetting* thisEffect, BGSProjectile * obj)
	{
		if (thisEffect)
			thisEffect->data.projectileBase = obj;
	}

	BGSExplosion* GetExplosion(EffectSetting* thisEffect)
	{
		return (thisEffect) ? thisEffect->data.explosion : NULL;
	}

	void SetExplosion(EffectSetting* thisEffect, BGSExplosion * obj)
	{
		if (thisEffect)
			thisEffect->data.explosion = obj;
	}

	BGSArtObject* GetCastingArt(EffectSetting* thisEffect)
	{
		return (thisEffect) ? thisEffect->data.castingArt : NULL;
	}

	void SetCastingArt(EffectSetting* thisEffect, BGSArtObject * obj)
	{
		if (thisEffect)
			thisEffect->data.castingArt = obj;
	}

	BGSArtObject* GetHitEffectArt(EffectSetting* thisEffect)
	{
		return (thisEffect) ? thisEffect->data.hitEffectArt : NULL;
	}

	void SetHitEffectArt(EffectSetting* thisEffect, BGSArtObject * obj)
	{
		if (thisEffect)
			thisEffect->data.hitEffectArt = obj;
	}

	BGSImpactDataSet* GetImpactDataSet(EffectSetting* thisEffect)
	{
		return (thisEffect) ? thisEffect->data.impactDataSet : NULL;
	}

	void SetImpactDataSet(EffectSetting* thisEffect, BGSImpactDataSet * obj)
	{
		if (thisEffect)
			thisEffect->data.impactDataSet = obj;
	}

	BGSArtObject* GetEnchantArt(EffectSetting* thisEffect)
	{
		return (thisEffect) ? thisEffect->data.enchantEffectArt : NULL;
	}

	void SetEnchantArt(EffectSetting* thisEffect, BGSArtObject * obj)
	{
		if (thisEffect)
			thisEffect->data.enchantEffectArt = obj;
	}

	SpellItem* GetEquipAbility(EffectSetting* thisEffect)
	{
		return (thisEffect) ? thisEffect->data.equipAbility : NULL;
	}

	void SetEquipAbility(EffectSetting* thisEffect, SpellItem * obj)
	{
		if (thisEffect)
			thisEffect->data.equipAbility = obj;
	}

	TESImageSpaceModifier* GetImageSpaceMod(EffectSetting* thisEffect)
	{
		return (thisEffect) ? thisEffect->data.imageSpaceMod : NULL;
	}

	void SetImageSpaceMod(EffectSetting* thisEffect, TESImageSpaceModifier * obj)
	{
		if (thisEffect)
			thisEffect->data.imageSpaceMod = obj;
	}

	BGSPerk* GetPerk(EffectSetting* thisEffect)
	{
		return (thisEffect) ? thisEffect->data.perk : NULL;
	}

	void SetPerk(EffectSetting* thisEffect, BGSPerk * obj)
	{
		if (thisEffect)
			thisEffect->data.perk = obj;
	}

	uint32_t GetCastingType(EffectSetting* thisEffect)
	{
		return (thisEffect) ? thisEffect->data.castingType : 0;
	}

	uint32_t GetDeliveryType(EffectSetting* thisEffect)
	{
		return (thisEffect) ? thisEffect->data.delivery : 0;
	}

	// ?
	void SetAssociatedSkill(EffectSetting* thisEffect, BSFixedString school)
	{
		if (thisEffect) 
		{
			uint32_t actorValue = (uint32_t)ActorValueList::GetSingleton()->LookupActorValueByName(school.m_data);
			if (actorValue >= 164)
				actorValue = 255;

			thisEffect->data.associatedSkill = actorValue;
		}
	}
	
	BSFixedString GetResistance(EffectSetting* thisEffect)
	{
		if (!thisEffect)
			return "";
	
		ActorValueList * avList = ActorValueList::GetSingleton();
		if (!avList)
			return "";
	
		ActorValueInfo * info = avList->GetActorValue((ActorValue)thisEffect->data.resistVariable);
		if (!info)
			return "";
	
		return info->name;
	}
	
	void SetResistance(EffectSetting* thisEffect, BSFixedString resistance)
	{
		if (thisEffect) 
		{
			uint32_t actorValue = (uint32_t)ActorValueList::GetSingleton()->LookupActorValueByName(resistance.m_data);
			if (actorValue >= 164)
				actorValue = 255;

			thisEffect->data.resistVariable = actorValue;
		}
	}

	bool RegisterMagicEffect(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		//
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetSounds),                 EffectSetting, std::vector<BGSSoundDescriptorForm*>>			("GetSounds",          "MagicEffect", GetSounds));
		//

		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(IsEffectFlagSet),           EffectSetting, bool, uint32_t>								("IsEffectFlagSet",    "MagicEffect", IsEffectFlagSet));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetEffectFlag),             EffectSetting, void, uint32_t>								("SetEffectFlag",      "MagicEffect", SetEffectFlag));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(ClearEffectFlag),           EffectSetting, void, uint32_t>								("ClearEffectFlag",    "MagicEffect", ClearEffectFlag));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetCastTime),               EffectSetting, float>										("GetCastTime",        "MagicEffect", GetCastTime));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetCastTime),               EffectSetting, void, float>									("SetCastTime",        "MagicEffect", SetCastTime));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetSkillLevel),             EffectSetting, uint32_t>										("GetSkillLevel",      "MagicEffect", GetSkillLevel));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetSkillLevel),             EffectSetting, void, uint32_t>								("SetSkillLevel",      "MagicEffect", SetSkillLevel));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetArea),                   EffectSetting, uint32_t>										("GetArea",            "MagicEffect", GetArea));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetArea),                   EffectSetting, void, uint32_t>								("SetArea",            "MagicEffect", SetArea));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetSkillUsageMult),         EffectSetting, float>										("GetSkillUsageMult",  "MagicEffect", GetSkillUsageMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetSkillUsageMult),         EffectSetting, void, float>									("SetSkillUsageMult",  "MagicEffect", SetSkillUsageMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetBaseCost),               EffectSetting, float>										("GetBaseCost",        "MagicEffect", GetBaseCost));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetBaseCost),               EffectSetting, void, float>									("SetBaseCost",        "MagicEffect", SetBaseCost));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetAssociatedSkill),		   EffectSetting, void, BSFixedString>							("SetAssociatedSkill", "MagicEffect", SetAssociatedSkill));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetResistance),			   EffectSetting, BSFixedString>								("GetResistance",      "MagicEffect", GetResistance));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetResistance),			   EffectSetting, void, BSFixedString>							("SetResistance",      "MagicEffect", SetResistance));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetLight),                  EffectSetting, TESObjectLIGH*>								("GetLight",           "MagicEffect", GetLight));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetLight),                  EffectSetting, void, TESObjectLIGH*>							("SetLight",           "MagicEffect", SetLight));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetHitShader),              EffectSetting, TESEffectShader*>								("GetHitShader",       "MagicEffect", GetHitShader));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetHitShader),              EffectSetting, void, TESEffectShader*>						("SetHitShader",       "MagicEffect", SetHitShader));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetEnchantShader),          EffectSetting, TESEffectShader*>								("GetEnchantShader",   "MagicEffect", GetEnchantShader));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetEnchantShader),	       EffectSetting, void, TESEffectShader*>						("SetEnchantShader",   "MagicEffect", SetEnchantShader));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetProjectile),		       EffectSetting, BGSProjectile*>								("GetProjectile",      "MagicEffect", GetProjectile));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetProjectile),		       EffectSetting, void, BGSProjectile*>							("SetProjectile",      "MagicEffect", SetProjectile));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetExplosion),		       EffectSetting, BGSExplosion*>								("GetExplosion",       "MagicEffect", GetExplosion));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetExplosion),		       EffectSetting, void, BGSExplosion*>							("SetExplosion",       "MagicEffect", SetExplosion));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetCastingArt),		       EffectSetting, BGSArtObject*>								("GetCastingArt",      "MagicEffect", GetCastingArt));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetCastingArt),		       EffectSetting, void, BGSArtObject*>							("SetCastingArt",      "MagicEffect", SetCastingArt));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetHitEffectArt),           EffectSetting, BGSArtObject*>								("GetHitEffectArt",    "MagicEffect", GetHitEffectArt));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetHitEffectArt),           EffectSetting, void, BGSArtObject*>							("SetHitEffectArt",    "MagicEffect", SetHitEffectArt));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetEnchantArt),             EffectSetting, BGSArtObject*>								("GetEnchantArt",      "MagicEffect", GetEnchantArt));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetEnchantArt),             EffectSetting, void, BGSArtObject*>							("SetEnchantArt",      "MagicEffect", SetEnchantArt));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetImpactDataSet),          EffectSetting, BGSImpactDataSet*>							("GetImpactDataSet",   "MagicEffect", GetImpactDataSet));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetImpactDataSet),          EffectSetting, void, BGSImpactDataSet*>						("SetImpactDataSet",   "MagicEffect", SetImpactDataSet));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetEquipAbility),           EffectSetting, SpellItem*>									("GetEquipAbility",    "MagicEffect", GetEquipAbility));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetEquipAbility),           EffectSetting, void, SpellItem*>								("SetEquipAbility",    "MagicEffect", SetEquipAbility));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetImageSpaceMod),          EffectSetting, TESImageSpaceModifier*>						("GetImageSpaceMod",   "MagicEffect", GetImageSpaceMod));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetImageSpaceMod),          EffectSetting, void, TESImageSpaceModifier*>					("SetImageSpaceMod",   "MagicEffect", SetImageSpaceMod));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetPerk),                   EffectSetting, BGSPerk*>										("GetPerk",            "MagicEffect", GetPerk));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetPerk),                   EffectSetting, void, BGSPerk*>								("SetPerk",            "MagicEffect", SetPerk));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetCastingType),            EffectSetting, uint32_t>										("GetCastingType",     "MagicEffect", GetCastingType));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetDeliveryType),           EffectSetting, uint32_t>										("GetDeliveryType",    "MagicEffect", GetDeliveryType));
		
		VM->SetCallableFromTasklets("MagicEffect", "IsEffectFlagSet",    true);
		VM->SetCallableFromTasklets("MagicEffect", "SetEffectFlag",      true);
		VM->SetCallableFromTasklets("MagicEffect", "ClearEffectFlag",    true);
		VM->SetCallableFromTasklets("MagicEffect", "GetCastTime",        true);
		VM->SetCallableFromTasklets("MagicEffect", "SetCastTime",        true);
		VM->SetCallableFromTasklets("MagicEffect", "GetSkillLevel",      true);
		VM->SetCallableFromTasklets("MagicEffect", "SetSkillLevel",      true);
		VM->SetCallableFromTasklets("MagicEffect", "GetArea",            true);
		VM->SetCallableFromTasklets("MagicEffect", "SetArea",            true);
		VM->SetCallableFromTasklets("MagicEffect", "GetSkillUsageMult",  true);
		VM->SetCallableFromTasklets("MagicEffect", "SetSkillUsageMult",  true);
		VM->SetCallableFromTasklets("MagicEffect", "GetBaseCost",        true);
		VM->SetCallableFromTasklets("MagicEffect", "SetBaseCost",        true);
		VM->SetCallableFromTasklets("MagicEffect", "SetAssociatedSkill", true);
		VM->SetCallableFromTasklets("MagicEffect", "GetResistance",      true);
		VM->SetCallableFromTasklets("MagicEffect", "SetResistance",      true);
		VM->SetCallableFromTasklets("MagicEffect", "GetLight",           true);
		VM->SetCallableFromTasklets("MagicEffect", "SetLight",           true);
		VM->SetCallableFromTasklets("MagicEffect", "GetHitShader",       true);
		VM->SetCallableFromTasklets("MagicEffect", "SetHitShader",       true);
		VM->SetCallableFromTasklets("MagicEffect", "GetEnchantShader",   true);
		VM->SetCallableFromTasklets("MagicEffect", "SetEnchantShader",   true);
		VM->SetCallableFromTasklets("MagicEffect", "GetProjectile",      true);
		VM->SetCallableFromTasklets("MagicEffect", "SetProjectile",      true);
		VM->SetCallableFromTasklets("MagicEffect", "GetExplosion",       true);
		VM->SetCallableFromTasklets("MagicEffect", "SetExplosion",       true);
		VM->SetCallableFromTasklets("MagicEffect", "GetCastingArt",      true);
		VM->SetCallableFromTasklets("MagicEffect", "SetCastingArt",      true);
		VM->SetCallableFromTasklets("MagicEffect", "GetHitEffectArt",    true);
		VM->SetCallableFromTasklets("MagicEffect", "SetHitEffectArt",    true);
		VM->SetCallableFromTasklets("MagicEffect", "GetImpactDataSet",   true);
		VM->SetCallableFromTasklets("MagicEffect", "SetImpactDataSet",   true);
		VM->SetCallableFromTasklets("MagicEffect", "GetEnchantArt",      true);
		VM->SetCallableFromTasklets("MagicEffect", "SetEnchantArt",      true);
		VM->SetCallableFromTasklets("MagicEffect", "GetEquipAbility",    true);
		VM->SetCallableFromTasklets("MagicEffect", "SetEquipAbility",    true);
		VM->SetCallableFromTasklets("MagicEffect", "GetImageSpaceMod",   true);
		VM->SetCallableFromTasklets("MagicEffect", "SetImageSpaceMod",   true);
		VM->SetCallableFromTasklets("MagicEffect", "GetPerk",            true);
		VM->SetCallableFromTasklets("MagicEffect", "SetPerk",            true);
		VM->SetCallableFromTasklets("MagicEffect", "GetCastingType",     true);
		VM->SetCallableFromTasklets("MagicEffect", "GetDeliveryType",    true);

		return true;
	}
}