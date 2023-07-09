#include "../Game/PapyrusExtGame.h"

#include "../../../SaveLoad/SaveLoad.h"
#include "../../../TaskPool/TaskPool.h"

#include "../../../Misc/Misc.h"

#include "../../../../../Internal/Tasks/Tasks/TaskUpdateTintMasks.h"
#include "../../../../../Internal/Tasks/Tasks/TaskUpdateHairColor.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/P/PlayerCharacter.h"
#include "../../../../../../source/B/BGSSaveLoadManager.h"
#include "../../../../../../source/T/TESDataHandler.h"
#include "../../../../../../source/I/INISettingCollection.h"
#include "../../../../../../source/T/TESDataHandler.h"
#include "../../../../../../source/T/TESFile.h"
#include "../../../../../../source/T/TintMask.h"
#include "../../../../../../source/P/PlayerCamera.h"
#include "../../../../../../source/P/PlayerControls.h"
#include "../../../../../../source/N/NiColor.h"
#include "../../../../../../source/M/MiscStatManager.h"
#include "../../../../../../source/M/MagicFavorites.h"
#include "../../../../../../source/E/ExtraContainerChanges.h"
#include "../../../../../../source/M/MenuTopicManager.h"


namespace PapyrusExtGame
{
	// I really hate doing this...
	using namespace ConsoleRE;

	// helper functions, 
	void SetPlayerTintMaskColor(TESNPC* actorBase, TintMask * tintMask, uint32_t argb)
	{
		Color4 color(((argb >> 16) & 0xFF), ((argb >> 8) & 0xFF), ((argb >> 0) & 0xFF), ((argb >> 24) & 0xFF));
		
		float alpha = color.a / 255.0f;
		if (alpha > 1.0f)
			alpha = 1.0f;

		if (alpha < 0.0f)
			alpha = 0.0f;

		tintMask->SetColor(color.r, TintMask::kRed);
		tintMask->SetColor(color.g, TintMask::kGreen);
		tintMask->SetColor(color.b, TintMask::kBlue);
		tintMask->m_alpha = alpha;

		if (tintMask->m_tintType == 6)
		{
			NiColorA colorResult;
			actorBase->SetSkinFromTint(&colorResult, tintMask, true);
		}
	}
	//

	TESForm*		GetFormEx(StaticFunctionTag * base, uint32_t formId) { return TESForm::GetFormFromID(formId); }


	uint32_t		GameGetPerkPoints(StaticFunctionTag* tag)
	{
		// *(uint32_t*)(PlayerCharacter::GetPlayer() + 0xA31);
		return PlayerCharacter::GetSingleton()->UnkA31;
	}

	void			GameSetPerkPoints(StaticFunctionTag* tag, uint32_t val)
	{
		if (val > UINT8_MAX)
			val = UINT8_MAX;

		// *(uint32_t*)(PlayerCharacter::GetPlayer() + 0xA31) = val;
		PlayerCharacter::GetSingleton()->UnkA31 = val;
	}

	void			ModPerkPoints(StaticFunctionTag*, int32_t points)
	{
		ConsoleRE::PlayerCharacter* pPC = ConsoleRE::PlayerCharacter::GetSingleton();

	//  int32_t nuPerkPoints = (*(uint32_t*)(pPC + 0xA31)) + points;
		int32_t nuPerkPoints = pPC->UnkA31 + points;
		if (nuPerkPoints < 0)
			nuPerkPoints = 0;
		else if (nuPerkPoints > 255)
			nuPerkPoints = 255;

	//  (*(uint32_t*)(pPC + 0xA31)) = nuPerkPoints;
		pPC->UnkA31 = nuPerkPoints;
	}

	void			SetPlayerExperience(StaticFunctionTag*, float points)
	{
		ConsoleRE::PlayerCharacter* pPC = ConsoleRE::PlayerCharacter::GetSingleton();
		if (pPC->Unk8E8)
		{
			pPC->Unk8E8->data->xp = points;
		}
	}
	
	void			SetPlayerLevel(StaticFunctionTag*, int32_t level)
	{
		PlayerCharacter* pc = ConsoleRE::PlayerCharacter::GetSingleton();
		if (pc->Unk8E8)
			pc->Unk8E8->SetLevel(level);
	}

	float			GetPlayerExperience(StaticFunctionTag*)
	{
		PlayerCharacter* pPC = PlayerCharacter::GetSingleton();
		if (pPC->Unk8E8)
			return pPC->Unk8E8->data->xp;

		return 0.0f;
	}

