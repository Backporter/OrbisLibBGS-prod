#include "../../../../../../../OrbisUtil/include//FileSystem.h"
#include "../../../../../../../OrbisUtil/include/SystemWrapper.h"

#include "../Dump/PapyrusExtDump.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"

#include "../../../../../../source/E/EffectSetting.h"
#include "../../../../../../source/T/TESObjectWEAP.h"
#include "../../../../../../source/T/TESObjectREFR.h"
#include "../../../../../../source/T/TESObjectBOOK.h"
#include "../../../../../../source/A/AlchemyItem.h"
#include "../../../../../../source/T/TESSoulGem.h"
#include "../../../../../../source/T/TESSound.h"
#include "../../../../../../source/T/TESWeather.h"
#include "../../../../../../source/T/TESObjectTREE.h"
#include "../../../../../../source/T/TESForm.h"
#include "../../../../../../source/B/BGSColorForm.h"
#include "../../../../../../source/T/TESNPC.h"
#include "../../../../../../source/A/Actor.h"
#include "../../../../../../source/A/ActorValueInfo.h"
#include "../../../../../../source/T/TESAmmo.h"
#include "../../../../../../source/T/TESObjectCELL.h"
#include "../../../../../../source/T/TESObjectARMA.h"
#include "../../../../../../source/T/TESCombatStyle.h"
#include "../../../../../../source/B/BGSKeyword.h"
#include "../../../../../../source/B/BGSConstructibleObject.h"
#include "../../../../../../source/B/BGSDefaultObjectManager.h"
#include "../../../../../../source/B/BGSEquipSlot.h"
#include "../../../../../../source/T/TESFaction.h"
#include "../../../../../../source/T/TESFlora.h"
#include "../../../../../../source/B/BGSListForm.h"
#include "../../../../../../source/B/BGSHeadPart.h"
#include "../../../../../../source/I/IngredientItem.h"
#include "../../../../../../source/B/BGSKeyword.h"
#include "../../../../../../source/B/BGSTextureSet.h"
#include "../../../../../../source/T/TESShout.h"
#include "../../../../../../source/S/ScrollItem.h"
#include "../../../../../../source/T/TESRace.h"
#include "../../../../../../source/T/TESObjectARMO.h"
#include "../../../../../../source/B/BGSVoiceType.h"
#include "../../../../../../source/T/TESQuest.h"
#include "../../../../../../source/B/BGSBaseAlias.h"
#include "../../../../../../source/B/BGSPerk.h"
#include "../../../../../../source/T/TESObjectREFR.h"
#include "../../../../../../source/B/BGSApparatus.h"
#include "../../../../../../source/B/BGSOutfit.h"
#include "../../../../../../source/T/TESEffectShader.h"
#include "../../../../../../source/T/TESObjectLIGH.h"
#include "../../../../../../source/B/BGSProjectile.h"
#include "../../../../../../source/B/BGSExplosion.h"
#include "../../../../../../source/B/BGSArtObject.h"
#include "../../../../../../source/B/BGSArtObject.h"
#include "../../../../../../source/B/BGSImpactDataSet.h"
#include "../../../../../../source/T/TESImageSpaceModifier.h"
#include "../../../../../../source/T/TESLevSpell.h"
#include "../../../../../../source/T/TESLevItem.h"
#include "../../../../../../source/T/TESLeveledList.h"
#include "../../../../../../source/T/TESLevCharacter.h"
#include "../../../../../../source/B/BGSKeyword.h"
#include "../../../../../../source/I/IngredientItem.h"
#include "../../../../../../source/B/BGSHeadPart.h"
#include "../../../../../../source/B/BGSListForm.h"
#include "../../../../../../source/T/TESFlora.h"
#include "../../../../../../source/T/TESFaction.h"
#include "../../../../../../source/T/TESWorldSpace.h"
#include "../../../../../../source/B/BGSEquipSlot.h"
#include "../../../../../../source/B/BGSDefaultObjectManager.h"
#include "../../../../../../source/B/BGSConstructibleObject.h"
#include "../../../../../../source/T/TESCombatStyle.h"
#include "../../../../../../source/P/PlayerCamera.h"

#if defined(__OPENORBIS__)
#include <orbis/Rtc.h>
#include <orbis/libkernel.h>
typedef TimeTable SceRtcDateTime;
#elif defined(__ORBIS__)
#include <rtc.h>
#include <kernel.h>
#include <wchar.h>
#include <string>
#endif

namespace PapyrusExtDump
{
	// I really hate doing this...
	using namespace ConsoleRE;

