#include "SaveLoad.h"

#include "../../../../../OrbisUtil/include/Mutex.h"

#include "../../../Internal/PluginManger.h"

#include "../../../../source/S/SkyrimVM.h"

namespace SaveGame
{
	namespace New
	{	
		bool NewGame(ConsoleRE::TESQuest* a_this, bool& a_result, bool a_startNow)
		{
			auto ret = a_this->EnsureQuestStarted(a_result, a_startNow);

			Internal::PluginManger::DispatchMessageToListener(0, Interface::MessagingInterface::kNewGame, 0, 0, 0);
			return ret;
		}
	}
	
	namespace Save
	{
		Relocation<func_t*>		Save_Func("", 0x669E70);
		Relocation<uintptr_t>	savehooktarget("", 0x677D52);
	
		void SaveGame(ConsoleRE::BGSSaveLoadManager* a_this, FileType* buf)
		{
			const char* SaveGameName = *reinterpret_cast<const char **>(reinterpret_cast<uintptr_t>(buf) + 0xBA8);
			if (!SaveGameName)
			{
				SaveGameName = "";
			}

			Internal::PluginManger::DispatchMessageToListener(0, Interface::MessagingInterface::kSave, (void*)SaveGameName, strlen(SaveGameName), 0);
			Save_Func(a_this, buf);
			
			//
			xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kInfo, "Executed SaveGame::Save::SaveGame");
		}
	}
	
	namespace Load
	{
		Relocation<func_t*>		Load_Fun("", 0x66A860);
		Relocation<uintptr_t>	loadhooktarget("", 0x6791D7);
	
		bool LoadGame(ConsoleRE::BGSSaveLoadManager* a_this, FileType* buf, uint32_t a_unk3, uint32_t a_unk4, void* a_unk5)
		{
			const char* SaveGameName = *reinterpret_cast<const char **>(reinterpret_cast<uintptr_t>(buf) + 0xBA8);
			if (!SaveGameName)
			{
				SaveGameName = "";
			}

			//
			xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).Lock();
			Internal::PluginManger::DispatchMessageToListener(0, Interface::MessagingInterface::kLoading, (void*)SaveGameName, strlen(SaveGameName), 0);
			auto ret = Load_Fun(a_this, buf, a_unk3, a_unk4, a_unk5);
			Internal::PluginManger::DispatchMessageToListener(0, Interface::MessagingInterface::kLoaded, &ret, sizeof(bool*), 0);
			xUtilty::Mutex::GetSingleton(xUtilty::Mutex::kGame).Unlock();

			if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->ClearInvalidRegistrations)
			{
				auto vm = ConsoleRE::SkyrimVM::GetSingleton();
				uint32_t count = vm ? vm->ClearInvalidRegistrations() : 0;
				if (count > 0)
				{
					xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kInfo, "ClearInvalidRegistrations: Removed %d invalid OnUpdate registration(s)", count);
				}
			}

			return ret;
		}
	}

	namespace Delete
	{
		Relocation<func_t*>		Delete_Fun("", 0x67E240);
		Relocation<uintptr_t>	deletehooktarget("", 0xA8B083);

		void DeleteGame(ConsoleRE::BGSSaveLoadManager* a_this, FileType* a_unk2)
		{
			return Delete_Fun(a_this, a_unk2);
		}
	}

	namespace Process
	{
		Relocation<func_t*>		ProcessQueue_Rel("", 0x67C9C0);
		Relocation<uintptr_t>	processhooktarget("", 0x6A7640 + 0x70);

		bool g_save = false;
		bool g_load = false;
		std::string g_savename;
		std::string g_loadname;

		void SetLoadState(const char* a_str)
		{
			g_load = true;
			g_loadname = a_str;
		}

		void SetSaveState(const char* a_str)
		{
			g_save = true;
			g_savename = a_str;
		}
		
		void ProcessQueue(ConsoleRE::BGSSaveLoadManager* a_this)
		{
			ProcessQueue_Rel(a_this);

			if (g_save && g_load)
			{
				xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kModuleLog)->Write(xUtilty::Log::logLevel::kWarning, "Save & Load Requested, Ignoring Both");
			}
			else if (g_save)
			{
				a_this->Save(g_savename.c_str());
			}
			else if (g_load)
			{
				a_this->Load(g_loadname.c_str());
			}

			g_save = false;
			g_load = false;

			g_savename.clear();
			g_loadname.clear();
		}
	}

	namespace Logs
	{
		Relocation<uintptr_t> HookTarget("", 0x674152);
		Relocation<int(*)(char*, size_t, const char*)> func;

		int strcpy_s(char* dest, size_t destsz, const char* src)
		{
			auto ret = func(dest, destsz, src);

			//
			xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kInfo, "BGSSaveLoadManager Wrote:\n \"%s\"", dest);

			return ret;
		}
	}
}