#include "ConsoleCommands.h"

#include "../../../../OrbisUtil/include/DialogueManger.h"

namespace ConsoleCommands
{
	Relocation<bool*> God										 ("g_godmode",                   0x3183ED0);
	Relocation<TYPE_BOOL_NO_ARGS> SkyrimVM_DumpStacks			 ("SkyrimVM:DUP",                0x2C4EE0);
	Relocation<TYPE_BOOL_NO_ARGS> SkyrimVM_DumpUpdateStacks		 ("SkyrimVM:DumpPapyrusUpdates", 0x2C4F00);
	Relocation<ObjectReference_AddItemT> ObjectReference_AddItem ("AddItem:ObjectReference",     0xB65EE0);
	Relocation<Game_TeachWordT> Game_TeachWord                   ("Game:TeachWord",              0xB46310);
	Relocation<Game_addspell>   Game_AddSpell                    ("Game:addspell",               0xB1C2B0);

	bool ToggleGodMode()
	{
		if (*God)
		{
			*God = false;
		}
		else
		{
			*God = true;
		}

		return *God;
	}

	void QuickQuit()
	{
		xUtilty::Notify("Goodbye!");
		sceSystemServiceLoadExec("exit", nullptr);
	}

	bool DumpPapyrusStacks()
	{
		return SkyrimVM_DumpStacks();
	}

	bool DumpPapyrusUpdates()
	{
		return SkyrimVM_DumpUpdateStacks();
	}

	void SetGlobalTimeMultiplier()
	{
		char buffer[2048]{ 0 };
		auto _OrbisDialogueManger = xUtilty::DialogueManger::OrbisDialogueManger::GetSingleton();
		_OrbisDialogueManger->InitializeImeDialog("SGTM... what scale?", "1.5f");
		_OrbisDialogueManger->ShowImeDialog(buffer);
	}

	bool ToggleMapMarkers()
	{
		// typedef bool(*_TMM)(void*, void*, void*, void*, void*, void*, double*, unsigned int*);
		// Relocation<_TMM> tmm(0x2B5BB0);
		// return tmm(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
		return false;
	}

	void PlayerAddItem()
	{
		char buffer[2048]{ 0 };

		auto _OrbisDialogueManger = xUtilty::DialogueManger::OrbisDialogueManger::GetSingleton();
		_OrbisDialogueManger->InitializeImeDialog("player.additem... what formID?", "15");
		if (_OrbisDialogueManger->ShowImeDialog(buffer) != 0)
			return;

		auto FormID = std::stoi(buffer);

		_OrbisDialogueManger->InitializeImeDialog("player.additem... how many??", "100");
		if (_OrbisDialogueManger->ShowImeDialog(buffer) != 0)
			return;

		auto count = std::stoi(buffer);

		_OrbisDialogueManger->InitializeMsgDialog("player.additem... add silently?", xUtilty::DialogueManger::OrbisDialogueManger::Mode::M_USER_MSG, xUtilty::DialogueManger::OrbisDialogueManger::ButtonType::BT_YESNO_FOCUS_NO);
		_OrbisDialogueManger->ShowMsgDialog();
		bool silentmode = (_OrbisDialogueManger->GetMsgDialogResult()->buttonId == 1);

		sprintf(buffer, "FormID \"0x%lx\" count \"%d\" mode \"%s\" is this correct?", FormID, count, BOOL_TYPE_AS_STRING(silentmode));
		_OrbisDialogueManger->InitializeMsgDialog(buffer, xUtilty::DialogueManger::OrbisDialogueManger::M_USER_MSG, xUtilty::DialogueManger::OrbisDialogueManger::BT_YESNO);
		if (_OrbisDialogueManger->ShowMsgDialog() != 0)
			return;

		if (_OrbisDialogueManger->GetMsgDialogResult()->buttonId != 1)
			return;

		auto* form = ConsoleRE::TESForm::GetFormFromID(FormID);
		if (!form)
		{
			xUtilty::Notify("Failed to find TESForm with that FormID");
			return;
		}

		auto VM = ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton();
		xUtilty::KernelPrintOut("VM is %p", VM);
		ObjectReference_AddItem(VM, 0, ConsoleRE::PlayerCharacter::GetSingleton(), form, count, silentmode);
	}

	void ADDALL()
	{
		auto* gold = ConsoleRE::TESForm::GetFormFromID(15);
		auto* DaedricArmor = ConsoleRE::TESForm::GetFormFromID(0x0001396B);
		auto* DaedricBoots = ConsoleRE::TESForm::GetFormFromID(0x0001396A);
		auto* DaedricGauntlets = ConsoleRE::TESForm::GetFormFromID(0x0001396C);
		auto* DaedricHelmet = ConsoleRE::TESForm::GetFormFromID(0x0001396D);
		auto* DaedricShield = ConsoleRE::TESForm::GetFormFromID(0x0001396E);
		auto* VM = ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton();
		auto* player = ConsoleRE::PlayerCharacter::GetSingleton();

		ObjectReference_AddItem(VM, 0, player, gold, 1000000000, false);
		ObjectReference_AddItem(VM, 0, player, DaedricArmor, 10, false);
		ObjectReference_AddItem(VM, 0, player, DaedricBoots, 10, false);
		ObjectReference_AddItem(VM, 0, player, DaedricGauntlets, 10, false);
		ObjectReference_AddItem(VM, 0, player, DaedricHelmet, 10, false);
		ObjectReference_AddItem(VM, 0, player, DaedricShield, 10, false);

	}

	void OpenConsole()
	{
		ConsoleRE::UIMessageQueue::GetSingleton()->AddMessage(ConsoleRE::UIMenuStrings::GetSingleton()->console, 1, nullptr);
	}

	void CloseConsole()
	{
		ConsoleRE::UIMessageQueue::GetSingleton()->AddMessage(ConsoleRE::UIMenuStrings::GetSingleton()->console, 3, nullptr);
	}

	void teachword()
	{
		char buffer[2048]{ 0 };
		const auto& odialoguemanger = xUtilty::DialogueManger::OrbisDialogueManger::GetSingleton();
		odialoguemanger->InitializeImeDialog("player.teachword", "393882");
		if (odialoguemanger->ShowImeDialog(buffer) == 0)
		{
			uint32_t id = std::stoi(buffer);
			auto* form = ConsoleRE::TESForm::GetFormFromID(id);
			if (form)
			{
				Game_TeachWord(ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton(), 0, ConsoleRE::PlayerCharacter::GetSingleton(), form);
			}
		}
	}

	void AddSpell()
	{
		char buffer[2048]{ 0 };

		const auto& odialoguemanger = xUtilty::DialogueManger::OrbisDialogueManger::GetSingleton();
		odialoguemanger->InitializeImeDialog("player.addspell", "77776");
		if (odialoguemanger->ShowImeDialog(buffer) == 0)
		{
			uint32_t id = std::stoi(buffer);
			auto* form = ConsoleRE::TESForm::GetFormFromID(id);
			if (form)
			{
				Game_AddSpell(ConsoleRE::BSScript::Internal::VirtualMachine::GetSingleton(), 0, ConsoleRE::PlayerCharacter::GetSingleton(), form);
			}
		}
	}
}