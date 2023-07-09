#include "../Weather/PapyrusExtWeather.h"

#include "../../../../../../source/A/ActorValueList.h"
#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/S/SpellItem.h"
#include "../../../../../../source/T/TESObjectWEAP.h"
#include "../../../../../../source/T/TESObjectSTAT.h"
#include "../../../../../../source/B/BGSEquipSlot.h"

namespace PapyrusExtWeapon
{
	// I really hate doing this...
	using namespace ConsoleRE;

	uint32_t GetBaseDamage(TESObjectWEAP* thisWeapon)
	{
		return (thisWeapon) ? thisWeapon->attackDamage : 0;
	}

	void	 SetBaseDamage(TESObjectWEAP* thisWeapon, uint32_t nuDamage)
	{
		if (thisWeapon) 
		{
			thisWeapon->attackDamage = nuDamage;
		}
	}

	uint32_t GetCritDamage(TESObjectWEAP* thisWeapon)
	{
		return (thisWeapon) ? thisWeapon->criticalData.damage : 0;
	}

	void	 SetCritDamage(TESObjectWEAP* thisWeapon, uint32_t critDamage)
	{
		if (thisWeapon) 
		{
			thisWeapon->criticalData.damage = critDamage;
		}
	}

	float	 GetReach(TESObjectWEAP* thisWeapon)
	{
		return (thisWeapon) ? thisWeapon->weaponData.reach : 0;
	}

	void	 SetReach(TESObjectWEAP* thisWeapon, float nuReach)
	{
		if (thisWeapon) 
		{
			thisWeapon->weaponData.reach = nuReach;
		}
	}

	float    GetSpeed(TESObjectWEAP* thisWeapon)
	{
		return (thisWeapon) ? thisWeapon->weaponData.speed : 0.0f;
	}

	void	 SetSpeed(TESObjectWEAP* thisWeapon, float speed)
	{
		if (thisWeapon) 
		{
			thisWeapon->weaponData.speed = speed;
		}
	}

	float	 GetStagger(TESObjectWEAP* thisWeapon)
	{
		return (thisWeapon) ? thisWeapon->weaponData.staggerValue : 0.0f;
	}

	void	 SetStagger(TESObjectWEAP* thisWeapon, float stagger)
	{
		if (thisWeapon) 
		{
			thisWeapon->weaponData.staggerValue = stagger;
		}
	}

	float GetMinRange(TESObjectWEAP* thisWeapon)
	{
		return (thisWeapon) ? thisWeapon->weaponData.minRange : 0.0f;
	}

	void SetMinRange(TESObjectWEAP* thisWeapon, float minRange)
	{
		if (thisWeapon)
		{
			thisWeapon->weaponData.minRange = minRange;
		}
	}

	float GetMaxRange(TESObjectWEAP* thisWeapon)
	{
		return (thisWeapon) ? thisWeapon->weaponData.maxRange : 0.0f;
	}

	void SetMaxRange(TESObjectWEAP* thisWeapon, float maxRange)
	{
		if (thisWeapon)
		{
			thisWeapon->weaponData.maxRange = maxRange;
		}
	}

	uint32_t GetWeaponType(TESObjectWEAP* thisWeapon)
	{
		return (thisWeapon) ? thisWeapon->weaponData.animationType : 0;
	}

	void SetWeaponType(TESObjectWEAP* thisWeapon, uint32_t nuType)
	{
		if (thisWeapon) 
		{
			thisWeapon->weaponData.animationType = nuType;
		}
	}

	BSFixedString GetModelPath(TESObjectWEAP* thisWeapon)
	{
		return (thisWeapon) ? static_cast<TESModelTextureSwap*>(thisWeapon)->GetModel() : NULL;
	}

	void SetModelPath(TESObjectWEAP* thisWeapon, BSFixedString nuPath)
	{
		if (thisWeapon) 
		{
			thisWeapon->SetModel(nuPath.m_data);
		}
	}

	EnchantmentItem* GetEnchantment(TESObjectWEAP* thisWeapon)
	{
		return (thisWeapon) ? static_cast<TESEnchantableForm*>(thisWeapon)->formEnchanting : NULL;
	}

	void SetEnchantment(TESObjectWEAP* thisWeapon, EnchantmentItem* enchantment)
	{
		if (thisWeapon) 
		{
			static_cast<TESEnchantableForm*>(thisWeapon)->formEnchanting = enchantment;
		}
	}

