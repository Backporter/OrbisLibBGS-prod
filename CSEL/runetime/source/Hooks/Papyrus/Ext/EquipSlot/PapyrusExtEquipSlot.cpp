#include "../EquipSlot/PapyrusExtEquipSlot.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/B/BGSEquipSlot.h"

namespace PapyrusExtEquipSlot
{
	// I really hate doing this...
	using namespace ConsoleRE;

	uint32_t GetNumParents(BGSEquipSlot* equipSlot)
	{
		return (equipSlot) ? equipSlot->Parent.m_size : 0;
	}

	BGSEquipSlot* GetNthParent(BGSEquipSlot* equipSlot, uint32_t n)
	{
		if (equipSlot) 
		{
			BGSEquipSlot* nthSlot = NULL;
			equipSlot->Parent.Get(n, nthSlot);
			if (nthSlot)
				return nthSlot;
		}

		return NULL;
	}

	bool RegisterEquipSlot(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNumParents), BGSEquipSlot, uint32_t>                ("GetNumParents", "EquipSlot", GetNumParents));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthParent),  BGSEquipSlot, BGSEquipSlot*, uint32_t> ("GetNthParent",  "EquipSlot", GetNthParent));

		return true;
	}
}