	float			GetExperienceForLevel(StaticFunctionTag*, uint32_t level)
	{
		float fXPLevelUpMult = ConsoleRE::INISettingCollection::GetSingleton()->GetSetting("fXPLevelUpMult")->GetFloat();
		float fXPLevelUpBase = ConsoleRE::INISettingCollection::GetSingleton()->GetSetting("fXPLevelUpBase")->GetFloat();
		return fXPLevelUpBase + fXPLevelUpMult * level;
	}

	uint32_t		GameGetModCount(StaticFunctionTag* base)
	{
		ConsoleRE::TESDataHandler* singleton = ConsoleRE::TESDataHandler::GetSingleton();
		if (singleton)
		{
			return singleton->Unk918.m_size;
		}

		return 0;
	}

	uint32_t		GetModByName(StaticFunctionTag*, BSFixedString name)
	{
		TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
		TESFile * modInfo = pDataHandler->LookupModByName(name.m_data);
		if (!modInfo || !modInfo->IsActive())
			return 0xFF;

		if (modInfo->IsLight())
			return modInfo->Unk47A + 0x100;

		return modInfo->Unk478;
	}

	BSFixedString	GetModName(StaticFunctionTag*, uint32_t index)
	{
		TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
		TESFile* modInfo = nullptr;

		if (index > 0xFF) 
		{
			uint32_t adjusted = index - 0x100;

			if (adjusted >= pDataHandler->Unk918.m_size)
				return "";

			pDataHandler->Unk918.Get(adjusted, modInfo);

		}
		else 
		{
			if (index >= pDataHandler->Unk918.m_size)
				return "";

			pDataHandler->Unk918.Get(index, modInfo);
		}

		return (modInfo) ? modInfo->fileName : "";
	}

	BSFixedString	GetModAuthor(StaticFunctionTag*, uint32_t index)
	{
		TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
		TESFile* modInfo = nullptr;

		if (index > 0xFF) 
		{
			uint32_t adjusted = index - 0x100;

			if (adjusted >= pDataHandler->Unk918.m_size)
				return "";

			pDataHandler->Unk918.Get(adjusted, modInfo);

		}
		else 
		{
			if (index >= pDataHandler->Unk918.m_size)
				return "";

			pDataHandler->Unk918.Get(index, modInfo);
		}

		return (modInfo) ? modInfo->Creator.c_str() : "";
	}

	BSFixedString	GetModDescription(StaticFunctionTag*, uint32_t index)
	{
		TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
		TESFile* modInfo = nullptr;

		if (index > 0xFF) 
		{
			uint32_t adjusted = index - 0x100;

			if (adjusted >= pDataHandler->Unk918.m_size)
				return "";

			pDataHandler->Unk918.Get(adjusted, modInfo);

		}
		else 
		{
			if (index >= pDataHandler->Unk918.m_size)
				return "";

			pDataHandler->Unk918.Get(index, modInfo);
		}
		return (modInfo) ? modInfo->Summary.c_str() : "";
	}

	uint32_t	    GetModDependencyCount(StaticFunctionTag*, uint32_t index)
	{
		TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
		TESFile* modInfo = nullptr;
		
		if (index > 0xFF)
		{
			uint32_t adjusted = index - 0x100;
			
			if (adjusted >= pDataHandler->Unk918.m_size)
				return 0;
			
			pDataHandler->Unk918.Get(adjusted, modInfo);

		}
		else
		{
			if (index >= pDataHandler->Unk918.m_size)
				return 0;
			
			pDataHandler->Unk918.Get(index, modInfo);
		}
		return (modInfo) ? modInfo->Unk460 : 0;
	}

	uint32_t		GetLightModCount(StaticFunctionTag*)
	{
		TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
		return pDataHandler->Unk928.m_size;
	}

	uint32_t		GetLightModByName(StaticFunctionTag*, BSFixedString name)
	{
		TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
		TESFile* modInfo = pDataHandler->LookupModByName(name.m_data);
		if (!modInfo || !modInfo->IsActive() || !modInfo->IsLight())
			return 0xFFFF;

		return modInfo->Unk47A;
	}

	BSFixedString	GetLightModName(StaticFunctionTag*, uint32_t index)
	{
		TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
		if (index >= pDataHandler->Unk928.m_size)
			return "";

		TESFile* modInfo = nullptr;
		pDataHandler->Unk928.Get(index, modInfo);

		return (modInfo) ? modInfo->fileName : NULL;
	}

