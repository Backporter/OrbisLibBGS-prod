#include "../SoulGem/PapyrusExtSoulGem.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESSoulGem.h"

namespace PapyrusExtSoulGem
{
	// I really hate doing this...
	using namespace ConsoleRE;

	uint32_t GetSoulSize(TESSoulGem* thisGem)
	{
		if (!thisGem)
			return 0;

		return thisGem->GetContainedSoul();
	}

	uint32_t GetGemSize(TESSoulGem* thisGem)
	{
		if (!thisGem)
			return 0;

		return thisGem->GetMaximumCapacity();
	}

	bool RegisterSoulGem(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetSoulSize), TESSoulGem, uint32_t> ("GetSoulSize", "SoulGem", GetSoulSize));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetGemSize), TESSoulGem, uint32_t>  ("GetGemSize",  "SoulGem", GetGemSize));

		return true;
	}
}