#include "../M/MenuTopicManager.h"

#include "../T/TESObjectREFR.h"

namespace ConsoleRE
{
	NiPointer<TESObjectREFR> MenuTopicManager::GetDialogueTarget()
	{
		Relocation<void(*)(uint32_t&, NiPointer<TESObjectREFR>&)> func("", 0x5DB210);
		Relocation<uint32_t*> g_invalidRefHandle("", 0x20BD820);

		//
		NiPointer<TESObjectREFR> refr;
		if (speaker == (*g_invalidRefHandle) || speaker == 0)
			return refr;

		func(speaker, refr);
		return refr;
	}

	MenuTopicManager* MenuTopicManager::GetSingleton()
	{
		Relocation<MenuTopicManager**> Singleton("", 0x30FC5C0);
		return *Singleton;
	}
}