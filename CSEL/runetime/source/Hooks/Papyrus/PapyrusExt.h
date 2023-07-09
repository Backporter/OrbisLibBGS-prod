#pragma once

#include "../../../../source/V/VirtualMachine.h"

namespace Papyrus
{
	namespace Plugin
	{
		using RegisterPluginFunctions_t = bool(ConsoleRE::BSScript::Internal::VirtualMachine*);

		void RegisterPluginFunctions(RegisterPluginFunctions_t*);
		void UnregisterPluginFunctions(RegisterPluginFunctions_t*);
	}

	using RegisterFunctions_t = void(ConsoleRE::BSScript::Internal::VirtualMachine**);
	extern Relocation<RegisterFunctions_t*> _RegisterPapyrusFunctions;

	void RegisterPapyrus(ConsoleRE::BSScript::Internal::VirtualMachine** arg_VM);
}