	BSFixedString	GetLightModAuthor(StaticFunctionTag*, uint32_t index)
	{
		TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
		if (index >= pDataHandler->Unk928.m_size)
			return "";

		TESFile* modInfo = NULL;
		pDataHandler->Unk928.Get(index, modInfo);

		return (modInfo) ? modInfo->Creator.c_str(): NULL;
	}

	BSFixedString	GetLightModDescription(StaticFunctionTag*, uint32_t index)
	{
		TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
		if (index >= pDataHandler->Unk928.m_size)
			return "";

		TESFile* modInfo = NULL;
		pDataHandler->Unk928.Get(index, modInfo);

		return (modInfo) ? modInfo->Summary.c_str() : NULL;
	}

	uint32_t		GetLightModDependencyCount(StaticFunctionTag*, uint32_t index)
	{
		TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
		if (index >= pDataHandler->Unk928.m_size)
			return 0;

		TESFile* modInfo = NULL;
		pDataHandler->Unk928.Get(index, modInfo);
		return (modInfo) ? modInfo->Unk460 : 0;
	}

	uint32_t		GetNthLightModDependency(StaticFunctionTag*, uint32_t index, uint32_t dep_index)
	{
		TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();
		if (index >= pDataHandler->Unk928.m_size)
			return 0;

		TESFile* modInfo = NULL;
		pDataHandler->Unk928.Get(index, modInfo);

		return (modInfo && dep_index < modInfo->Unk460) ? modInfo->Unk468[dep_index]->Unk478 : 0;
	}

	bool			IsPluginInstalled(StaticFunctionTag*, BSFixedString name)
	{
		TESDataHandler* pDataHandler = TESDataHandler::GetSingleton();

		TESFile* modInfo = pDataHandler->LookupModByName(name.m_data);
		
		if (modInfo)
			return modInfo->IsActive();

		return false;
	}

	void			GameSaveGame(StaticFunctionTag * base, BSFixedString name)
	{
		SaveGame::Process::SetSaveState(name.m_data);

	}

	void			GameLoadGame(StaticFunctionTag * base, BSFixedString name)
	{
		SaveGame::Process::SetLoadState(name.m_data);

	}
	
	void			SetGameSettingFloat(StaticFunctionTag * base, BSFixedString name, float value)
	{
		auto* singleton = ConsoleRE::INISettingCollection::GetSingleton();
		if (singleton)
		{
			auto setting = singleton->GetSetting(name.m_data);
			if (setting)
			{
				setting->SetFloat(value);
			}
		}
	}

	void			SetGameSettingInt(StaticFunctionTag * base, BSFixedString name, uint32_t value)
	{
		auto* singleton = ConsoleRE::INISettingCollection::GetSingleton();
		if (singleton)
		{
			auto setting = singleton->GetSetting(name.m_data);
			if (setting)
			{
				setting->SetUInt32(value);
			}
		}
	}

	void			SetGameSettingBool(StaticFunctionTag * base, BSFixedString name, bool value)
	{
		auto* singleton = ConsoleRE::INISettingCollection::GetSingleton();
		if (singleton)
		{
			auto setting = singleton->GetSetting(name.m_data);
			if (setting)
			{
				setting->SetBool(value);
			}
		}
	}

	void			SetGameSettingString(StaticFunctionTag * base, BSFixedString name, BSFixedString value)
	{
		auto* singleton = ConsoleRE::INISettingCollection::GetSingleton();
		if (singleton)
		{
			auto setting = singleton->GetSetting(name.m_data);
			if (setting)
			{
				setting->SetString(value.m_data);
			}
		}
	}

	uint32_t		GetNumTintMasks(StaticFunctionTag * base)
	{
		ConsoleRE::PlayerCharacter* pPC = ConsoleRE::PlayerCharacter::GetSingleton();
		if (!pPC)
		{
			return 0;
		}

		return pPC->UnkA40.m_size;
	}

	uint32_t		GetNthTintMaskColor(StaticFunctionTag * base, uint32_t n)
	{
		ConsoleRE::PlayerCharacter* pPC = ConsoleRE::PlayerCharacter::GetSingleton();
		if (!pPC)
		{
			return 0;
		}

		TintMask * tintMask = NULL;
		if (pPC->UnkA40.Get(n, tintMask))
		{
			return tintMask->ToARGB();
		}
		return 0;
	}