	bool DumpTESObjectWEAP(TESObjectWEAP* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("Weapon/TESObjectWEAPG", base, 0x1F0);
		return true;
	}
	bool DumpTESObjectBOOK(TESObjectBOOK* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("Book/TESObjectBOOKG", base, 0x108);
		return true;
	}
	bool DumpAlchemyItem(AlchemyItem* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("Potion/AlchemyItemG", base, 0x120);
		return true;
	}
	bool DumpSoulGem(TESSoulGem* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("SoulGem/TESSoulGemG", base, 0xE0);
		return true;
	}
	bool DumpSpell(SpellItem* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("Spell/SpellItem", base, 0xD8);
		return true;
	}
	bool DumpEnchantmentItem(EnchantmentItem* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("Enchantment/EnchantmentItem", base, 0xB0);
		return true;
	}
	bool DumpEffectSetting(EffectSetting* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("MagicEffect/EffectSetting", base, 0x190);
		return true;
	}
	bool DumpTESSound(TESSound* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("Sound/TESSound", base, 0x30);
		return true;
	}
	bool DumpBGSSoundDescriptorForm(BGSSoundDescriptorForm* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("BGSSoundDescriptorForm/BGSSoundDescriptorForm", base, 0x30);
		return true;
	}
	bool DumpVM(BSScript::Internal::VirtualMachine* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("BSScript_Internal_VirtualMachine", base, 0x9488);
		return true;
	}
	bool DumpTESWeather(TESWeather* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("Weather/TESWeather", base, 0x8D0);
		return true;
	}

	bool DumpTESObjectTREE(TESObjectTREE* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESObjectTREE/TESObjectTREE", base, 0xC0);
		return true;
	}

	bool DumpBGSTextureSet(BGSTextureSet* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("BGSTextureSet/BGSTextureSet", base, 0x128);
		return true;
	}
	bool DumpTESShout(TESShout* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESShout/TESShout", base, 0xA8);
		return true;
	}
	bool DumpScrollItem(ScrollItem* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("ScrollItem/ScrollItem", base, 0x158);
		return true;
	}
	
	// ????
	bool DumpTESRace(TESRace* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESRace/TESRace", base, 0xFFFF);
		return true;
	}

	bool DumpTESObjectARMO(TESObjectARMO* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESObjectARMO/TESObjectARMO", base, 0x1C8);
		return true;
	}
	bool DumpBGSVoiceType(BGSVoiceType* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("BGSVoiceType/BGSVoiceType", base, 0x30);
		return true;
	}
	bool DumpTESQuest(TESQuest* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESQuest/TESQuest", base, 0x1D8);
		return true;
	}
	bool DumpBGSBaseAlias(BGSBaseAlias* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("BGSBaseAlias/BGSBaseAlias", base, 0x60);
		return true;
	}
	bool DumpBGSPerk(BGSPerk* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("BGSPerk/BGSPerk", base, 0x68);
		return true;
	}
	
	// ????
	bool DumpTESObjectREFR(TESObjectREFR* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESObjectREFR/TESObjectREFR", base, 0xFFFFFF);
		return true;
	}

	bool DumpBGSApparatus(BGSApparatus* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("BGSApparatus/BGSApparatus", base, 0xF0);
		return true;
	}
	bool DumpBGSOutfit(BGSOutfit* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("BGSOutfit/BGSOutfit", base, 0x30);
		return true;
	}
	bool DumpTESEffectShader(TESEffectShader* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESEffectShader/TESEffectShader", base, 0x220);
		return true;
	}
	bool DumpTESObjectLIGH(TESObjectLIGH* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESObjectLIGH/TESObjectLIGH", base, 0x100);
		return true;
	}
	bool DumpBGSProjectile(BGSProjectile* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("BGSProjectile/BGSProjectile", base, 0x130);
		return true;
	}
	bool DumpBGSExplosion(BGSExplosion* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("BGSExplosion/BGSExplosion", base, 0xE0);
		return true;
	}
	bool DumpBGSArtObject(BGSArtObject* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("BGSArtObject/BGSArtObject", base, 0x60u);
		return true;
	}
	bool DumpBGSImpactDataSet(BGSImpactDataSet* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("BGSImpactDataSet/BGSImpactDataSet", base, 0x48);
		return true;
	}
	bool DumpTESImageSpaceModifier(TESImageSpaceModifier* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESImageSpaceModifier/TESImageSpaceModifier", base, 0x2D8);
		return true;
	}
	bool DumpTESLevSpell(TESLevSpell* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESLevSpell/TESLevSpell", base, 0x50);
		return true;
	}
	bool DumpTESLevItem(TESLevItem* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESLevItem/TESLevItem", base, 0x50);
		return true;
	}
	
	// ????
	bool DumpTESLeveledList(TESLeveledList* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESLeveledList/TESLeveledList", base, 0xFFFFF);
		return true;
	}