	uint32_t GetEnchantmentValue(TESObjectWEAP* thisWeapon)
	{
		return (thisWeapon && static_cast<TESEnchantableForm*>(thisWeapon)->formEnchanting) ? static_cast<TESEnchantableForm*>(thisWeapon)->castingType : 0;
	}

	void SetEnchantmentValue(TESObjectWEAP* thisWeapon, uint32_t value)
	{
		if (thisWeapon && static_cast<TESEnchantableForm*>(thisWeapon)->formEnchanting)
		{
			static_cast<TESEnchantableForm*>(thisWeapon)->castingType = value;
		}
	}

	TESObjectSTAT * GetEquippedModel(TESObjectWEAP* thisWeapon)
	{
		return (thisWeapon) ? thisWeapon->firstPersonModelObject : NULL;
	}

	void SetEquippedModel(TESObjectWEAP* thisWeapon, TESObjectSTAT * model)
	{
		if (thisWeapon) 
		{
			thisWeapon->firstPersonModelObject = model;
		}
	}

	BGSEquipSlot * GetEquipType(TESObjectWEAP* thisWeapon)
	{
		if (thisWeapon) 
		{
			return thisWeapon->equipSlot;
		}

		return NULL;
	}

	void SetEquipType(TESObjectWEAP* thisWeapon, BGSEquipSlot * slot)
	{
		if (thisWeapon && slot) 
		{
			thisWeapon->equipSlot = slot;
		}
	}

	SpellItem * GetCritEffect(TESObjectWEAP* thisWeapon)
	{
		return (thisWeapon) ? thisWeapon->criticalData.effect : NULL;
	}

	void SetCritEffect(TESObjectWEAP* thisWeapon, SpellItem * spell)
	{
		if (thisWeapon) 
		{
			thisWeapon->criticalData.effect = spell;
		}
	}

	bool GetCritEffectOnDeath(TESObjectWEAP* thisWeapon)
	{
		return (thisWeapon) ? (thisWeapon->criticalData.flags != 0) : false;
	}

	void SetCritEffectOnDeath(TESObjectWEAP* thisWeapon, bool critOnDeath)
	{
		if (thisWeapon) 
		{
			thisWeapon->criticalData.flags = (uint8_t)critOnDeath;
		}
	}

	float GetCritMultiplier(TESObjectWEAP* thisWeapon)
	{
		return (thisWeapon) ? thisWeapon->criticalData.prcntMult : 0.0f;
	}
	
	void SetCritMultiplier(TESObjectWEAP* thisWeapon, float critMult)
	{
		if (thisWeapon) 
		{
			thisWeapon->criticalData.prcntMult = critMult;
		}
	}

	TESObjectWEAP* GetTemplate(TESObjectWEAP* thisWeapon)
	{
		return (thisWeapon) ? thisWeapon->templateWeapon : NULL;
	}


	// good?
	BSFixedString GetSkill(TESObjectWEAP* thisWeapon)
	{
		if (!thisWeapon)
			return "";

		ActorValueList* avList = ActorValueList::GetSingleton();
		if (!avList)
			return "";

		ActorValueInfo* info = avList->GetActorValue((ActorValue)thisWeapon->weaponData.skill);
		if (!info)
			return "";

		return info->name;
	}

	void SetSkill(TESObjectWEAP* thisWeapon, BSFixedString skill)
	{
		if (thisWeapon)
		{
			uint32_t actorValue = (uint32_t)ActorValueList::GetSingleton()->LookupActorValueByName(skill.m_data);
			if (actorValue >= 164)
				actorValue = 255;

			thisWeapon->weaponData.skill = actorValue;
		}
	}

	BSFixedString GetResist(TESObjectWEAP* thisWeapon)
	{
		if (!thisWeapon)
			return "";
	
		ActorValueList * avList = ActorValueList::GetSingleton();
		if (!avList)
			return "";
	
		ActorValueInfo * info = avList->GetActorValue((ActorValue)thisWeapon->weaponData.resistance);
		if (!info)
			return "";
	
		return info->name;
	}

	void SetResist(TESObjectWEAP* thisWeapon, BSFixedString resist)
	{
		if (thisWeapon) 
		{
			uint32_t actorValue = (uint32_t)ActorValueList::GetSingleton()->LookupActorValueByName(resist.m_data);
			if (actorValue >= 164)
				actorValue = 255;

			thisWeapon->weaponData.resistance = actorValue;
		}
	}

