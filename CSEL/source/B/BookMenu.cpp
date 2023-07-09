#include "../B/BookMenu.h"

namespace ConsoleRE
{
	TESObjectREFR* BookMenu::GetTargetReference()
	{
		Relocation<NiPointer<TESObjectREFR>*> refptr("", 0x3198BC8);
		return refptr->get();
	}
}