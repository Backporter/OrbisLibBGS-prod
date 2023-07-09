#include "../Papyrus/PapyrusExt.h"

// 
#include "../Papyrus/Ext/PapyrusExtCSEL.h"
#include "../Papyrus/Ext/PapyrusExtPS4.h"
#include "../Papyrus/Ext/PapyrusExtTrophies.h"
#include "../Papyrus/Ext/PapyrusExtPLUGINS.h"
#include "../Papyrus/Ext/GPU/PapyrusExtGPU.h"
#include "../Papyrus/Ext/CPU/PapyrusExtCPU.h"
#include "../Papyrus/Ext/Memory/PapyrusExtMemory.h"
#include "../Papyrus/Ext/FrameUtil/PapyrusExtFrameUtil.h"
#include "../Papyrus/Ext/Console/PapyrusExtConsole.h"
#include "../Papyrus/Ext/Dump/PapyrusExtDump.h"
#include "../Papyrus/Ext/DEBUG/PapyrusExtDEBUG.h"

// 
#include "../Papyrus/Ext/Forms/PapyrusExtForms.h"
#include "../Papyrus/Ext/Input/PapyrusExtInput.h"
#include "../Papyrus/Ext/Math/PapyrusExtMath.h"
#include "../Papyrus/Ext/String/PapyrusExtString.h"
#include "../Papyrus/Ext/TESForm/PapyrusExtTESForm.h"
#include "../Papyrus/Ext/INI/PapyrusExtINI.h"
#include "../Papyrus/Ext/SoundDescriptor/PapyrusExtSoundDescriptor.h"
#include "../Papyrus/Ext/Sound/PapyrusExtSound.h"
#include "../Papyrus/Ext/Shout/PapyrusExtShout.h"
#include "../Papyrus/Ext/Flora/PapyrusExtFlora.h"
#include "../Papyrus/Ext/Tree/PapyrusExtTree.h"
#include "../Papyrus/Ext/Enchantment/PapyrusExtEnchantment.h"
#include "../Papyrus/Ext/Armor/PapyrusExtArmor.h"
#include "../Papyrus/Ext/Game/PapyrusExtGame.h"
#include "../Papyrus/Ext/ObjectReference/PapyrusExtObjectReference.h"
#include "../Papyrus/Ext/Spell/PapyrusExtSpell.h"
#include "../Papyrus/Ext/Scroll/PapyrusExtScroll.h"
#include "../Papyrus/Ext/TextureSets/PapyrusExtTextureSet.h"
#include "../Papyrus/Ext/Faction/PapyrusExtFaction.h"
#include "../Papyrus/Ext/Alias/PapyrusExtAlias.h"
#include "../Papyrus/Ext/Quest/PapyrusExtQuest.h"
#include "../Papyrus/Ext/ArmorAddon/PapyrusExtArmorAddon.h"
#include "../Papyrus/Ext/Weapon/PapyrusExtWeapon.h"
#include "../Papyrus/Ext/Weather/PapyrusExtWeather.h"
#include "../Papyrus/Ext/Art/PapyrusExtArt.h"
#include "../Papyrus/Ext/Book/PapyrusExtBook.h"
#include "../Papyrus/Ext/Camera/PapyrusExtCamera.h"
#include "../Papyrus/Ext/CombatStyle/PapyrusExtCombatStyle.h"
#include "../Papyrus/Ext/ConstructibleObject/PapyrusExtConstructibleObject.h"
#include "../Papyrus/Ext/EquipSlot/PapyrusExtEquipSlot.h"
#include "../Papyrus/Ext/FormList/PapyrusExtFormList.h"
#include "../Papyrus/Ext/LeveledActor/PapyrusExtLeveledActor.h"
#include "../Papyrus/Ext/LeveledSpell/PapyrusExtLeveledSpell.h"
#include "../Papyrus/Ext/LeveledItem/PapyrusExtLeveledItem.h"
#include "../Papyrus/Ext/Util/PapyrusExtUtil.h"
#include "../Papyrus/Ext/WornObject/PapyrusExtWornObject.h"
#include "../Papyrus/Ext/Race/PapyrusExtRace.h"
#include "../Papyrus/Ext/Potion/PapyrusExtPotion.h"
#include "../Papyrus/Ext/Perk/PapyrusExtPerk.h"
#include "../Papyrus/Ext/MagicEffect/PapyrusExtMagicEffect.h"
#include "../Papyrus/Ext/Keyword/PapyrusExtKeyword.h"
#include "../Papyrus/Ext/Ingredient/PapyrusExtIngredient.h"
#include "../Papyrus/Ext/HeadPart/PapyrusExtHeadPart.h"
#include "../Papyrus/Ext/DefaultObjectManager/PapyrusExtDefaultObjectManager.h"
#include "../Papyrus/Ext/Cell/PapyrusExtCell.h"
#include "../Papyrus/Ext/ActorValueInfo/PapyrusExtActorValueInfo.h"
#include "../Papyrus/Ext/Actor/PapyrusExtActor.h"
#include "../Papyrus/Ext/SoulGem/PapyrusExtSoulGem.h"
#include "../Papyrus/Ext/Apparatus/PapyrusExtApparatus.h"
#include "../Papyrus/Ext/Outfit/PapyrusExtOutfit.h"
#include "../Papyrus/Ext/NetImmerse/PapyrusExtNetImmerse.h"
#include "../Papyrus\Ext/Ammo/PapyrusExtAmmo.h"
#include "../Papyrus/Ext/ColorForm/PapyrusExtColorForm.h"
#include "../Papyrus/Ext/ColorComponent/PapyrusExtColorComponent.h"
#include "../Papyrus/Ext/Misc/PapyrusExtMisc.h"
#include "../Papyrus/Ext/NPC/PapyrusExtNPC.h"
#include "../Papyrus/Ext/GameData/PapyrusExtGameData.h"
#include "../Papyrus/Ext/ActiveEffect/PapyrusExtActiveEffect.h"
#include "../Papyrus/Ext/UI/PapyrusExtUI.h"

