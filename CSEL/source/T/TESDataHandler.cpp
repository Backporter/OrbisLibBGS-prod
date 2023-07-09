#include "../T/TESDataHandler.h"

#include "../../../OrbisUtil/include/Relocation.h"

#include "../T/TESFile.h"
#include "../T/TESForm.h"

namespace ConsoleRE
{
	TESDataHandler*	TESDataHandler::GetSingleton()
	{
		Relocation<TESDataHandler**> Singleton("", 0x20BEC50);
		return *Singleton;
	}

	uint32_t TESDataHandler::LoadScripts()
	{
		using func_t = uint32_t(TESDataHandler* const);
		Relocation<func_t*> func("", 0xBDE60);
		return func(this);
	}

	TESForm* TESDataHandler::LookupForm(uint32_t a_localFormID, const char* a_modName)
	{
		auto file = LookupModByName(a_modName);
		if (!file || file->Unk478 == 0xFF)
		{
			return nullptr;
		}

		uint32_t formID = file->Unk478 << (3 * 8);
		formID += file->Unk47A << ((1 * 8) + 4);
		formID += a_localFormID;

		return TESForm::GetFormFromID(formID);
	}

	//
	TESFile* TESDataHandler::LookupModByName(const char* a_modName)
	{
		for (auto file : Unk908)
		{
			if (!strcasecmp(file->fileName, a_modName))
			{
				return file;
			}
		}

		return nullptr;

	}

	uint8_t	TESDataHandler::GetModIndex(const char* a_modName)
	{
		auto mod = LookupModByName(a_modName);
		return mod ? mod->Unk478 : NULL;
	}

	TESFile* TESDataHandler::LookupLoadedModByName(const char* a_modName)
	{
		for (auto& file : Unk918)
		{
			if (!strcasecmp(file->fileName, a_modName))
			{
				return file;
			}
		}

		return nullptr;
	}

	TESFile* TESDataHandler::LookupLoadedModByIndex(uint8_t a_index)
	{
		for (auto& file : Unk918)
		{
			if (file->Unk478 == a_index)
			{
				return file;
			}
		}

		return nullptr;
	}

	uint8_t	TESDataHandler::GetLoadedModIndex(const char* a_modName)
	{
		auto mod = LookupLoadedModByName(a_modName);
		return mod ? mod->Unk478 : NULL;
	}

	TESFile* TESDataHandler::LookupLoadedLightModByName(const char* a_modName)
	{
		for (auto& smallFile : Unk928)
		{
			if (!strcasecmp(smallFile->fileName, a_modName))
			{
				return smallFile;
			}
		}

		return nullptr;
	}

	TESFile* TESDataHandler::LookupLoadedLightModByIndex(uint16_t a_index)
	{
		for (auto& smallFile : Unk928)
		{
			if (smallFile->Unk47A == a_index)
			{
				return smallFile;
			}
		}

		return nullptr;
	}

	uint16_t TESDataHandler::GetLoadedLightModIndex(const char* a_modName)
	{
		auto mod = LookupLoadedLightModByName(a_modName);
		return mod ? mod->Unk47A : NULL;
	}

	bool TESDataHandler::IsGeneratedID(uint32_t a_formID)
	{
		return a_formID >= 0xFF000000;
	}

	BSTArray<TESForm*>&	TESDataHandler::GetFormArray(uint32_t a_formType) 
	{ 
		return FormsArray[a_formType]; 
	}

	ObjectRefHandle TESDataHandler::CreateReferenceAtLocation(TESBoundObject* a_base, const NiPoint3& a_location, const NiPoint3& a_rotation, TESObjectCELL* a_targetCell, TESWorldSpace* a_selfWorldSpace, TESObjectREFR* a_alreadyCreatedRef, BGSPrimitive* a_primitive, const ObjectRefHandle& a_linkedRoomRefHandle, bool a_forcePersist, bool a_arg11)
	{
		using func_t = decltype(&TESDataHandler::CreateReferenceAtLocation);
		Relocation<func_t> FN("", 0xBE680);
		return FN(this, a_base, a_location, a_rotation, a_targetCell, a_selfWorldSpace, a_alreadyCreatedRef, a_primitive, a_linkedRoomRefHandle, a_forcePersist, a_arg11);
	}	
}