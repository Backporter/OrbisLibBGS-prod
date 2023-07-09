#include "../Cell/PapyrusExtCell.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/T/TESObjectCELL.h"
#include "../../../../../../source/T/TESObjectREFR.h"
#include "../../../../../../source/T/TESBoundObject.h"

namespace PapyrusExtCell
{
	// I really hate doing this...
	using namespace ConsoleRE;

	// int32_t GetNumRefs(TESObjectCELL* thisCell, uint32_t formType)
	// {
	// 	PRINT_POS;
	// 
	// 	if (!thisCell)
	// 		return 0;
	// 
	// 	if (formType == 0)
	// 		return thisCell->Unk98.FillCount();
	// 
	// 	uint32_t	numRefs = 0;
	// 	for (uint32_t i = 0; i < thisCell->Unk98.m_freeCount; i++)
	// 	{
	// 		auto entry = thisCell->Unk98.GetEntryAt(i);
	// 		if (entry->item)
	// 		{
	// 			if (entry->item->data.objectReference->FormType == formType)
	// 			{
	// 				numRefs++;
	// 			}
	// 		}
	// 	}
	// 
	// 	return numRefs;
	// }
	// 
	// TESObjectREFR* GetNthRef(TESObjectCELL* thisCell, uint32_t index, uint32_t formType)
	// {
	// 	PRINT_POS;
	// 
	// 	if (!thisCell)
	// 		return NULL;
	// 
	// 	for (uint32_t i = 0, n = 0; i < thisCell->Unk98.m_freeCount; i++)
	// 	{
	// 		auto entry = thisCell->Unk98.GetEntryAt(i);
	// 		if (entry->item)
	// 		{
	// 			if (formType == 0 || entry->item->data.objectReference->FormType == formType)
	// 			{
	// 				if (n++ == index)
	// 				{
	// 					return entry->item;
	// 				}
	// 			}
	// 		}
	// 	}
	// 
	// 	return NULL;
	// }
	//  
	// 
	// float GetWaterLevel(TESObjectCELL* thisCell)
	// {
	// 	if (!thisCell)
	// 	{
	// 		return LONG_MIN;
	// 	}
	//  
	//  	return thisCell->waterHeight;
	// }

	bool RegisterCell(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		// VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNumRefs),		TESObjectCELL, uint32_t, uint32_t>					("GetNumRefs",		"Cell", GetNumRefs));
		// VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetNthRef),		TESObjectCELL, TESObjectREFR*, uint32_t, uint32_t>	("GetNthRef",		"Cell", GetNthRef));
		// VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetWaterLevel),	TESObjectCELL, float>								("GetWaterLevel",	"Cell", GetWaterLevel));

		return true;
	}
}