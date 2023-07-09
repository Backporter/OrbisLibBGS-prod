#include "../../../OrbisUtil/include/Relocation.h"

#include "../E/ExtraMissingLinkedRefIDs.h"

#include "../B/BGSKeyword.h"
#include "../T/TESObjectREFR.h"

namespace ConsoleRE
{
	TESObjectREFR* ExtraMissingLinkedRefIDs::GetLinkedRef(BGSKeyword* a_keyword)
	{
		for (auto& entry : entries) 
		{
			if (entry.keyword == a_keyword) 
			{
				auto objRef = ConsoleRE::TESForm::GetFormFromID(entry.linkedRefID);
				return objRef ? objRef->AsReference() : nullptr;
			}
		}
		return nullptr;
	}
}