	bool RegisterWeapon(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetTemplate),          TESObjectWEAP, TESObjectWEAP*>        ("GetTemplate",          "Weapon", GetTemplate));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetWeaponType),        TESObjectWEAP, uint32_t>              ("GetWeaponType",        "Weapon", GetWeaponType));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetWeaponType),        TESObjectWEAP, void, uint32_t>        ("SetWeaponType",        "Weapon", SetWeaponType));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetBaseDamage),        TESObjectWEAP, uint32_t>              ("GetBaseDamage",        "Weapon", GetBaseDamage));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetBaseDamage),        TESObjectWEAP, void, uint32_t>        ("SetBaseDamage",        "Weapon", SetBaseDamage));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetCritDamage),        TESObjectWEAP, uint32_t>              ("GetCritDamage",        "Weapon", GetCritDamage));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetCritDamage),        TESObjectWEAP, void, uint32_t>        ("SetCritDamage",        "Weapon", SetCritDamage));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetReach),             TESObjectWEAP, float>                 ("GetReach",             "Weapon", GetReach));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetReach),             TESObjectWEAP, void, float>           ("SetReach",             "Weapon", SetReach));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetMinRange),          TESObjectWEAP, float>                 ("GetMinRange",          "Weapon", GetMinRange));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetMinRange),          TESObjectWEAP, void, float>           ("SetMinRange",          "Weapon", SetMinRange));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetMaxRange),          TESObjectWEAP, float>                 ("GetMaxRange",          "Weapon", GetMaxRange));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetMaxRange),          TESObjectWEAP, void, float>           ("SetMaxRange",          "Weapon", SetMaxRange));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetSpeed),             TESObjectWEAP, float>                 ("GetSpeed",             "Weapon", GetSpeed));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetSpeed),             TESObjectWEAP, void, float>           ("SetSpeed",             "Weapon", SetSpeed));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetStagger),           TESObjectWEAP, float>                 ("GetStagger",           "Weapon", GetStagger));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetStagger),           TESObjectWEAP, void, float>           ("SetStagger",           "Weapon", SetStagger));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetModelPath),         TESObjectWEAP, BSFixedString>         ("GetModelPath",         "Weapon", GetModelPath));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetModelPath),         TESObjectWEAP, void, BSFixedString>   ("SetModelPath",         "Weapon", SetModelPath));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetEnchantment),       TESObjectWEAP, EnchantmentItem*>      ("GetEnchantment",       "Weapon", GetEnchantment));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetEnchantment),       TESObjectWEAP, void, EnchantmentItem*>("SetEnchantment",       "Weapon", SetEnchantment));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetEnchantmentValue),  TESObjectWEAP, uint32_t>              ("GetEnchantmentValue",  "Weapon", GetEnchantmentValue));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetEnchantmentValue),  TESObjectWEAP, void, uint32_t>        ("SetEnchantmentValue",  "Weapon", SetEnchantmentValue));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetEquippedModel),     TESObjectWEAP, TESObjectSTAT*>        ("GetEquippedModel",     "Weapon", GetEquippedModel));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetEquippedModel),     TESObjectWEAP, void, TESObjectSTAT*>  ("SetEquippedModel",     "Weapon", SetEquippedModel));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetEquipType),         TESObjectWEAP, BGSEquipSlot*>         ("GetEquipType",         "Weapon", GetEquipType));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetEquipType),         TESObjectWEAP, void, BGSEquipSlot*>   ("SetEquipType",         "Weapon", SetEquipType));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetSkill),             TESObjectWEAP, BSFixedString>         ("GetSkill",             "Weapon", GetSkill));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetSkill),             TESObjectWEAP, void, BSFixedString>   ("SetSkill",             "Weapon", SetSkill));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetResist),            TESObjectWEAP, BSFixedString>         ("GetResist",            "Weapon", GetResist));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetResist),            TESObjectWEAP, void, BSFixedString>   ("SetResist",            "Weapon", SetResist));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetCritEffect),        TESObjectWEAP, SpellItem*>            ("GetCritEffect",        "Weapon", GetCritEffect));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetCritEffect),        TESObjectWEAP, void, SpellItem*>      ("SetCritEffect",        "Weapon", SetCritEffect));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetCritEffectOnDeath), TESObjectWEAP, bool>                  ("GetCritEffectOnDeath", "Weapon", GetCritEffectOnDeath));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetCritEffectOnDeath), TESObjectWEAP, void, bool>            ("SetCritEffectOnDeath", "Weapon", SetCritEffectOnDeath));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetCritMultiplier),    TESObjectWEAP, float>                 ("GetCritMultiplier",    "Weapon", GetCritMultiplier));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetCritMultiplier),    TESObjectWEAP, void, float>           ("SetCritMultiplier",    "Weapon", SetCritMultiplier));

		return true;
	}
}