#include "../ActorValueInfo/PapyrusExtActorValueInfo.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/A/ActorValueInfo.h"
#include "../../../../../../source/A/ActorValueList.h"
#include "../../../../../../source/P/PlayerCharacter.h"
#include "../../../../../../source/I/INISettingCollection.h"
#include "../../../../../../source/B/BGSSkillPerkTreeNode.h"

#include "../../../../../../source/Helper.h"

//
#include "../../../../../../source/P/PackUnpackImpl.h"
//

namespace PapyrusExtActorValueInfo
{
	// I really hate doing this...
	using namespace ConsoleRE;

	std::vector<BGSPerk*> GetPerks(ActorValueInfo* info, Actor* actor, bool unowned, bool allRanks)
	{
		std::vector<BGSPerk*> result;

		if (info) 
		{
			BGSSkillPerkTreeNode* root = info->perkTree;
			if (root) 
			{
				auto lambda = [&](BGSPerk* a_perk) -> bool
				{
					if (a_perk)
					{
						bool addPerk = true;
						if (actor)
						{
							if (!actor->HasPerk(a_perk))
							{
								addPerk = unowned;
							}
							else
							{
								addPerk = !unowned;
							}
						}

						if (addPerk)
						{
							result.push_back(a_perk);

						}

						if (allRanks)
						{
							BGSPerk* nextPerk = a_perk->nextPerk;
							while (nextPerk)
							{
								addPerk = true;
								if (actor)
								{
									if (!actor->HasPerk(nextPerk))
										addPerk = unowned;
									else
										addPerk = !unowned;
								}

								if (addPerk)
								{
									result.push_back(nextPerk);
								}

								nextPerk = nextPerk->nextPerk;
							}
						}
					}

					return false;
				};
				root->Visit(lambda);
			}
		}
	
		return result;
	}

	ActorValueInfo* GetActorValueInfoByName(StaticFunctionTag*, BSFixedString a_name)
	{
		auto* s_actorvalueslist = ActorValueList::GetSingleton();
		return s_actorvalueslist->GetActorValue(s_actorvalueslist->LookupActorValueByName(a_name.m_data));
	}
	
	ActorValueInfo * GetActorValueInfoByID(StaticFunctionTag * base, uint32_t actorValue)
	{
		ActorValueList * avList = ActorValueList::GetSingleton();
		if (avList)
			return avList->GetActorValue((ActorValue)actorValue);
		else
			return nullptr;
	}

	bool IsSkill(ActorValueInfo * info)
	{
		return (info && info->skill) ? true : false;
	}

	float GetSkillUseMult(ActorValueInfo * info)
	{
		return (info && info->skill) ? info->skill->useMult : 0.0;
	}

	void SetSkillUseMult(ActorValueInfo * info, float value)
	{
		if (info && info->skill)
			info->skill->useMult = value;
	}

	float GetSkillOffsetMult(ActorValueInfo * info)
	{
		return (info && info->skill) ? info->skill->offsetMult : 0.0;
	}

	void SetSkillOffsetMult(ActorValueInfo * info, float value)
	{
		if (info && info->skill)
			info->skill->offsetMult = value;
	}

	float GetSkillImproveMult(ActorValueInfo * info)
	{
		return (info && info->skill) ? info->skill->inproveMult : 0.0;
	}

	void SetSkillImproveMult(ActorValueInfo * info, float value)
	{
		if (info && info->skill)
			info->skill->inproveMult = value;
	}

	float GetSkillImproveOffset(ActorValueInfo * info)
	{
		return (info && info->skill) ? info->skill->inproveOffset : 0.0;
	}

	void SetSkillImproveOffset(ActorValueInfo * info, float value)
	{
		if (info && info->skill)
			info->skill->inproveOffset = value;
	}

	float GetSkillExperience(ActorValueInfo * info)
	{
		ConsoleRE::PlayerCharacter* pPC = ConsoleRE::PlayerCharacter::GetSingleton();
		return (info && pPC->Unk8E8) ? pPC->Unk8E8->GetSkillPoints(info->name) : 0.0;
	}

	void SetSkillExperience(ActorValueInfo * info, float points)
	{
		ConsoleRE::PlayerCharacter* pPC = ConsoleRE::PlayerCharacter::GetSingleton();
		if (info && pPC->Unk8E8)
		{
			pPC->Unk8E8->SetSkillPoints(info->name, points);
		}
	}

