#include "../../../OrbisUtil/include/Relocation.h"

#include "../L/LockpickingMenu.h"

#include "../T/TESObjectREFR.h"

namespace ConsoleRE
{
	TESObjectREFR* LockpickingMenu::GetTargetReference()
	{
		Relocation<NiPointer<TESObjectREFR>*> refptr("", 0x319B7C8);
		return refptr->get();
	}

}