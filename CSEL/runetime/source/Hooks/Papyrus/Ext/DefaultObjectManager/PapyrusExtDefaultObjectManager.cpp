#include "../DefaultObjectManager/PapyrusExtDefaultObjectManager.h"

#include "../../../../../../source/B/BSFixedString.h"
#include "../../../../../../source/N/NativeFunction.h"
#include "../../../../../../source/B/BGSDefaultObjectManager.h"
#include "../../../../../../source/T/TESForm.h"
#include "../../../../../../source/D/DefaultObjectList.h"

namespace PapyrusExtDefaultObjectManager
{
	// I really hate doing this...
	using namespace ConsoleRE;

	void SetForm(BGSDefaultObjectManager * objectManager, BSFixedString keySearch, TESForm * form)
	{
		if (objectManager) 
		{
			uint32_t size = strlen(keySearch.m_data);
			if (size == 4) 
			{
				uint32_t key = std::toupper(keySearch.m_data[3]) << 24 | std::toupper(keySearch.m_data[2]) << 16 | std::toupper(keySearch.m_data[1]) << 8 | std::toupper(keySearch.m_data[0]);

				DefaultObjectList * defaultList = DefaultObjectList::GetSingleton();
				if (defaultList)
				{
					for (uint32_t i = 0; i < 0x15B; i++)
					{
						if (key == defaultList->Unk00[i].Unk0C)
						{
							objectManager->objects[i] = form;
						}
					}
				}
			}
		}
	}

	TESForm * GetForm(BGSDefaultObjectManager * objectManager, BSFixedString keySearch)
	{
		if (!objectManager)
			return NULL;

		uint32_t size = strlen(keySearch.m_data);
		if (size != 4) 
		{
			return NULL;
		}

		uint32_t key = toupper(keySearch.m_data[3]) << 24 | toupper(keySearch.m_data[2]) << 16 | toupper(keySearch.m_data[1]) << 8 | toupper(keySearch.m_data[0]);

		DefaultObjectList * defaultList = DefaultObjectList::GetSingleton();
		if (defaultList)
		{
			for (uint32_t i = 0; i < 0x15B; i++)
			{
				if (key == defaultList->Unk00[i].Unk0C)
				{
					return objectManager->objects[i];
				}
			}
		}

		return NULL;
	}

	bool RegisterDefaultObjectManager(ConsoleRE::BSScript::Internal::VirtualMachine* VM)
	{
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(GetForm), BGSDefaultObjectManager, TESForm*, BSFixedString>		("GetForm", "DefaultObjectManager", GetForm));
		VM->RegisterFunction(new BSScript::NativeFunction <false, NFDLSE(SetForm), BGSDefaultObjectManager, void, BSFixedString, TESForm*>	("SetForm", "DefaultObjectManager", SetForm));
		
		return true;
	}
}