	void AddSkillExperience(ActorValueInfo* info, float points)
	{
		if (info) 
		{
			uint32_t actorValue = (uint32_t)ConsoleRE::ActorValueList::GetSingleton()->LookupActorValueByName(info->name);
			if (actorValue < 164) 
			{
				ConsoleRE::PlayerCharacter* pPC = ConsoleRE::PlayerCharacter::GetSingleton();
				pPC->AddSkillExperience(actorValue, points);
			}
		}
	}

	float GetExperienceForLevel(ActorValueInfo * info, uint32_t level)
	{
		if (!info || !info->skill)
			return 0.0;
		
		double fSkillUseCurve = 0.0;
		auto* settings = ConsoleRE::INISettingCollection::GetSingleton();
		if (!settings)
			return 0.0;
		
		Setting* skillUseCurve = settings->GetSetting("fSkillUseCurve");
		if (skillUseCurve)
			fSkillUseCurve = skillUseCurve->GetFloat();
		
		return info->skill[2].useMult * pow(level, fSkillUseCurve) + info->skill[3].useMult;
	}

	int32_t GetSkillLegendaryLevel(ActorValueInfo * info)
	{
		ConsoleRE::PlayerCharacter* pPC = ConsoleRE::PlayerCharacter::GetSingleton();
		if (pPC && info && pPC->Unk8E8)
		{
			return pPC->Unk8E8->GetSkillPoints(info->name, true);
		}
		
		return -1;
	}

	void SetSkillLegendaryLevel(ActorValueInfo * info, uint32_t level)
	{
		ConsoleRE::PlayerCharacter* pPC = ConsoleRE::PlayerCharacter::GetSingleton();
		if (pPC && info && pPC->Unk8E8)
		{
			pPC->Unk8E8->SetSkillPoints(info->name, level, true);
		}
	}

	void GetPerkTree(ActorValueInfo* info, BGSListForm* formList, Actor* actor, bool unowned, bool allRanks)
	{
		if (info && formList) 
		{
			BGSSkillPerkTreeNode * root = info->perkTree;
			if (root) 
			{
				auto lambda = [&](BGSPerk* a_perk) -> bool
				{
					if (a_perk)
					{
						bool addPerk = true;
						if (actor)
						{
							if (!actor->HasPerk(a_perk))
							{
								addPerk = unowned;
							}
							else
							{
								addPerk = !unowned;
							}
						}

						if (addPerk)
						{
							formList->AddForm(a_perk);

						}

						if (allRanks)
						{
							BGSPerk* nextPerk = a_perk->nextPerk;
							while (nextPerk)
							{
								addPerk = true;
								if (actor)
								{
									if (!actor->HasPerk(nextPerk))
										addPerk = unowned;
									else
										addPerk = !unowned;
								}

								if (addPerk)
								{
									formList->AddForm(nextPerk);
								}

								nextPerk = nextPerk->nextPerk;
							}
						}
					}

					return false;
				};
				root->Visit(lambda);
			}
		}
	}

	float GetCurrentValue(ActorValueInfo * info, Actor * actor)
	{
		if (info && actor) 
		{
			uint32_t actorValue = (uint32_t)ActorValueList::GetSingleton()->LookupActorValueByName(info->name);
			if (actorValue < 164) 
			{
				return static_cast<ActorValueOwner*>(actor)->GetActorValue(actorValue);
			}
		}
		return 0.0f;
	}

	float GetBaseValue(ActorValueInfo * info, Actor * actor)
	{
		if (info && actor) 
		{
			uint32_t actorValue = (uint32_t)ActorValueList::GetSingleton()->LookupActorValueByName(info->name);
			if (actorValue < 164)
			{
				return static_cast<ActorValueOwner*>(actor)->GetBaseActorValue(actorValue);
			}
		}

		return 0.0f;
	}

	float GetMaximumValue(ActorValueInfo * info, Actor * actor)
	{
		if (info && actor) 
		{
			uint32_t actorValue = (uint32_t)ActorValueList::GetSingleton()->LookupActorValueByName(info->name);
			if (actorValue < 164)
			{
				return static_cast<ActorValueOwner*>(actor)->GetPermanentActorValue(actorValue);
			}
		}

		return 0.0f;
	}

