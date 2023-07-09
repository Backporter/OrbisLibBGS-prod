#include "../GameData/PapyrusExtGameData.h"

#include "../../../../../../source/A/AlchemyItem.h"
#include "../../../../../../source/T/TESDataHandler.h"
#include "../../../../../../source/T/TESForm.h"
#include "../../../../../../source/T/TESRace.h"
#include "../../../../../../source/T/TESNPC.h"
#include "../../../../../../source/T/TESAmmo.h"
#include "../../../../../../source/T/TESFile.h"
#include "../../../../../../source/T/TESObjectBOOK.h"
#include "../../../../../../source/I/IngredientItem.h"
#include "../../../../../../source/T/TESObjectWEAP.h"
#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/B/BGSKeyword.h"
#include "../../../../../../source/S/ScrollItem.h"
#include "../../../../../../source/T/TESKey.h"
#include "../../../../../../source/T/TESObjectMISC.h"
#include "../../../../../../source/T/TESObjectARMO.h"
#include "../../../../../../source/P/PackUnpackImpl.h"

namespace PapyrusExtGameData
{
	// I really hate doing this...
	using namespace ConsoleRE;

	bool VerifyKeywords(TESForm * form, std::vector<BGSKeyword*>* keywords)
	{
		if (keywords->size() > 0)
		{
			BGSKeywordForm* pKeywords = TES_RTTI(form, TESForm, BGSKeywordForm);
			if (pKeywords)
			{
				bool		failed = false;
				BGSKeyword* keyword = NULL;

				for (uint32_t k = 0; k < keywords->size(); k++)
				{
					keyword = (*keywords)[k];
					if (keyword && !pKeywords->HasKeyword(keyword))
					{
						failed = true;
						break;
					}
				}

				if (failed)
				{
					return false;
				}
			}
		}

		return true;
	}

	template <typename T>
	bool IS_TYPE(int32_t weaponTypes, T weapon, int32_t t, int32_t h, int32_t s)
	{
		return ((weaponTypes & t) == t) && (weapon->weaponData.animationType == h || weapon->weaponData.animationType == s);
	}

	//
	std::vector<TESForm*> GetAllWeapons(StaticFunctionTag*, BSFixedString modName, std::vector<BGSKeyword*> keywords, bool playable, bool ignoreTemplates, bool ignoreEnchantments, bool onlyEnchanted, uint32_t weaponTypes)
	{
		std::vector<TESForm*> result;

		TESDataHandler * dataHandler = TESDataHandler::GetSingleton();
		TESFile * modInfo = dataHandler->LookupModByName(modName.c_str());
		if (!modInfo || !modInfo->IsActive())
			return result;

		TESObjectWEAP * weapon = NULL;
		
		auto WeaponArray = dataHandler->GetFormArray<TESObjectWEAP>();
		for (uint32_t i = 0; i < WeaponArray.m_size; i++)
		{
			WeaponArray.Get(i, weapon);

			if (!modInfo->IsFormInMod(weapon->FormID))
				continue;

			if (playable != weapon->GetPlayable())
				continue;
			
			if (ignoreTemplates && weapon->templateWeapon)
				continue;
			
			if (ignoreEnchantments && weapon->formEnchanting)
				continue;
			
			if (onlyEnchanted && !weapon->formEnchanting)
				continue;

			if (!VerifyKeywords(weapon, &keywords))
				continue;

			bool accept = false;

			if (IS_TYPE(weaponTypes, weapon, 1, 0, 10))
				accept = true;

			if (IS_TYPE(weaponTypes, weapon, 2, 1, 11))
				accept = true;

			if (IS_TYPE(weaponTypes, weapon, 4, 2, 12))
				accept = true;

			if (IS_TYPE(weaponTypes, weapon, 8, 3, 13))
				accept = true;

			if (IS_TYPE(weaponTypes, weapon, 16, 4, 14))
				accept = true;

			if (IS_TYPE(weaponTypes, weapon, 32, 5, 15))
				accept = true;

			if (IS_TYPE(weaponTypes, weapon, 64, 6, 16))
				accept = true;

			if (IS_TYPE(weaponTypes, weapon, 128, 7, 17))
				accept = true;

			if (IS_TYPE(weaponTypes, weapon, 256, 8, 18))
				accept = true;

			if (IS_TYPE(weaponTypes, weapon, 512, 9, 19))
				accept = true;

			if (!accept)
				continue;

			result.push_back(weapon);
		}

		return result;
	}

