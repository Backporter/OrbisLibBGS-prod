#include "../NPC/PapyrusExtNPC.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESCombatStyle.h"
#include "../../../../../../source/T/TESNPC.h"
#include "../../../../../../source/B/BGSVoiceType.h"
#include "../../../../../../source/S/SpellItem.h"
#include "../../../../../../source/T/TESObjectARMO.h"
#include "../../../../../../source/T/TESClass.h"
#include "../../../../../../source/B/BGSOutfit.h"

namespace PapyrusExtNPC
{
	// I really hate doing this...
	using namespace ConsoleRE;

	TESCombatStyle* GetCombatStyle(TESNPC* thisNPC)
	{
		return (thisNPC) ? thisNPC->combatStyle : NULL;
	}

	void SetCombatStyle(TESNPC* thisNPC, TESCombatStyle* cs)
	{
		if (thisNPC && cs) 
		{
			thisNPC->combatStyle = cs;
		}
	}

	BGSOutfit* GetOutfit(TESNPC* thisNPC, bool bSleepOutfit)
	{
		if (!thisNPC)
			return NULL;

		return bSleepOutfit ? thisNPC->sleepOutfit : thisNPC->defaultOutfit;
	}

	void SetClass(TESNPC* thisNPC, TESClass* nuClass)
	{
		if (thisNPC && nuClass) 
		{
			thisNPC->npcClass = nuClass;
		}
	}

	uint32_t GetSpellCount(TESNPC* thisNPC)
	{
		if (thisNPC)
		{
			TESSpellList* base = static_cast<TESSpellList*>(thisNPC);
			if (base->actorEffects)
			{
				return base->actorEffects->numSpells;
			}
		}

		return 0;
	}

	SpellItem* GetNthSpell(TESNPC* thisNPC, uint32_t n)
	{
		if (thisNPC)
		{
			TESSpellList* base = static_cast<TESSpellList*>(thisNPC);
			if (base->actorEffects && n < base->actorEffects->numSpells)
			{
				return base->actorEffects->spells[n];
			}
		}

		return NULL;
	}

	BGSVoiceType* GetVoiceType(TESNPC* thisNPC)
	{
		return (thisNPC) ? thisNPC->voiceType : NULL;
	}

	void SetVoiceType(TESNPC* thisNPC, BGSVoiceType * newVoice)
	{
		if (thisNPC) 
		{
			thisNPC->voiceType = newVoice;
		}
	}

	float GetWeight(TESNPC* thisNPC)
	{
		return (thisNPC) ? thisNPC->weight : 0.0;
	}

	void SetWeight(TESNPC* thisNPC, float weight)
	{
		if (thisNPC) 
		{
			thisNPC->weight = weight;
		}
	}

	float GetHeight(TESNPC* thisNPC)
	{
		return (thisNPC) ? thisNPC->height : 0.0;
	}

	void SetHeight(TESNPC* thisNPC, float height)
	{
		if (thisNPC) 
		{
			thisNPC->height = height;
		}
	}

	uint32_t GetNumHeadParts(TESNPC* thisNPC)
	{
		return (thisNPC) ? thisNPC->numHeadParts : 0;
	}

	BGSHeadPart* GetNthHeadPart(TESNPC* thisNPC, uint32_t n)
	{
		return (thisNPC && thisNPC->headParts && n < thisNPC->numHeadParts) ? thisNPC->headParts[n] : NULL;
	}

	void SetNthHeadPart(TESNPC* thisNPC, BGSHeadPart* headPart, uint32_t n)
	{
		if (thisNPC && n < thisNPC->numHeadParts) 
		{
			if (headPart && thisNPC->headParts)
			{
				thisNPC->headParts[n] = headPart;
			}
		}
	}

