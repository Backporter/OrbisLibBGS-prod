#include "../Armor/PapyrusExtArmor.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source//N/NativeFunction.h"
#include "../../../../../../source/T/TESObjectARMA.h"
#include "../../../../../../source/T/TESObjectARMO.h"
#include "../../../../../../source/U/UI.h"
#include "../../../../../../source/U/UIMessageQueue.h"

namespace PapyrusExtConsole
{
	// I really hate doing this...
	using namespace ConsoleRE;

	void	ConsoleOpen(StaticFunctionTag* tag)
	{
		UIMessageQueue::GetSingleton()->AddMessage("Console", 1, 0);
	}

	void	ConsoleClose(StaticFunctionTag* tag)
	{
		UIMessageQueue::GetSingleton()->AddMessage("Console", 3, 0);
	}

	BSFixedString GetLastCommand(StaticFunctionTag* tag)
	{
		if (UI::GetSingleton()->IsMenuOpen("Console"))
		{
			// Console is currently open
			return NULL;
		}

		return "";
	}

	bool	RegisterConsole(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(ConsoleOpen),  StaticFunctionTag, void>("Open",  "Console", ConsoleOpen));
		VM->RegisterFunction(new BSScript::NativeFunction<false, NFDLSE(ConsoleClose), StaticFunctionTag, void>("Close", "Console", ConsoleClose));

		// VM->RegisterFunction(new BSScript::NativeFunction0<NFDLSE(GetLastCommand), StaticFunctionTag, BSFixedString>("GetLastCommand", "Console", GetLastCommand));
		return true;
	}
}