	std::vector<TESForm*> GetAllArmor(StaticFunctionTag*, BSFixedString modName, std::vector<BGSKeyword*> keywords, bool playable, bool ignoreTemplates, bool ignoreEnchantments, bool onlyEnchanted, bool ignoreSkin)
	{
		std::vector<TESForm*> result;

		TESDataHandler * dataHandler = TESDataHandler::GetSingleton();

		TESFile * modInfo = dataHandler->LookupModByName(modName.c_str());
		if (!modInfo || !modInfo->IsActive())
			return result;

		std::set<TESObjectARMO*> exclude;
		if (ignoreSkin) 
		{
			TESRace * race = NULL;

			auto RaceForm = dataHandler->GetFormArray<TESRace>();
			for (uint32_t i = 0; i < RaceForm.m_size; i++)
			{
				RaceForm.Get(i, race);
				if (race->skin)
					exclude.insert(race->skin);
			}

			TESNPC * npc = NULL;
			auto NPCForm = dataHandler->GetFormArray<TESNPC>();
			for (uint32_t i = 0; i < NPCForm.m_size; i++)
			{
				NPCForm.Get(i, npc);
				if (npc->skin)
					exclude.insert(npc->skin);
			}
		}

		TESObjectARMO * armor = NULL;
		auto ArrmorForm = dataHandler->GetFormArray<TESObjectARMO>();
		for (uint32_t i = 0; i < ArrmorForm.m_size; i++)
		{
			ArrmorForm.Get(i, armor);

			if (!modInfo->IsFormInMod(armor->FormID))
				continue;

			if (ignoreSkin && exclude.find(armor) != exclude.end())
				continue;
			
			if (playable != armor->GetPlayable())
				continue;

			if (ignoreTemplates && armor->templateArmor)
				continue;
			
			if (ignoreEnchantments && armor->formEnchanting)
				continue;
			
			if (onlyEnchanted && !armor->formEnchanting)
				continue;
			
			if (!VerifyKeywords(armor, &keywords))
				continue;

			result.push_back(armor);
		}


		return result;
	}

	std::vector<TESForm*> GetAllAmmo(StaticFunctionTag*, BSFixedString modName, std::vector<BGSKeyword*> keywords, bool playable)
	{
		std::vector<TESForm*> result;

		TESDataHandler * dataHandler = TESDataHandler::GetSingleton();
		TESFile * modInfo = dataHandler->LookupModByName(modName.c_str());
		if (!modInfo || !modInfo->IsActive())
			return result;

		TESAmmo * ammo = NULL;
		auto AmmorArray = dataHandler->GetFormArray<TESAmmo>();
		for (uint32_t i = 0; i < AmmorArray.m_size; i++)
		{
			AmmorArray.Get(i, ammo);

			if (!modInfo->IsFormInMod(ammo->FormID))
				continue;

			if (playable != ammo->GetPlayable())
				continue;
			
			if (!VerifyKeywords(ammo, &keywords))
				continue;

			result.push_back(ammo);
		}

		return result;
	}

	std::vector<TESForm*> GetAllBooks(StaticFunctionTag*, BSFixedString modName, std::vector<BGSKeyword*> keywords, bool regular, bool spellBook, bool skillBook)
	{
		std::vector<TESForm*> result;

		TESDataHandler * dataHandler = TESDataHandler::GetSingleton();
		TESFile * modInfo = dataHandler->LookupModByName(modName.c_str());
		if (!modInfo || !modInfo->IsActive())
			return result;

		TESObjectBOOK * book = NULL;
		auto BookArray = dataHandler->GetFormArray<TESObjectBOOK>();
		for (uint32_t i = 0; i < BookArray.m_size; i++)
		{
			BookArray.Get(i, book);

			if (!modInfo->IsFormInMod(book->FormID))
				continue;

			if (!VerifyKeywords(book, &keywords))
				continue;

			bool isSkillBook = book->data.GetSanitizedType() == 1;
			bool isSpellBook = book->data.GetSanitizedType() == 4;

			bool accept = false;
			if (regular && !isSkillBook && !isSpellBook)
				accept = true;

			if (spellBook && isSpellBook)
				accept = true;

			if (skillBook && isSkillBook)
				accept = true;

			if (!accept)
				continue;


			result.push_back(book);
		}

		return result;
	}

	std::vector<TESForm*> GetAllPotions(StaticFunctionTag*, BSFixedString modName, std::vector<BGSKeyword*> keywords, bool potions, bool food, bool poison)
	{
		std::vector<TESForm*> result;

		TESDataHandler * dataHandler = TESDataHandler::GetSingleton();
		TESFile * modInfo = dataHandler->LookupModByName(modName.c_str());
		if (!modInfo || !modInfo->IsActive())
			return result;

		AlchemyItem * potion = NULL;
		auto PotionArray = dataHandler->GetFormArray<AlchemyItem>();
		for (uint32_t i = 0; i < PotionArray.m_size; i++)
		{
			PotionArray.Get(i, potion);

			if (!modInfo->IsFormInMod(potion->FormID))
				continue;

			if (!VerifyKeywords(potion, &keywords))
				continue;

			bool isFood = potion->Is(0x00000002);
			bool isPoison = potion->Is(0x00020000);

			bool accept = false;
			if (potions && !isFood && !isPoison)
				accept = true;
			if (food && isFood)
				accept = true;
			if (poison && isPoison)
				accept = true;
			if (!accept)
				continue;


			result.push_back(potion);
		}

		return result;
	}