	// Convenience function to return a headPart's index by type
	int32_t GetIndexOfHeadPartByType(TESNPC* thisNPC, uint32_t type)
	{
		if (thisNPC && thisNPC->headParts)
		{
			for (int i = 0; i < thisNPC->numHeadParts; i++) 
			{
				if (thisNPC->headParts[i] && thisNPC->headParts[i]->type == type && !thisNPC->headParts[i]->IsExtraPart()) {
					return i;
				}
			}
		}

		return -1;
	}

	Relocation<BGSHeadPart**(*)(TESNPC*)> GetActorBaseOverlays("", 0x31E030);
	Relocation<uint32_t(*)(TESNPC*)>      GetNumActorBaseOverlays("", 0x3182B0);

	uint32_t GetNumOverlayHeadParts(TESNPC* thisNPC)
	{
		return (thisNPC) ? GetNumActorBaseOverlays(thisNPC) : 0;
	}
	
	BGSHeadPart* GetNthOverlayHeadPart(TESNPC* thisNPC, uint32_t n)
	{
		if (!thisNPC)
			return NULL;
	
		uint32_t numOverlays = GetNumActorBaseOverlays(thisNPC);
		if (n >= numOverlays)
			return NULL;
	
		BGSHeadPart ** overlays = GetActorBaseOverlays(thisNPC);
		return overlays[n];
	}
	
	// Convenience function to return a headPart's index by type
	int32_t GetIndexOfOverlayHeadPartByType(TESNPC* thisNPC, uint32_t type)
	{
		if (!thisNPC)
			return NULL;
	
		uint32_t numOverlays = GetNumActorBaseOverlays(thisNPC);
		BGSHeadPart ** overlays = GetActorBaseOverlays(thisNPC);
		for (uint32_t i = 0; i < numOverlays; i++)
		{
			if (overlays[i] && overlays[i]->type == type && !overlays[i]->IsExtraPart())
				return i;
		}
	
		return -1;
	}
	
	float GetFaceMorph(TESNPC* thisNPC, uint32_t index)
	{
		return (thisNPC && thisNPC->faceData && index < 19) ? thisNPC->faceData->morphs[index] : 0.0f;
	}
	
	void SetFaceMorph(TESNPC* thisNPC, float value, uint32_t index)
	{
		if (thisNPC && thisNPC->faceData && index < 19) 
		{
			thisNPC->faceData->morphs[index] = value;
		}
	}

	uint32_t GetFacePreset(TESNPC* thisNPC, uint32_t index)
	{
		return (thisNPC && thisNPC->faceData && index < 4) ? thisNPC->faceData->parts[index] : 0;
	}
	
	void SetFacePreset(TESNPC* thisNPC, uint32_t value, uint32_t index)
	{
		if (thisNPC && thisNPC->faceData && index < 4)
		{
			thisNPC->faceData->parts[index] = value;
		}
	}

	// Hair Color
	BGSColorForm* GetHairColor(TESNPC* thisNPC)
	{
		return (thisNPC && thisNPC->headRelatedData) ? thisNPC->headRelatedData->hairColor : NULL;
	}
	
	void SetHairColor(TESNPC* thisNPC, BGSColorForm* colorForm)
	{
		if (thisNPC && colorForm && thisNPC->headRelatedData)
		{
			thisNPC->headRelatedData->hairColor = colorForm;
		}
	}
	

	BGSTextureSet * GetFaceTextureSet(TESNPC* thisNPC)
	{
		return (thisNPC && thisNPC->headRelatedData) ? thisNPC->headRelatedData->faceDetails : NULL;
	}
	
	void SetFaceTextureSet(TESNPC* thisNPC, BGSTextureSet * textureSet)
	{
		if (thisNPC) 
		{
			thisNPC->SetFaceTexture(textureSet);
		}
	}
	
	TESObjectARMO * GetSkin(TESNPC* thisNPC)
	{
		return (thisNPC) ? static_cast<BGSSkinForm*>(thisNPC)->skin : NULL;
	}
	
