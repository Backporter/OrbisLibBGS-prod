#pragma once

#include "../../../../../OrbisUtil/include/Relocation.h"
#include "../../../../../OrbisUtil/include/INIHandler.h"
#include "../../../../../OrbisUtil/include/Logger.h"
#include "../../../../../OrbisUtil/include/Macro.h"
#include "../../../../../OrbisUtil/include/MessageHandler.h"
#include "../../../../../OrbisUtil/include/SystemWrapper.h"

#if defined(__ORBIS__) || defined (__OPENORBIS__) || defined(PLATFORM_PS4)
#include "../../../../source/B/BSOrbisSaveDataSystemUtility.h"
#endif

#include "../../../../source/B/BGSSaveLoadManager.h"
#include "../../../../source/T/TESQuest.h"

namespace SaveGame
{
	namespace New
	{	
		bool NewGame(ConsoleRE::TESQuest* a_this, bool& a_result, bool a_startNow);
	}
	
	namespace Save
	{
		using FileType	= ConsoleRE::BSOrbisSaveDataSystemUtility::FileType;
		using func_t	= void(ConsoleRE::BGSSaveLoadManager*, FileType*);

		extern Relocation<func_t*>		Save_Func;
		extern Relocation<uintptr_t>	savehooktarget;

		void SaveGame(ConsoleRE::BGSSaveLoadManager* a_this, FileType* buf);
	}
	
	namespace Load
	{
		using FileType	= ConsoleRE::BSOrbisSaveDataSystemUtility::FileType;
		using func_t	= bool(ConsoleRE::BGSSaveLoadManager*, FileType*, uint32_t, uint32_t, void*);

		extern Relocation<func_t*>		Load_Fun;
		extern Relocation<uintptr_t>	loadhooktarget;
	
		bool LoadGame(ConsoleRE::BGSSaveLoadManager* a_this, FileType* a_unk2, uint32_t a_unk3, uint32_t a_unk4, void* a_unk5);
	}

	namespace Delete
	{
		using FileType	= ConsoleRE::BSOrbisSaveDataSystemUtility::FileType;
		using func_t	= void(ConsoleRE::BGSSaveLoadManager*, FileType*);

		extern Relocation<func_t*>		Delete_Fun;
		extern Relocation<uintptr_t>	deletehooktarget;

		void DeleteGame(ConsoleRE::BGSSaveLoadManager* a_this, FileType* a_unk2);
	}

	namespace Process
	{
		using func_t = void(ConsoleRE::BGSSaveLoadManager*);

		extern Relocation<func_t*>		ProcessQueue_Rel;
		extern Relocation<uintptr_t>	processhooktarget;

		void SetLoadState(const char* a_str);
		void SetSaveState(const char* a_str);

		void ProcessQueue(ConsoleRE::BGSSaveLoadManager* a_this);
	}

	namespace Logs
	{
		extern Relocation<uintptr_t> HookTarget;

		extern Relocation<int(*)(char*, size_t, const char*)> func;
		
		int strcpy_s(char* dest, size_t destsz, const char* src);
	}
}