	std::vector<TESForm*> GetAllIngredients(StaticFunctionTag*, BSFixedString modName, std::vector<BGSKeyword*> keywords)
	{
		std::vector<TESForm*> result;

		TESDataHandler * dataHandler = TESDataHandler::GetSingleton();
		TESFile * modInfo = dataHandler->LookupModByName(modName.c_str());
		if (!modInfo || !modInfo->IsActive())
			return result;

		IngredientItem * ingredient = NULL;
		auto IngredientArray = dataHandler->GetFormArray<IngredientItem>();
		for (uint32_t i = 0; i < IngredientArray.m_size; i++)
		{
			IngredientArray.Get(i, ingredient);

			if (!modInfo->IsFormInMod(ingredient->FormID))
				continue;

			if (!VerifyKeywords(ingredient, &keywords))
				continue;

			result.push_back(ingredient);
		}

		return result;
	}

	std::vector<TESForm*> GetAllScrolls(StaticFunctionTag*, BSFixedString modName, std::vector<BGSKeyword*> keywords)
	{
		std::vector<TESForm*> result;

		TESDataHandler * dataHandler = TESDataHandler::GetSingleton();
		TESFile * modInfo = dataHandler->LookupModByName(modName.c_str());
		if (!modInfo || !modInfo->IsActive())
			return result;

		ScrollItem * scroll = NULL;
		auto ScrollArray = dataHandler->GetFormArray<ScrollItem>();
		for (uint32_t i = 0; i < ScrollArray.m_size; i++)
		{
			ScrollArray.Get(i, scroll);

			if (!modInfo->IsFormInMod(scroll->FormID))
				continue;

			if (!VerifyKeywords(scroll, &keywords))
				continue;

			result.push_back(scroll);
		}

		return result;
	}

	std::vector<TESForm*> GetAllKeys(StaticFunctionTag*, BSFixedString modName, std::vector<BGSKeyword*> keywords)
	{
		std::vector<TESForm*> result;

		TESDataHandler * dataHandler = TESDataHandler::GetSingleton();
		TESFile * modInfo = dataHandler->LookupModByName(modName.c_str());
		if (!modInfo || !modInfo->IsActive())
			return result;

		TESKey * key = NULL;
		auto KeyArray = dataHandler->GetFormArray<TESKey>();
		for (uint32_t i = 0; i < KeyArray.m_size; i++)
		{
			KeyArray.Get(i, key);

			if (!modInfo->IsFormInMod(key->FormID))
				continue;

			if (!VerifyKeywords(key, &keywords))
				continue;

			result.push_back(key);
		}

		return result;
	}

	std::vector<TESForm*> GetAllMiscItems(StaticFunctionTag*, BSFixedString modName, std::vector<BGSKeyword*> keywords)
	{
		std::vector<TESForm*> result;

		TESDataHandler * dataHandler = TESDataHandler::GetSingleton();
		TESFile * modInfo = dataHandler->LookupModByName(modName.c_str());
		if (!modInfo || !modInfo->IsActive())
			return result;

		TESObjectMISC * misc = NULL;
		auto MiscArray = dataHandler->GetFormArray<TESObjectMISC>();
		for (uint32_t i = 0; i < MiscArray.m_size; i++)
		{
			MiscArray.Get(i, misc);

			if (!modInfo->IsFormInMod(misc->FormID))
				continue;

			if (!VerifyKeywords(misc, &keywords))
				continue;

			result.push_back(misc);
		}

		return result;
	}

	bool RegisterGameData(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetAllWeapons),			StaticFunctionTag, std::vector<TESForm*>, BSFixedString, std::vector<BGSKeyword*>, bool, bool, bool, bool, uint32_t>	("GetAllWeapons",		"GameData", GetAllWeapons));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetAllArmor),			StaticFunctionTag, std::vector<TESForm*>, BSFixedString, std::vector<BGSKeyword*>, bool, bool, bool, bool, bool>		("GetAllArmor",			"GameData", GetAllArmor));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetAllAmmo),			StaticFunctionTag, std::vector<TESForm*>, BSFixedString, std::vector<BGSKeyword*>, bool>								("GetAllAmmo",			"GameData", GetAllAmmo));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetAllBooks),			StaticFunctionTag, std::vector<TESForm*>, BSFixedString, std::vector<BGSKeyword*>, bool, bool, bool>					("GetAllBooks",			"GameData", GetAllBooks));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetAllPotions),			StaticFunctionTag, std::vector<TESForm*>, BSFixedString, std::vector<BGSKeyword*>, bool, bool, bool>					("GetAllPotions",		"GameData", GetAllPotions));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetAllIngredients),		StaticFunctionTag, std::vector<TESForm*>, BSFixedString, std::vector<BGSKeyword*>>										("GetAllIngredients",	"GameData", GetAllIngredients));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetAllScrolls),			StaticFunctionTag, std::vector<TESForm*>, BSFixedString, std::vector<BGSKeyword*>>										("GetAllScrolls",		"GameData", GetAllScrolls));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetAllKeys),			StaticFunctionTag, std::vector<TESForm*>, BSFixedString, std::vector<BGSKeyword*>>										("GetAllKeys",			"GameData", GetAllKeys));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetAllMiscItems),		StaticFunctionTag, std::vector<TESForm*>, BSFixedString, std::vector<BGSKeyword*>>										("GetAllMiscItems",		"GameData", GetAllMiscItems));

		return true;
	}
}