	void SetSkin(TESNPC* thisNPC, TESObjectARMO * skin)
	{
		if (thisNPC) 
		{
			static_cast<BGSSkinForm*>(thisNPC)->skin = skin;
		}
	}
	
	TESObjectARMO * GetSkinFar(TESNPC* thisNPC)
	{
		return (thisNPC) ? thisNPC->farSkin : NULL;
	}
	
	void SetSkinFar(TESNPC* thisNPC, TESObjectARMO * skin)
	{
		if (thisNPC) 
		{
			thisNPC->farSkin = skin;
		}
	}
	
	TESNPC* GetTemplate(TESNPC* thisNPC)
	{
		return thisNPC ? thisNPC->GetRootFaceNPC() : NULL;
	}

	bool RegisterNPC(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetCombatStyle),					 TESNPC, TESCombatStyle*>             ("GetCombatStyle",                  "ActorBase", GetCombatStyle));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetCombatStyle),					 TESNPC, void, TESCombatStyle*>       ("SetCombatStyle",                  "ActorBase", SetCombatStyle));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetOutfit),						 TESNPC, BGSOutfit*, bool>            ("GetOutfit",                       "ActorBase", GetOutfit));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetClass),							 TESNPC, void, TESClass*>             ("SetClass",                        "ActorBase", SetClass));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetSpellCount),					 TESNPC, uint32_t>                    ("GetSpellCount",                   "ActorBase", GetSpellCount));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthSpell),						 TESNPC, SpellItem*, uint32_t>        ("GetNthSpell",                     "ActorBase", GetNthSpell));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetVoiceType),						 TESNPC, BGSVoiceType*>               ("GetVoiceType",                    "ActorBase", GetVoiceType));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetVoiceType),						 TESNPC, void, BGSVoiceType*>         ("SetVoiceType",                    "ActorBase", SetVoiceType));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetHeight),						 TESNPC, float>                       ("GetHeight",                       "ActorBase", GetHeight));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetHeight),						 TESNPC, void, float>                 ("SetHeight",                       "ActorBase", SetHeight));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetWeight),						 TESNPC, float>                       ("GetWeight",                       "ActorBase", GetWeight));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetWeight),						 TESNPC, void, float>                 ("SetWeight",                       "ActorBase", SetWeight));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNumHeadParts),					 TESNPC, uint32_t>                    ("GetNumHeadParts",                 "ActorBase", GetNumHeadParts));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthHeadPart),					 TESNPC, BGSHeadPart*, uint32_t>      ("GetNthHeadPart",                  "ActorBase", GetNthHeadPart));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetNthHeadPart),					 TESNPC, void, BGSHeadPart*, uint32_t>("SetNthHeadPart",                  "ActorBase", SetNthHeadPart));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetIndexOfHeadPartByType),			 TESNPC, int32_t, uint32_t>           ("GetIndexOfHeadPartByType",        "ActorBase", GetIndexOfHeadPartByType));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNumOverlayHeadParts),			 TESNPC, uint32_t>                    ("GetNumOverlayHeadParts",          "ActorBase", GetNumOverlayHeadParts));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthOverlayHeadPart),			 TESNPC, BGSHeadPart*, uint32_t>      ("GetNthOverlayHeadPart",           "ActorBase", GetNthOverlayHeadPart));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetIndexOfOverlayHeadPartByType),	 TESNPC, int32_t, uint32_t>           ("GetIndexOfOverlayHeadPartByType", "ActorBase", GetIndexOfOverlayHeadPartByType));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetFaceMorph),						 TESNPC, float, uint32_t>             ("GetFaceMorph",                    "ActorBase", GetFaceMorph));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetFaceMorph),						 TESNPC, void, float, uint32_t>       ("SetFaceMorph",                    "ActorBase", SetFaceMorph));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetFacePreset),					 TESNPC, uint32_t, uint32_t>          ("GetFacePreset",                   "ActorBase", GetFacePreset));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetFacePreset),					 TESNPC, void, uint32_t, uint32_t>    ("SetFacePreset",                   "ActorBase", SetFacePreset));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetHairColor),						 TESNPC, BGSColorForm*>               ("GetHairColor",                    "ActorBase", GetHairColor));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetHairColor),						 TESNPC, void, BGSColorForm*>         ("SetHairColor",                    "ActorBase", SetHairColor));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetFaceTextureSet),				 TESNPC, BGSTextureSet*>              ("GetFaceTextureSet",               "ActorBase", GetFaceTextureSet));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetFaceTextureSet),				 TESNPC, void, BGSTextureSet*>        ("SetFaceTextureSet",               "ActorBase", SetFaceTextureSet));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetSkin),							 TESNPC, TESObjectARMO*>              ("GetSkin",                         "ActorBase", GetSkin));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetSkin),							 TESNPC, void, TESObjectARMO*>        ("SetSkin",                         "ActorBase", SetSkin));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetSkinFar),						 TESNPC, TESObjectARMO*>              ("GetSkinFar",                      "ActorBase", GetSkinFar));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetSkinFar),						 TESNPC, void, TESObjectARMO*>        ("SetSkinFar",                      "ActorBase", SetSkinFar));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetTemplate),						 TESNPC, TESNPC*>                     ("GetTemplate",                     "ActorBase", GetTemplate));

		VM->SetCallableFromTasklets("ActorBase", "GetCombatStyle", true);
		VM->SetCallableFromTasklets("ActorBase", "SetCombatStyle", true);
		VM->SetCallableFromTasklets("ActorBase", "GetOutfit", true);
		VM->SetCallableFromTasklets("ActorBase", "SetClass", true);
		VM->SetCallableFromTasklets("ActorBase", "GetSpellCount", true);
		VM->SetCallableFromTasklets("ActorBase", "GetNthSpell", true);
		VM->SetCallableFromTasklets("ActorBase", "GetHeight", true);
		VM->SetCallableFromTasklets("ActorBase", "SetHeight", true);
		VM->SetCallableFromTasklets("ActorBase", "GetWeight", true);
		VM->SetCallableFromTasklets("ActorBase", "SetWeight", true);
		VM->SetCallableFromTasklets("ActorBase", "GetNumHeadParts", true);
		VM->SetCallableFromTasklets("ActorBase", "GetNthHeadPart", true);
		VM->SetCallableFromTasklets("ActorBase", "SetNthHeadPart", true);
		VM->SetCallableFromTasklets("ActorBase", "GetIndexOfHeadPartByType", true);
		VM->SetCallableFromTasklets("ActorBase", "GetNumOverlayHeadParts", true);
		VM->SetCallableFromTasklets("ActorBase", "GetNthOverlayHeadPart", true);
		VM->SetCallableFromTasklets("ActorBase", "GetIndexOfOverlayHeadPartByType", true);
		VM->SetCallableFromTasklets("ActorBase", "GetFaceMorph", true);
		VM->SetCallableFromTasklets("ActorBase", "SetFaceMorph", true);
		VM->SetCallableFromTasklets("ActorBase", "GetFacePreset", true);
		VM->SetCallableFromTasklets("ActorBase", "SetFacePreset", true);
		VM->SetCallableFromTasklets("ActorBase", "SetHairColor", true);
		VM->SetCallableFromTasklets("ActorBase", "GetHairColor", true);
		VM->SetCallableFromTasklets("ActorBase", "GetFaceTextureSet", true);
		VM->SetCallableFromTasklets("ActorBase", "SetFaceTextureSet", true);
		VM->SetCallableFromTasklets("ActorBase", "GetSkin", true);
		VM->SetCallableFromTasklets("ActorBase", "SetSkin", true);
		VM->SetCallableFromTasklets("ActorBase", "GetTemplate", true);

		return true;
	}
}