//
#include "../../../../Build/Flags.h"

#if USE_SKSE_ADDON
#include "../../../../EXTERNAL/SKSE/SKSE.h"
#endif

#include <vector>
#include <assert.h>

namespace Papyrus
{	
	namespace Plugin
	{
		// 
		static std::vector<RegisterPluginFunctions_t*> g_papyrusFuncs;

		// 
		void RegisterPluginFunctions(RegisterPluginFunctions_t* a_func)
		{
			g_papyrusFuncs.push_back(a_func);
		}

		// 
		void UnregisterPluginFunctions(RegisterPluginFunctions_t* a_func)
		{
			for (auto iter = g_papyrusFuncs.begin(); iter != g_papyrusFuncs.end(); ++iter)
			{
				if ((*iter) == a_func)
				{
					g_papyrusFuncs.erase(iter);
				}
			}
		}
	}

	// 
	Relocation<RegisterFunctions_t*> _RegisterPapyrusFunctions;

	void RegisterPapyrus(ConsoleRE::BSScript::Internal::VirtualMachine** arg_VM)
	{
		_RegisterPapyrusFunctions(arg_VM);

		ConsoleRE::BSScript::Internal::VirtualMachine* VM = *arg_VM;

		// 
		PapyrusExtCSEL::RegisterCSEL(VM);
		PapyrusExtPS4::RegisterPS4(VM);
		PapyrusExtTrophies::RegisterTrophies(VM);
		PapyrusExtPLUGINS::RegisterPLUGINS(VM);
		PapyrusExtGPU::RegisterGPU(VM);
		PapyrusExtCPU::RegisterCPU(VM);
		PapyrusExtMemory::RegisterMemory(VM);
		PapyrusExtFrameUtil::RegisterFrameUtil(VM);
		PapyrusExtConsole::RegisterConsole(VM);
		PapyrusExtDump::RegisterDump(VM);
		PapyrusExtDEBUG::RegisterDEBUG(VM);

		// 
		PapyrusExtForms::RegisterForms(VM);
		PapyrusExtInput::RegisterInput(VM);
		PapyrusExtMath::RegisterMath(VM);
		PapyrusExtString::RegisterString(VM);
		PapyrusExtTESForm::RegisterForm(VM);
		PapyrusExtUI::RegisterUI(VM);
		PapyrusExtINI::RegisterINI(VM);
		PapyrusExtSoundDescriptor::RegisterSoundDescriptor(VM);
		PapyrusExtSound::RegisterSound(VM);
		PapyrusExtShout::RegisterShout(VM);
		PapyrusExtFlora::RegisterFlora(VM);
		PapyrusExtTree::RegisterTree(VM);
		PapyrusExtEnchantment::RegisterEnchantment(VM);
		PapyrusExtArmor::RegisterArmor(VM);
		PapyrusExtGame::RegisterGame(VM);
		PapyrusExtObjectReference::RegisterObjectReference(VM);
		PapyrusExtActiveEffect::RegisterActiveEffect(VM);
		PapyrusExtSpell::RegisterSpell(VM);
		PapyrusExtScroll::RegisterScroll(VM);
		PapyrusExtTextureSet::RegisterTextureSet(VM);
		PapyrusExtFaction::RegisterFaction(VM);
		PapyrusExtAlias::RegisterAlias(VM);
		PapyrusExtQuest::RegisterQuest(VM);
		PapyrusExtArmorAddon::RegisterArmorAddon(VM);
		PapyrusExtWeapon::RegisterWeapon(VM);
		PapyrusExtWeather::RegisterWeather(VM);
		PapyrusExtArt::RegisterArt(VM);
		PapyrusExtBook::RegisterBook(VM);
		PapyrusExtCamera::RegisterCamera(VM);
		PapyrusExtCombatStyle::RegisterCombatStyle(VM);
		PapyrusExtConstructibleObject::RegisterConstructibleObject(VM);
		PapyrusExtEquipSlot::RegisterEquipSlot(VM);
		PapyrusExtFormList::RegisterFormList(VM);
		PapyrusExtLeveledItem::RegisterLeveledItem(VM);
		PapyrusExtLeveledSpell::RegisterLeveledSpell(VM);
		PapyrusExtLeveledActor::RegisterLeveledActor(VM);
		PapyrusExtUtil::RegisterUtil(VM);
		PapyrusExtWornObject::RegisterWornObject(VM);
		PapyrusExtRace::RegisterRace(VM);
		PapyrusExtPotion::RegisterPotion(VM);
		PapyrusExtPerk::RegisterPerk(VM);
		PapyrusExtMagicEffect::RegisterMagicEffect(VM);
		PapyrusExtKeyword::RegisterKeyword(VM);
		PapyrusExtIngredient::RegisterIngredient(VM);
		PapyrusExtHeadPart::RegisterHeadPart(VM);
		PapyrusExtDefaultObjectManager::RegisterDefaultObjectManager(VM);
		PapyrusExtCell::RegisterCell(VM);
		PapyrusExtActorValueInfo::RegisterActorValueInfo(VM);
		PapyrusExtActor::RegisterActor(VM);
		PapyrusExtSoulGem::RegisterSoulGem(VM);
		PapyrusExtApparatus::RegisterApparatus(VM);
		PapyrusExtOutfit::RegisterOutfit(VM);
		PapyrusExtNetImmerse::RegisterNetImmerse(VM);
		PapyrusExtAmmo::RegisterAmmo(VM);
		PapyrusExtColorForm::RegisterColorForm(VM);
		PapyrusExtColorComponent::RegisterColorComponent(VM);
		PapyrusExtMisc::RegisterMisc(VM);
		PapyrusExtNPC::RegisterNPC(VM);
		PapyrusExtGameData::RegisterGameData(VM);

		for (auto func : Plugin::g_papyrusFuncs)
		{
			func(VM);
		}
	}
}