	bool DumpTESLevCharacter(TESLevCharacter* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESLevCharacter/TESLevCharacter", base, 0x88);
		return true;
	}
	bool DumpBGSKeyword(BGSKeyword* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("BGSKeyword/BGSKeyword", base, 0x28);
		return true;
	}
	bool DumpIngredientItem(IngredientItem* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("IngredientItem/IngredientItem", base, 0x118);
		return true;
	}
	bool DumpBGSHeadPart(BGSHeadPart* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("BGSHeadPart/BGSHeadPart", base, 0x118);
		return true;
	}
	bool DumpBGSListForm(BGSListForm* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("BGSListForm/BGSListForm", base, 0x40);
		return true;
	}
	bool DumpTESFlora(TESFlora* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESFlora/TESFlora", base, 0xE0);
		return true;
	}
	bool DumoTESFaction(TESFaction* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESFaction/TESFaction", base, 0x100);
		return true;
	}
	bool DumpBGSEquipSlot(BGSEquipSlot* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("BGSEquipSlot/BGSEquipSlot", base, 0x38);
		return true;
	}
	
	// ???
	bool DumpBGSDefaultObjectManager(BGSDefaultObjectManager* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("BGSDefaultObjectManager/BGSDefaultObjectManager", base, 0xFFFFFF);
		return true;
	}