	bool RegisterActorValueInfo(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		//
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetPerks),						ActorValueInfo, std::vector<BGSPerk*>, Actor*, bool, bool>	("GetPerks",				"ActorValueInfo", GetPerks));
		//

		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetActorValueInfoByName),		StaticFunctionTag, ActorValueInfo*, BSFixedString>			("GetActorValueInfoByName", "ActorValueInfo", GetActorValueInfoByName));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetActorValueInfoByID),		StaticFunctionTag, ActorValueInfo*, uint32_t>				("GetActorValueInfoByID",	"ActorValueInfo", GetActorValueInfoByID));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(IsSkill),						ActorValueInfo, bool>										("IsSkill",					"ActorValueInfo", IsSkill));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetSkillUseMult),				ActorValueInfo, float>										("GetSkillUseMult",			"ActorValueInfo", GetSkillUseMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetSkillUseMult),				ActorValueInfo, void, float>								("SetSkillUseMult",			"ActorValueInfo", SetSkillUseMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetSkillOffsetMult),			ActorValueInfo, float>										("GetSkillOffsetMult",		"ActorValueInfo", GetSkillOffsetMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetSkillOffsetMult),			ActorValueInfo, void, float>								("SetSkillOffsetMult",		"ActorValueInfo", SetSkillOffsetMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetSkillImproveMult),			ActorValueInfo, float>										("GetSkillImproveMult",		"ActorValueInfo", GetSkillImproveMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetSkillImproveMult),			ActorValueInfo, void, float>								("SetSkillImproveMult",		"ActorValueInfo", SetSkillImproveMult));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetSkillImproveOffset),		ActorValueInfo, float>										("GetSkillImproveOffset",	"ActorValueInfo", GetSkillImproveOffset));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetSkillImproveOffset),		ActorValueInfo, void, float>								("SetSkillImproveOffset",	"ActorValueInfo", SetSkillImproveOffset));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetSkillExperience),			ActorValueInfo, float>										("GetSkillExperience",		"ActorValueInfo", GetSkillExperience));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetSkillExperience),			ActorValueInfo, void, float>								("SetSkillExperience",		"ActorValueInfo", SetSkillExperience));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(AddSkillExperience),			ActorValueInfo, void, float>								("AddSkillExperience",		"ActorValueInfo", AddSkillExperience));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetExperienceForLevel),		ActorValueInfo, float, uint32_t>							("GetExperienceForLevel",	"ActorValueInfo", GetExperienceForLevel));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetSkillLegendaryLevel),		ActorValueInfo, int32_t>									("GetSkillLegendaryLevel",	"ActorValueInfo", GetSkillLegendaryLevel));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetSkillLegendaryLevel),		ActorValueInfo, void, uint32_t>								("SetSkillLegendaryLevel",	"ActorValueInfo", SetSkillLegendaryLevel));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetPerkTree),					ActorValueInfo, void, BGSListForm*, Actor*, bool, bool>		("GetPerkTree",				"ActorValueInfo", GetPerkTree));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetCurrentValue),				ActorValueInfo, float, Actor*>								("GetCurrentValue",			"ActorValueInfo", GetCurrentValue));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetBaseValue),					ActorValueInfo, float, Actor*>								("GetBaseValue",			"ActorValueInfo", GetBaseValue));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetMaximumValue),				ActorValueInfo, float, Actor*>								("GetMaximumValue",			"ActorValueInfo", GetMaximumValue));

		VM->SetCallableFromTasklets("ActorValueInfo", "GetActorValueInfoByName", 1);
		VM->SetCallableFromTasklets("ActorValueInfo", "GetActorValueInfoByID", 1);
		VM->SetCallableFromTasklets("ActorValueInfo", "GetSkillUseMult", 1);
		VM->SetCallableFromTasklets("ActorValueInfo", "SetSkillUseMult", 1);
		VM->SetCallableFromTasklets("ActorValueInfo", "GetSkillOffsetMult", 1);
		VM->SetCallableFromTasklets("ActorValueInfo", "SetSkillOffsetMult", 1);
		VM->SetCallableFromTasklets("ActorValueInfo", "GetSkillImproveMult", 1);
		VM->SetCallableFromTasklets("ActorValueInfo", "SetSkillImproveMult", 1);
		VM->SetCallableFromTasklets("ActorValueInfo", "GetSkillImproveOffset", 1);
		VM->SetCallableFromTasklets("ActorValueInfo", "SetSkillImproveOffset", 1);
		VM->SetCallableFromTasklets("ActorValueInfo", "GetSkillLegendaryLevel", 1);
		VM->SetCallableFromTasklets("ActorValueInfo", "SetSkillLegendaryLevel", 1);
		VM->SetCallableFromTasklets("ActorValueInfo", "GetSkillExperience", 1);
		VM->SetCallableFromTasklets("ActorValueInfo", "SetSkillExperience", 1);
		VM->SetCallableFromTasklets("ActorValueInfo", "AddSkillExperience", 1);
		VM->SetCallableFromTasklets("ActorValueInfo", "GetExperienceForLevel", 1);
		VM->SetCallableFromTasklets("ActorValueInfo", "GetPerkTree", 1);

		return true;
	}
}