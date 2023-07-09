#pragma once

#include "../../../../../../source/V/VirtualMachine.h"

namespace PapyrusExtConsole
{
	class StaticFunctionTag;

	void	ConsoleOpen(StaticFunctionTag* tag);
	void	ConsoleClose(StaticFunctionTag* tag);

	bool RegisterConsole(ConsoleRE::BSScript::Internal::VirtualMachine*);
}