	uint32_t		GetNthTintMaskType(StaticFunctionTag * base, uint32_t n)
	{
		PlayerCharacter * pPC = PlayerCharacter::GetSingleton();
		if (!pPC) 
		{
			return 0;
		}

		TintMask * tintMask = NULL;
		if (pPC->UnkA40.Get(n, tintMask))
		{
			return tintMask->m_tintType;
		}

		return 0;
	}

	BSFixedString	GetNthTintMaskTexturePath(StaticFunctionTag * base, uint32_t n)
	{
		PlayerCharacter * pPC = PlayerCharacter::GetSingleton();
		if (!pPC) 
		{
			return NULL;
		}

		TintMask * tintMask = NULL;
		if (pPC->UnkA40.Get(n, tintMask))
		{
			if (tintMask->m_texture) 
			{
				return tintMask->m_texture->textureName;
			}
		}

		return NULL;
	}

	void			SetNthTintMaskTexturePath(StaticFunctionTag * base, BSFixedString path, uint32_t n)
	{
		PlayerCharacter * pPC = PlayerCharacter::GetSingleton();
		if (pPC) 
		{
			TintMask * tintMask = NULL;
			if (pPC->UnkA40.Get(n, tintMask))
			{
				if (tintMask->m_texture) 
				{
					tintMask->m_texture->textureName = path;
				}
			}

			if (pPC->UnkA50)
			{
				if (pPC->UnkA50->Get(n, tintMask))
				{
					if (tintMask->m_texture) 
					{
						tintMask->m_texture->textureName = path;
					}
				}
			}
		}
	}

	uint32_t		GetNumTintMasksByType(StaticFunctionTag * base, uint32_t tintType)
	{
		PlayerCharacter * pPC = PlayerCharacter::GetSingleton();
		if (!pPC) 
		{
			return 0;
		}

		return pPC->GetNumTints(tintType);
	}

	uint32_t		GetTintMaskColor(StaticFunctionTag * base, uint32_t tintType, uint32_t index)
	{
		PlayerCharacter * pPC = PlayerCharacter::GetSingleton();
		if (!pPC) 
		{
			return 0;
		}

		uint32_t color = 0;
		TintMask* tintMask = pPC->GetTintMask(tintType, index);
		if (tintMask) 
		{
			color = tintMask->ToARGB();
		}


		return color;
	}

	void			UpdateThirdPerson(StaticFunctionTag * base)
	{
		PlayerCharacter* pPC = PlayerCharacter::GetSingleton();
		PlayerCamera * camera = PlayerCamera::GetSingleton();

		if (pPC && camera)
		{
			camera->UpdateThirdPerson(pPC->IsWeaponDrawn());
		}
	}

	int32_t			GetCameraState(StaticFunctionTag * base)
	{
		PlayerCamera * playerCamera = PlayerCamera::GetSingleton();
		if (playerCamera)
		{
			for (int i = 0; i < 13; i++)
			{
				if (playerCamera->currentState == playerCamera->cameraStates[i])
					return i;
			}
		}

		return -1;
	}

	BSFixedString	GetTintMaskTexturePath(StaticFunctionTag * base, uint32_t tintType, uint32_t index)
	{
		PlayerCharacter* pPC = PlayerCharacter::GetSingleton();
		if (!pPC)
		{
			return NULL;
		}

		TintMask* tintMask = pPC->GetTintMask(tintType, index);
		if (tintMask && tintMask->m_texture)
		{
			return tintMask->m_texture->textureName;
		}

		return NULL;
	}
	
	void			SetTintMaskTexturePath(StaticFunctionTag * base, BSFixedString path, uint32_t tintType, uint32_t index)
	{
		PlayerCharacter* pPC = PlayerCharacter::GetSingleton();
		if (pPC) 
		{
			TintMask* tintMask = pPC->GetTintMask(tintType, index);
			if (tintMask && tintMask->m_texture) 
			{
				tintMask->m_texture->textureName = path;
			}

			if (pPC->UnkA50)
			{
				TintMask * overlayMask = pPC->GetOverlayTintMask(tintMask);
				if (overlayMask && overlayMask->m_texture) 
				{
					overlayMask->m_texture->textureName = path;
				}
			}
		}
	}