	bool DumpBGSConstructibleObject(BGSConstructibleObject* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("BGSConstructibleObject/BGSConstructibleObject", base, 0x58);
		return true;
	}
	bool DumpTESCombatStyle(TESCombatStyle* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESCombatStyle/TESCombatStyle", base, 0xA0);
		return true;
	}
	bool DumpTESObjectCELL(TESObjectCELL* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESObjectCELL/TESObjectCELL", base, 0x130);
		return true;
	}
	bool DumpTESObjectARMA(TESObjectARMA* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESObjectARMA/TESObjectARMA", base, 0x170);
		return true;
	}
	bool DumpTESAmmo(TESAmmo* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESAmmo/TESAmmo", base, 0xF8);
		return true;
	}
	bool DumpActorValueInfo(ActorValueInfo* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("ActorValueInfo/ActorValueInfo", base, 0x118);
		return true;
	}
	bool DumpActor(Actor* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("Actor/Actor", base, 0x2A8);
		return true;
	}
	bool DumpTESNPC(TESNPC* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESNPC/TESNPC", base, 0x258);
		return true;
	}
	bool DumpBGSColorForm(BGSColorForm* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("BGSColorForm/BGSColorForm", base, 0x38);
		return true;
	}
	bool DumpTESForm(TESForm* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESForm/TESForm", base, sizeof(TESForm));
		return true;
	}
	bool DumpCamera(StaticFunctionTag*)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, ConsoleRE::PlayerCamera::GetSingleton());
		xUtilty::FileSystem::Dump("Camera/Camera", ConsoleRE::PlayerCamera::GetSingleton(), sizeof(PlayerCamera));
		return true;
	}
	bool DumpTESWorldSpace(TESWorldSpace* base)
	{
		xUtilty::KernelPrintOut("%s %p", __FUNCTION__, base);
		xUtilty::FileSystem::Dump("TESWorldSpace/TESWorldSpace", base, 0x2C8);
		return true;
	}

	bool RegisterDump(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		// ??
		// VM->RegisterFunction(new BSScript::NativeFunction0<NFDLSE(DumpTESObjectTREE),		ConsoleRE::TESObjectTREE,			bool>("Dump", "TreeObject",			DumpTESObjectTREE,			VM));
		// VM->RegisterFunction(new BSScript::NativeFunction0<NFDLSE(DumpActorValueInfo),		ConsoleRE::ActorValueInfo,			bool>("Dump", "ActorValueInfo",		DumpActorValueInfo,			VM));
		// VM->RegisterFunction(new BSScript::NativeFunction0<NFDLSE(DumpTESCombatStyle),		ConsoleRE::TESCombatStyle,			bool>("Dump", "CombatStyle",		DumpTESCombatStyle,			VM));
		// VM->RegisterFunction(new BSScript::NativeFunction0<NFDLSE(DumpBGSEquipSlot),			ConsoleRE::BGSEquipSlot,			bool>("Dump", "EquipSlot",			DumpBGSEquipSlot,			VM));
		// VM->RegisterFunction(new BSScript::NativeFunction0<NFDLSE(DumpBGSHeadPart),			ConsoleRE::BGSHeadPart,				bool>("Dump", "HeadPart",			DumpBGSHeadPart,			VM));
		// VM->RegisterFunction(new BSScript::NativeFunction0<NFDLSE(DumpBGSArtObject),			ConsoleRE::BGSArtObject,			bool>("Dump", "Art",				DumpBGSArtObject,			VM));


		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpTESObjectWEAP),				ConsoleRE::TESObjectWEAP,			bool>("Dump", "Weapon",			    DumpTESObjectWEAP));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpTESObjectBOOK),				ConsoleRE::TESObjectBOOK,			bool>("Dump", "Book",			    DumpTESObjectBOOK));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpAlchemyItem),				ConsoleRE::AlchemyItem,				bool>("Dump", "Potion",			    DumpAlchemyItem));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpSoulGem),					ConsoleRE::TESSoulGem,				bool>("Dump", "SoulGem",		    DumpSoulGem));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpSpell),						ConsoleRE::SpellItem,				bool>("Dump", "Spell",			    DumpSpell));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpEnchantmentItem),			ConsoleRE::EnchantmentItem,			bool>("Dump", "Enchantment",	    DumpEnchantmentItem));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpEffectSetting),				ConsoleRE::EffectSetting,			bool>("Dump", "MagicEffect",	    DumpEffectSetting));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpTESSound),					ConsoleRE::TESSound,				bool>("Dump", "Sound",			    DumpTESSound));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpBGSSoundDescriptorForm),		ConsoleRE::BGSSoundDescriptorForm,  bool>("Dump", "SoundDescriptor",    DumpBGSSoundDescriptorForm));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpTESWeather),					ConsoleRE::TESWeather,				bool>("Dump", "Weather",			DumpTESWeather));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpActor),						ConsoleRE::Actor,					bool>("Dump", "Actor",				DumpActor));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpTESAmmo),					ConsoleRE::TESAmmo,					bool>("Dump", "Ammo",				DumpTESAmmo));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpTESObjectARMA),				ConsoleRE::TESObjectARMA,			bool>("Dump", "ArmorAddon",			DumpTESObjectARMA));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpTESObjectCELL),				ConsoleRE::TESObjectCELL,			bool>("Dump", "Cell",				DumpTESObjectCELL));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpBGSConstructibleObject),		ConsoleRE::BGSConstructibleObject,	bool>("Dump", "ConstructibleObject", DumpBGSConstructibleObject));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumoTESFaction),					ConsoleRE::TESFaction,				bool>("Dump", "Faction",			DumoTESFaction));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpTESFlora),					ConsoleRE::TESFlora,				bool>("Dump", "Flora",				DumpTESFlora));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpBGSListForm),				ConsoleRE::BGSListForm,				bool>("Dump", "FormList",			DumpBGSListForm));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpIngredientItem),				ConsoleRE::IngredientItem,			bool>("Dump", "Ingredient",			DumpIngredientItem));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpBGSKeyword),					ConsoleRE::BGSKeyword,				bool>("Dump", "Keyword",			DumpBGSKeyword));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpTESLevCharacter),			ConsoleRE::TESLevCharacter,			bool>("Dump", "LeveledActor",		DumpTESLevCharacter));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpTESLevItem),					ConsoleRE::TESLevItem,				bool>("Dump", "LeveledItem",		DumpTESLevItem));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpTESLevSpell),				ConsoleRE::TESLevSpell,				bool>("Dump", "LeveledSpell",		DumpTESLevSpell));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpBGSOutfit),					ConsoleRE::BGSOutfit,				bool>("Dump", "Outfit",				DumpBGSOutfit));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpBGSApparatus),				ConsoleRE::BGSApparatus,			bool>("Dump", "Apparatus",			DumpBGSApparatus));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpBGSPerk),					ConsoleRE::BGSPerk,					bool>("Dump", "Perk",				DumpBGSPerk));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpBGSBaseAlias),				ConsoleRE::BGSBaseAlias,			bool>("Dump", "Alias",				DumpBGSBaseAlias));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpTESQuest),					ConsoleRE::TESQuest,				bool>("Dump", "Quest",				DumpTESQuest));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpTESObjectARMO),				ConsoleRE::TESObjectARMO,			bool>("Dump", "Armor",				DumpTESObjectARMO));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpScrollItem),					ConsoleRE::ScrollItem,				bool>("Dump", "Scroll",				DumpScrollItem));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpTESShout),					ConsoleRE::TESShout,				bool>("Dump", "Shout",				DumpTESShout));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpBGSTextureSet),				ConsoleRE::BGSTextureSet,			bool>("Dump", "TextureSet",			DumpBGSTextureSet));

		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpCamera),						StaticFunctionTag,                  bool>("Dump", "Camera",             DumpCamera));
		VM->RegisterFunction(new BSScript::NativeFunction<false,	NFDLSE(DumpTESWorldSpace),				TESWorldSpace,                      bool>("Dump", "WorldSpace",         DumpTESWorldSpace));

		return true;
	}
}