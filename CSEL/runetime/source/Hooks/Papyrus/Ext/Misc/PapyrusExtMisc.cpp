#include "../Misc/PapyrusExtMisc.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESWeather.h"

namespace PapyrusExtMisc
{
	// I really hate doing this...
	using namespace ConsoleRE;

	bool RegisterMisc(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		return true;
	}
}