	void			SetMiscStat(StaticFunctionTag * base, BSFixedString name, uint32_t value)
	{
		MiscStatManager::MiscStat* stat = MiscStatManager::GetSingleton()->Get(name.m_data);

		if (stat)
			stat->m_value = value;
		else
			xUtilty::KernelPrintOut("SetMiscStat: could not find stat (%s)", name.m_data);
	}

	bool			GetPlayerMovementMode(StaticFunctionTag * base)
	{
		PlayerControls * controls = PlayerControls::GetSingleton();
		if (controls) 
		{
			return controls->data.running == 1;
		}

		return false;
	}

	void			UpdateTintMaskColors(StaticFunctionTag * base)
	{
		TaskPool::PushQueue(new Tasks::TaskUpdateTintMasks());
	}

	void			UpdateHairColor(StaticFunctionTag * base)
	{
		TaskPool::PushQueue(new Tasks::TaskUpdateHairColor());
	}

	// 
	void			UnbindObjectHotkey(StaticFunctionTag * base, int32_t hotkey)
	{
		TESForm* s_Form = nullptr;
		ExtraHotkey* s_Hotkey = nullptr;

		MagicFavorites * magicFavorites = MagicFavorites::GetSingleton();
		if (magicFavorites) 
		{
			magicFavorites->ClearHHotkey(hotkey);
		}

		PlayerCharacter* pPC = PlayerCharacter::GetSingleton();
		if (pPC && hotkey >= 0) 
		{
			ExtraContainerChanges* pContainerChanges = pPC->extraList.GetByType<ExtraContainerChanges>();
			if (pContainerChanges) 
			{
				pContainerChanges->FindHotkey(s_Form, s_Hotkey, hotkey);
				if (s_Hotkey)
				{
					s_Hotkey->hotkey = -1;
				}
			}
		}
	}

	void			SetTintMaskColor(StaticFunctionTag * base, uint32_t color, uint32_t tintType, uint32_t index)
	{
		PlayerCharacter * pPC = PlayerCharacter::GetSingleton();
		if (pPC) 
		{
			TESNPC* npc = TES_RTTI(pPC->data.objectReference, TESForm, TESNPC);
			if (npc) 
			{
				TintMask * tintMask = pPC->GetTintMask(tintType, index);
				if (tintMask) 
				{
					SetPlayerTintMaskColor(npc, tintMask, color);
				}

				if (pPC->UnkA50)
				{
					TintMask* overlayMask = pPC->GetOverlayTintMask(tintMask);
					if (overlayMask) 
					{
						SetPlayerTintMaskColor(npc, overlayMask, color);
					}
				}
			}
		}
	}

	void			SetNthTintMaskColor(StaticFunctionTag * base, uint32_t n, uint32_t color)
	{
		PlayerCharacter* pPC = PlayerCharacter::GetSingleton();
		if (pPC) 
		{
			TESNPC* npc = TES_RTTI(pPC->data.objectReference, TESForm, TESNPC);
			if (npc) 
			{
				TintMask * tintMask = NULL;
				if (pPC->UnkA40.Get(n, tintMask))
				{
					SetPlayerTintMaskColor(npc, tintMask, color);
				}

				if (pPC->UnkA50)
				{
					if (pPC->UnkA50->Get(n, tintMask))
					{
						SetPlayerTintMaskColor(npc, tintMask, color);
					}
				}
			}
		}
	}

	TESForm*		GetHotkeyBoundObject(StaticFunctionTag * base, int32_t hotkey)
	{
		TESForm*		s_form = nullptr;
		ExtraHotkey*	s_list = nullptr;

		PlayerCharacter* pPC = PlayerCharacter::GetSingleton();
		if (!pPC || hotkey < 0)
			return NULL;

		MagicFavorites * magicFavorites = MagicFavorites::GetSingleton();
		if (magicFavorites) 
		{
			TESForm * form = magicFavorites->GetSpell(hotkey);
			if (form)
				return form;
		}

		ExtraContainerChanges* pContainerChanges = pPC->extraList.GetByType<ExtraContainerChanges>();
		if (pContainerChanges) 
		{
			pContainerChanges->FindHotkey(s_form, s_list, hotkey);
			if (s_form)
				return s_form;
		}

		return NULL;
	}

