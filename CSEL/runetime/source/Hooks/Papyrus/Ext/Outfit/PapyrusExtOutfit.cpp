#include "../Outfit/PapyrusExtOutfit.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/B/BGSOutfit.h"

namespace PapyrusExtOutfit
{
	// I really hate doing this...
	using namespace ConsoleRE;

	uint32_t GetNumParts(BGSOutfit* thisOutfit)
	{
		return thisOutfit ? thisOutfit->outfitItems.m_size : 0;
	}

	TESForm* GetNthPart(BGSOutfit* thisOutfit, uint32_t n)
	{
		TESForm* pForm = NULL;

		if (thisOutfit) 
		{
			thisOutfit->outfitItems.Get(n, pForm);
		}

		return pForm;
	}

	bool RegisterOutfit(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNumParts), BGSOutfit, uint32_t>          ("GetNumParts", "Outfit", GetNumParts));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthPart),  BGSOutfit, TESForm*, uint32_t>("GetNthPart",  "Outfit", GetNthPart));

		return true;
	}
}