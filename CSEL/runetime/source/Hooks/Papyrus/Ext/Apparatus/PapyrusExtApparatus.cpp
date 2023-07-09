#include "../Apparatus/PapyrusExtApparatus.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/B/BGSApparatus.h"

namespace PapyrusExtApparatus
{
	// I really hate doing this...
	using namespace ConsoleRE;

	uint32_t GetQuality(BGSApparatus* thisApparatus)
	{
		if (!thisApparatus)
			return 0;

		return thisApparatus->quality;
	}

	void SetQuality(BGSApparatus* thisApparatus, uint32_t nuQuality)
	{
		if (thisApparatus) 
		{
			thisApparatus->quality = nuQuality;
		}
	}

	bool RegisterApparatus(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetQuality), BGSApparatus, uint32_t>      ("GetQuality", "Apparatus", GetQuality));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetQuality), BGSApparatus, void, uint32_t>("SetQuality", "Apparatus", SetQuality));

		return true;
	}
}