	bool			IsObjectFavorited(StaticFunctionTag * base, TESForm * form)
	{
		TESForm*		s_form = nullptr;
		ExtraHotkey*	s_hotkey = nullptr;

		PlayerCharacter* player = PlayerCharacter::GetSingleton();
		if (!player || !form)
			return false;

		uint8_t formType = form->FormType;

		if (formType == 22 || formType == 119)
		{
			MagicFavorites * magicFavorites = MagicFavorites::GetSingleton();
			return magicFavorites && magicFavorites->IsFavorited(form);
		}
		else
		{
			bool result = false;

			ExtraContainerChanges* pContainerChanges = player->extraList.GetByType<ExtraContainerChanges>();
			if (pContainerChanges) 
			{
				pContainerChanges->FindHotkey(s_form, s_hotkey, form);
				if (s_hotkey)
					result = true;
			}

			return result;
		}
	}

	TESObjectREFR*	GetCurrentConsoleRef(StaticFunctionTag * base)
	{
		Relocation<void(*)(uint32_t&, NiPointer<TESObjectREFR>&)> func("", 0x5DB210);
		Relocation<uint32_t*> g_consoleHandle("", 0x3198E4C);
		Relocation<uint32_t*> g_invalidRefHandle("", 0x20BD820);

		uint32_t handle = *g_consoleHandle;
		NiPointer<TESObjectREFR> refr;
		if (handle != 0 && handle != *g_invalidRefHandle)
		{
			func(handle, refr);
			return refr;
		}

		return NULL;
	}

	// void			SetPlayersLastRiddenHorse(StaticFunctionTag * base, Actor* actor)
	// {
	// 	PlayerCharacter* pPC = PlayerCharacter::GetSingleton();
	// 	if (pPC) 
	// 	{
	// 		if (!actor)
	// 		{
	// 			pPC->Unk84C = 0;
	// 		}
	// 		else 
	// 		{
	// 			pPC->Unk84C = actor->CreateRef();
	// 		}
	// 	}
	// }

	TESObjectREFR*	GetDialogueTarget(StaticFunctionTag * base)
	{
		MenuTopicManager* topicManager = MenuTopicManager::GetSingleton();
		return topicManager ? topicManager->GetDialogueTarget() : nullptr;
	}

	TESObjectREFR*	GetCurrentCrosshairRef(StaticFunctionTag* base)
	{
		return Misc::GetCrossHairRefr();
	}

