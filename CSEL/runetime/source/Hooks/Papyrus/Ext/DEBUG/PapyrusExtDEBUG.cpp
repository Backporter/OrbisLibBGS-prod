#include "../../../../../../../OrbisUtil/include//FileSystem.h"
#include "../../../../../../../OrbisUtil/include/SystemWrapper.h"
#include "../../../../../../../OrbisUtil/include/MemoryUsageTracker.h"
#include "../../../../../../../OrbisUtil/include/CPU.h"

#include "../../../../C/ConsoleCommands.h"

#include "../DEBUG/PapyrusExtDEBUG.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESObjectARMA.h"
#include "../../../../../../source/T/TESObjectARMO.h"
#include "../../../../../../source/T/TESDataHandler.h"
#include "../../../../../../source/U/UIMessageQueue.h"

#include "../../../../../../source/P/PlayerCharacter.h"
#include "../../../../../../source/U/UI.h"
#include "../../../../../../source/M/MapMenu.h"
#include "../../../../../../source/U/UIMenuStrings.h"
#include "../../../../../../source/U/UIMessageQueue.h"

namespace PapyrusExtDEBUG
{
	// I really hate doing this...
	using namespace ConsoleRE;
	
	void RunDebug(StaticFunctionTag* tag)
	{
		typedef void(*_FN)(ConsoleRE::BSScript::Internal::VirtualMachine* VM, uint32_t StaticID, ConsoleRE::TESForm* base, ConsoleRE::TESForm* toadd, int count, bool silent);
		Relocation<_FN> FN("AddItem:ObjectReference", 0xB65EE0);

		auto VM		= ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton();
		auto player = ConsoleRE::PlayerCharacter::GetSingleton();

		FN(VM, 0, player, ConsoleRE::TESForm::GetFormFromID(15), 10000000, true);

		std::vector<TESForm*> formstoAdd
		{
			ConsoleRE::TESForm::GetFormFromID(0x000a26ee), // Spell Tome: Banish Daedra
			ConsoleRE::TESForm::GetFormFromID(0x000a26ec), // Spell Tome: Conjure Flame Atronach
			ConsoleRE::TESForm::GetFormFromID(0x0009e2ab), // Spell Tome: Conjure Familiar
			ConsoleRE::TESForm::GetFormFromID(0x0010fd60), // Spell Tome: Conjure Dremora Lord
			ConsoleRE::TESForm::GetFormFromID(0x000a26fd), // Spell Tome: Firebolt
			ConsoleRE::TESForm::GetFormFromID(0x000a2706), // Spell Tome: Fireball

			ConsoleRE::TESForm::GetFormFromID(0x0001396B), // Daedric Armor
			ConsoleRE::TESForm::GetFormFromID(0x0001396A), // Daedric Boots
			ConsoleRE::TESForm::GetFormFromID(0x0001396C), // Daedric Gauntlets
			ConsoleRE::TESForm::GetFormFromID(0x0001396D), // Daedric Helmet
			ConsoleRE::TESForm::GetFormFromID(0x0001396E), // Daedric Shield
			ConsoleRE::TESForm::GetFormFromID(0x000139B9), // Daedric Sword
			ConsoleRE::TESForm::GetFormFromID(0x000139B5), // Daedric Bow
			ConsoleRE::TESForm::GetFormFromID(0x000139C0), // Daedric Arrow

			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
			// ConsoleRE::TESForm::GetFormFromID(0),
		};

		for (auto form : formstoAdd)
		{
			FN(VM, 0, player, form, 1, true);
		}

		ConsoleCommands::ToggleGodMode();
	}

	bool RegisterDEBUG(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{	
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(RunDebug), StaticFunctionTag, void> ("RunDebug", "Debug", RunDebug));
		return true;
	}
}