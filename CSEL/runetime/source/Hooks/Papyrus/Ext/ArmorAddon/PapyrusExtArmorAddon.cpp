#include "../ArmorAddon/PapyrusExtArmorAddon.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESObjectARMA.h"
#include "../../../../../../source/B/BGSTextureSet.h"
#include "../../../../../../source/T/TESModelTextureSwap.h"
#include "../../../../../../source/T/TESRace.h"

namespace PapyrusExtArmorAddon
{
	// I really hate doing this...
	using namespace ConsoleRE;

	BSFixedString GetModelPath(TESObjectARMA* thisArmorAddon, bool bFirst, bool bFemale)
	{
		return (thisArmorAddon) ? thisArmorAddon->bipedModels[bFirst][bFemale].GetModel() : NULL;
	}

	void SetModelPath(TESObjectARMA* thisArmorAddon, BSFixedString nuPath, bool bFirst, bool bFemale)
	{
		if (thisArmorAddon)
		{
			thisArmorAddon->bipedModels[bFirst][bFemale].SetModel(nuPath.m_data);
		}
	}

	uint32_t GetModelNumTextureSets(TESObjectARMA* thisArmorAddon, bool bFirst, bool bFemale)
	{
		return (thisArmorAddon) ? thisArmorAddon->bipedModels[bFirst][bFemale].numAlternateTextures : 0;
	}

	BGSTextureSet* GetModelNthTextureSet(TESObjectARMA* thisArmorAddon, uint32_t n, bool bFirst, bool bFemale)
	{
		if (!thisArmorAddon)
			return NULL;

		TESModelTextureSwap	* tex = &thisArmorAddon->bipedModels[bFirst][bFemale];

		if (!tex->alternateTextures || n >= tex->numAlternateTextures)
			return NULL;

		return tex->alternateTextures[n].textureSet;
	}

	void SetModelNthTextureSet(TESObjectARMA* thisArmorAddon, BGSTextureSet* textureSet, uint32_t n, bool bFirst, bool bFemale)
	{
		if (!thisArmorAddon || !textureSet)
			return;

		TESModelTextureSwap	* tex = &thisArmorAddon->bipedModels[bFirst][bFemale];

		if (!tex->alternateTextures || n >= tex->numAlternateTextures)
			return;

		tex->alternateTextures[n].textureSet = textureSet;
	}

	// 
	uint32_t GetNumAdditionalRaces(TESObjectARMA* thisArmorAddon)
	{
		return (thisArmorAddon) ? thisArmorAddon->additionalRaces.m_size : 0;
	}

	TESRace* GetNthAdditionalRace(TESObjectARMA* thisArmorAddon, uint32_t n)
	{
		if (!thisArmorAddon || (n >= thisArmorAddon->additionalRaces.m_size))
			return NULL;

		TESRace * race = NULL;
		if (!thisArmorAddon->additionalRaces.Get(n, race))
			return NULL;

		return race;
	}

	uint32_t GetSlotMask(TESObjectARMA* thisArmorAddon)
	{
		if (thisArmorAddon)
		{
			return thisArmorAddon->GetSlotMask();
		}

		return 0;
	}

	void	 SetSlotMask(TESObjectARMA* thisArmorAddon, uint32_t slotMask)
	{
		if (thisArmorAddon) 
		{
			thisArmorAddon->SetSlotMask(slotMask);
		}
	}

	uint32_t AddSlotToMask(TESObjectARMA* thisArmorAddon, uint32_t slot)
	{
		if (thisArmorAddon)
		{
			return thisArmorAddon->AddSlotToMask(slot);
		}

		return 0;
	}

	uint32_t RemoveSlotFromMask(TESObjectARMA* thisArmorAddon, uint32_t slot)
	{
		if (thisArmorAddon)
		{
			return thisArmorAddon->RemoveSlotFromMask(slot);
		}


		return (thisArmorAddon) ? thisArmorAddon->GetSlotMask() : 0;
	}

	bool RegisterArmorAddon(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetModelPath),           TESObjectARMA, BSFixedString, bool, bool>                 ("GetModelPath",           "ArmorAddon", GetModelPath));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetModelPath),           TESObjectARMA, void, BSFixedString, bool, bool>           ("SetModelPath",           "ArmorAddon", SetModelPath));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetModelNumTextureSets), TESObjectARMA, uint32_t, bool, bool>                      ("GetModelNumTextureSets", "ArmorAddon", GetModelNumTextureSets));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetModelNthTextureSet),  TESObjectARMA, BGSTextureSet*, uint32_t, bool, bool>      ("GetModelNthTextureSet",  "ArmorAddon", GetModelNthTextureSet));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetModelNthTextureSet),  TESObjectARMA, void, BGSTextureSet*, uint32_t, bool, bool>("SetModelNthTextureSet",  "ArmorAddon", SetModelNthTextureSet));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNumAdditionalRaces),  TESObjectARMA, uint32_t>                                  ("GetNumAdditionalRaces",  "ArmorAddon", GetNumAdditionalRaces));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetNthAdditionalRace),   TESObjectARMA, TESRace*, uint32_t>                        ("GetNthAdditionalRace",   "ArmorAddon", GetNthAdditionalRace));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(GetSlotMask),            TESObjectARMA, uint32_t>                                  ("GetSlotMask",            "ArmorAddon", GetSlotMask));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(SetSlotMask),            TESObjectARMA, void, uint32_t>                            ("SetSlotMask",            "ArmorAddon", SetSlotMask));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(AddSlotToMask),          TESObjectARMA, uint32_t, uint32_t>                        ("AddSlotToMask",          "ArmorAddon", AddSlotToMask));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(RemoveSlotFromMask),     TESObjectARMA, uint32_t, uint32_t>                        ("RemoveSlotFromMask",     "ArmorAddon", RemoveSlotFromMask));

		return true;
	}
}