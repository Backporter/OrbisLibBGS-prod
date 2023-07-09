#pragma once

#include "../../../source/P/PlayerCharacter.h"
#include "../../../source/T/TESForm.h"

#include "../../../source/U/UI.h"
#include "../../../source/U/UIMenuStrings.h"
#include "../../../source/U/UIMessageQueue.h"
#include "../../../source/V/VirtualMachine.h"

#include <atomic>
#include <algorithm>
#include <string>
#include <iostream>

#if defined(__ORBIS__)
#include <kernel.h>
#include <system_service.h>
#elif defined (__OPENORBIS__)
#include <orbis/libkernel.h>
#include <orbis/SystemService.h>
#endif


namespace ConsoleCommands
{
	typedef bool(*TYPE_BOOL_NO_ARGS)();
	typedef void(*ObjectReference_AddItemT)(ConsoleRE::BSScript::Internal::VirtualMachine* VM, uint32_t StaticID, ConsoleRE::TESForm* base, ConsoleRE::TESForm* toadd, int count, bool silent);
	typedef void(*Game_TeachWordT)(ConsoleRE::BSScript::Internal::VirtualMachine* VM, uint32_t StaticID, ConsoleRE::TESForm* base, ConsoleRE::TESForm* toadd);
	typedef void(*Game_addspell)(ConsoleRE::BSScript::Internal::VirtualMachine* VM, uint32_t StaticID, ConsoleRE::TESForm* base, ConsoleRE::TESForm* toadd);

	extern Relocation<bool*> God;
	extern Relocation<TYPE_BOOL_NO_ARGS> SkyrimVM_DumpStacks;
	extern Relocation<TYPE_BOOL_NO_ARGS> SkyrimVM_DumpUpdateStacks;
	extern Relocation<ObjectReference_AddItemT> ObjectReference_AddItem;
	extern Relocation<Game_TeachWordT> Game_TeachWord;
	extern Relocation<Game_addspell> Game_AddSpell;

	bool ToggleGodMode();
	void QuickQuit();
	bool DumpPapyrusStacks();
	bool DumpPapyrusUpdates();
	void SetGlobalTimeMultiplier();
	bool ToggleMapMarkers();
	void PlayerAddItem();
	void ADDALL();

	void OpenConsole();
	void CloseConsole();
	void teachword();
	void AddSpell();
}