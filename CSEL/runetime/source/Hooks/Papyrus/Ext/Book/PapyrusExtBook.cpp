#include "../Book/PapyrusExtBook.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESObjectBOOK.h"

namespace PapyrusExtBook
{
	// I really hate doing this...
	using namespace ConsoleRE;

	uint32_t GetSkill(TESObjectBOOK * thisBook)
	{
		if (thisBook && thisBook->TeachesSkill())
			return thisBook->data.teaches.actorValueToAdvance;

		return 0;
	}

	SpellItem * GetSpell(TESObjectBOOK * thisBook)
	{
		if (thisBook && thisBook->TeachesSpell())
			return thisBook->data.teaches.spell;

		return NULL;
	}

	bool IsRead(TESObjectBOOK * thisBook)
	{
		if (thisBook)
			return thisBook->IsRead();

		return false;
	}

	bool IsTakeable(TESObjectBOOK * thisBook)
	{
		if (thisBook)
			return thisBook->CanBeTaken();
		
		return false;
	}

	bool RegisterBook(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetSkill),   TESObjectBOOK, uint32_t>   ("GetSkill",   "Book", GetSkill));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetSpell),   TESObjectBOOK, SpellItem*> ("GetSpell",   "Book", GetSpell));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(IsRead),     TESObjectBOOK, bool>       ("IsRead",     "Book", IsRead));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(IsTakeable), TESObjectBOOK, bool>       ("IsTakeable", "Book", IsTakeable));
		
		return true;
	}
}