	bool	 RegisterGame(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GameGetPerkPoints),			StaticFunctionTag, uint32_t>			                   ("GetPerkPoints",		      "Game", GameGetPerkPoints));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GameSetPerkPoints),			StaticFunctionTag, void, uint32_t>	                       ("SetPerkPoints",		      "Game", GameSetPerkPoints));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(ModPerkPoints),				StaticFunctionTag, void, int32_t>                          ("ModPerkPoints",              "Game", ModPerkPoints));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetPlayerExperience),		StaticFunctionTag, float>							       ("GetPlayerExperience",		  "Game", GetPlayerExperience));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetPlayerExperience),		StaticFunctionTag, void, float>						       ("SetPlayerExperience",        "Game", SetPlayerExperience));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetExperienceForLevel),		StaticFunctionTag, float, uint32_t>                        ("GetExperienceForLevel",      "Game", GetExperienceForLevel));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetPlayerLevel),				StaticFunctionTag, void, int32_t>                          ("SetPlayerLevel",             "Game", SetPlayerLevel));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GameGetModCount),			StaticFunctionTag, uint32_t>                               ("GetModCount",                "Game", GameGetModCount));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetModByName),				StaticFunctionTag, uint32_t, BSFixedString>			       ("GetModByName",				  "Game", GetModByName));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetModName),					StaticFunctionTag, BSFixedString, uint32_t>			       ("GetModName",				  "Game", GetModName));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetModAuthor),				StaticFunctionTag, BSFixedString, uint32_t>			       ("GetModAuthor",				  "Game", GetModAuthor));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetModDescription),			StaticFunctionTag, BSFixedString, uint32_t>			       ("GetModDescription",		  "Game", GetModDescription));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetModDependencyCount),		StaticFunctionTag, uint32_t, uint32_t>				       ("GetModDependencyCount",	  "Game", GetModDependencyCount));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetLightModCount),			StaticFunctionTag, uint32_t>						       ("GetLightModCount",			  "Game", GetLightModCount));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetLightModByName),			StaticFunctionTag, uint32_t, BSFixedString>			       ("GetLightModByName",		  "Game", GetLightModByName));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetLightModName),			StaticFunctionTag, BSFixedString, uint32_t>			       ("GetLightModName",			  "Game", GetLightModName));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetLightModAuthor),			StaticFunctionTag, BSFixedString, uint32_t>			       ("GetLightModAuthor",		  "Game", GetLightModAuthor));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetLightModDescription),		StaticFunctionTag, BSFixedString, uint32_t>			       ("GetLightModDescription",     "Game", GetLightModDescription));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetLightModDependencyCount), StaticFunctionTag, uint32_t, uint32_t>				       ("GetLightModDependencyCount", "Game", GetLightModDependencyCount));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(IsPluginInstalled),			StaticFunctionTag, bool, BSFixedString>				       ("IsPluginInstalled",		  "Game", IsPluginInstalled));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetNthLightModDependency),	StaticFunctionTag, uint32_t, uint32_t, uint32_t>	       ("GetNthLightModDependency",	  "Game", GetNthLightModDependency));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetGameSettingFloat),		StaticFunctionTag, void, BSFixedString, float>             ("SetGameSettingFloat",        "Game", SetGameSettingFloat));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetGameSettingInt),			StaticFunctionTag, void, BSFixedString, int>               ("SetGameSettingInt",          "Game", SetGameSettingInt));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetGameSettingBool),			StaticFunctionTag, void, BSFixedString, bool>              ("SetGameSettingBool",         "Game", SetGameSettingBool));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetGameSettingString),		StaticFunctionTag, void, BSFixedString, BSFixedString>     ("SetGameSettingString",       "Game", SetGameSettingString));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GameSaveGame),				StaticFunctionTag, void, BSFixedString>                    ("SaveGame",                   "Game", GameSaveGame));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GameLoadGame),				StaticFunctionTag, void, BSFixedString>                    ("LoadGame",                   "Game", GameLoadGame));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetNumTintMasks),			StaticFunctionTag, uint32_t>						       ("GetNumTintMasks",			  "Game", GetNumTintMasks));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetNthTintMaskColor),		StaticFunctionTag, uint32_t, uint32_t>				       ("GetNthTintMaskColor",		  "Game", GetNthTintMaskColor));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetNthTintMaskType),			StaticFunctionTag, uint32_t, uint32_t>				       ("GetNthTintMaskType",		  "Game", GetNthTintMaskType));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetNthTintMaskTexturePath),	StaticFunctionTag, BSFixedString, uint32_t>			       ("GetNthTintMaskTexturePath",  "Game", GetNthTintMaskTexturePath));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetNthTintMaskTexturePath),  StaticFunctionTag, void, BSFixedString, uint32_t>          ("SetNthTintMaskTexturePath",  "Game", SetNthTintMaskTexturePath));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetNumTintMasksByType),		StaticFunctionTag, uint32_t, uint32_t>				       ("GetNumTintsByType",		  "Game", GetNumTintMasksByType));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetTintMaskColor),			StaticFunctionTag, uint32_t, uint32_t, uint32_t>	       ("GetTintMaskColor",			  "Game", GetTintMaskColor));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetTintMaskTexturePath),		StaticFunctionTag, BSFixedString, uint32_t, uint32_t>      ("GetTintMaskTexturePath",	  "Game", GetTintMaskTexturePath));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetTintMaskTexturePath),		StaticFunctionTag, void, BSFixedString, uint32_t, uint32_t>("SetTintMaskTexturePath",	  "Game", SetTintMaskTexturePath));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetCameraState),				StaticFunctionTag, int32_t>								   ("GetCameraState",			  "Game", GetCameraState));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetMiscStat),				StaticFunctionTag, void, BSFixedString, uint32_t>		   ("SetMiscStat",				  "Game", SetMiscStat));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetPlayerMovementMode),		StaticFunctionTag, bool>								   ("GetPlayerMovementMode",      "Game", GetPlayerMovementMode));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(UpdateThirdPerson),			StaticFunctionTag, void>                                   ("UpdateThirdPerson",          "Game", UpdateThirdPerson));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetFormEx),					StaticFunctionTag, TESForm*, uint32_t>					   ("GetFormEx",				  "Game", GetFormEx));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(UpdateTintMaskColors),		StaticFunctionTag, void>								   ("UpdateTintMaskColors",		  "Game", UpdateTintMaskColors));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(UpdateHairColor),			StaticFunctionTag, void>								   ("UpdateHairColor",			  "Game", UpdateHairColor));

		//
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetNthTintMaskColor),		StaticFunctionTag, void, uint32_t, uint32_t>		       ("SetNthTintMaskColor",		  "Game", SetNthTintMaskColor));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetTintMaskColor),			StaticFunctionTag, void, uint32_t, uint32_t, uint32_t>     ("SetTintMaskColor",			  "Game", SetTintMaskColor));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(UnbindObjectHotkey),			StaticFunctionTag, void, int32_t>						   ("UnbindObjectHotkey",		  "Game", UnbindObjectHotkey));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetHotkeyBoundObject),		StaticFunctionTag, TESForm*, int32_t>					   ("GetHotkeyBoundObject",		  "Game", GetHotkeyBoundObject));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(IsObjectFavorited),			StaticFunctionTag, bool, TESForm*>						   ("IsObjectFavorited",		  "Game", IsObjectFavorited));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetCurrentConsoleRef),		StaticFunctionTag, TESObjectREFR*>						   ("GetCurrentConsoleRef",		  "Game", GetCurrentConsoleRef));
		
		//
		// VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(SetPlayersLastRiddenHorse),  StaticFunctionTag, void, Actor*>						   ("SetPlayersLastRiddenHorse",  "Game", SetPlayersLastRiddenHorse));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetDialogueTarget),		    StaticFunctionTag, TESObjectREFR*>						   ("GetDialogueTarget",		  "Game", GetDialogueTarget));
		VM->RegisterFunction(new BSScript::NativeFunction <false,   NFDLSE(GetCurrentCrosshairRef),		StaticFunctionTag, TESObjectREFR*>						   ("GetCurrentCrosshairRef",	  "Game", GetCurrentCrosshairRef));
		
		VM->SetCallableFromTasklets("Game", "GetFormEx",					true);
		VM->SetCallableFromTasklets("Game", "SaveGame",						true);
		VM->SetCallableFromTasklets("Game", "LoadGame",						true);
		VM->SetCallableFromTasklets("Game", "SetGameSettingFloat",			true);
		VM->SetCallableFromTasklets("Game", "SetGameSettingInt",			true);
		VM->SetCallableFromTasklets("Game", "SetGameSettingBool",			true);
		VM->SetCallableFromTasklets("Game", "SetGameSettingString",			true);
		VM->SetCallableFromTasklets("Game", "GetModCount",					true);
		VM->SetCallableFromTasklets("Game", "GetModByName",					true);
		VM->SetCallableFromTasklets("Game", "GetModName",					true);
		VM->SetCallableFromTasklets("Game", "GetModAuthor",					true);
		VM->SetCallableFromTasklets("Game", "GetModDescription",			true);
		VM->SetCallableFromTasklets("Game", "GetModDependencyCount",		true);
		VM->SetCallableFromTasklets("Game", "GetNthModDependency",			true);
		VM->SetCallableFromTasklets("Game", "GetNumTintMasks",				true);
		VM->SetCallableFromTasklets("Game", "GetNthTintMaskColor",			true);
		VM->SetCallableFromTasklets("Game", "SetNthTintMaskColor",			true);
		VM->SetCallableFromTasklets("Game", "GetNthTintMaskType",			true);
		VM->SetCallableFromTasklets("Game", "GetNthTintMaskTexturePath",	true);
		VM->SetCallableFromTasklets("Game", "SetNthTintMaskTexturePath",	true);
		VM->SetCallableFromTasklets("Game", "GetNumTintsByType",			true);
		VM->SetCallableFromTasklets("Game", "GetTintMaskColor",				true);
		VM->SetCallableFromTasklets("Game", "SetTintMaskColor",				true);
		VM->SetCallableFromTasklets("Game", "GetTintMaskTexturePath",		true);
		VM->SetCallableFromTasklets("Game", "SetTintMaskTexturePath",		true);
		VM->SetCallableFromTasklets("Game", "SetMiscStat",					true);
		VM->SetCallableFromTasklets("Game", "GetCameraState",				true);
		VM->SetCallableFromTasklets("Game", "SetPlayersLastRiddenHorse",	true);
		VM->SetCallableFromTasklets("Game", "GetPlayerExperience",			true);
		VM->SetCallableFromTasklets("Game", "SetPlayerExperience",			true);
		VM->SetCallableFromTasklets("Game", "GetExperienceForLevel",		true);
		VM->SetCallableFromTasklets("Game", "GetDialogueTarget",			true);
		VM->SetCallableFromTasklets("Game", "UpdateTintMaskColors",			true);
		VM->SetCallableFromTasklets("Game", "UpdateHairColor",				true);

		return true;
	}
}