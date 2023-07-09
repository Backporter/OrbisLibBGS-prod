// not needed here, but needs to be defined.
void SetPath(const char** a_log, const char** a_mira, const char** a_data, const char** a_appdata) { }

#if PLATFORM_ORBIS && PROJECT_TYPE_RUNETIME
#include "../../OrbisUtil/include/Types.h"
static_assert(sizeof(wchar_t_t) == sizeof(uint16_t), "WCHAR_T SIZE MISMATCH");

#include "../runetime/Internal/PluginManger.h"
#include "../runetime/source/Debugging/Debug.h"
#include "../runetime/source/Enderal/Enderal.h"
#include "../runetime/source/Hooks/Hooks_Global.h"
#include "../runetime/source/Hooks/Hooks_Orbis.h"
#include "../runetime/source/C/ConsoleCommandEmulator.h"
#include "../runetime/Internal/Interfaces/SerializationInterface/Serialization/Serialization.h"

#include "../../OrbisUtil/include/OffsertManger.h"
#include "../../OrbisUtil/include/OrbisSFOHandler.h"
#include "../../OrbisUtil/include/Trampoline.h"
#include "../../OrbisUtil/include/Macro.h"
#include "../../OrbisUtil/include/INIHandler.h"
#include "../../OrbisUtil/include/Logger.h"
#include "../../OrbisUtil/include/DialogueManger.h"
#include "../../OrbisUtil/include/RelocationManager.h"
#include "../../OrbisUtil/include/OffsertManger.h"

#include "../runetime/source/Hooks/Hooks_Development.h"

#include "../../OrbisUtil/include/PersistentSocketConnection.h"

#include "Internal\PluginManger.h"

#if defined(__OPENORBIS__)
#include <orbis/Rtc.h>
#include <orbis/libkernel.h>
typedef TimeTable SceRtcDateTime;
#elif defined(__ORBIS__)
#include <rtc.h>
#include <kernel.h>
#include <wchar.h>
#include <string>
#endif

bool ConfirmValidTitle(const char* a_title, const char* a_appverSTR)
{
	if (!a_title || !a_appverSTR)
		return false;

	// compare the name to Skyrim OR Enderal: Forgotten Stories
	if (strncasecmp(a_title, "Skyrim", 6) != 0 && strncasecmp(a_title, "Enderal", 7) != 0)
	{
		xUtilty::Notify("Not Skyrim/Enderal!... exiting(got %s)", a_title);
		return false;
	}

	return true;
}

EXPORT void ConsoleLibInitialize()
{
	auto s_sfo = OrbisSFOHandler::sfo_parser::GetSingleton();
	auto s_title = s_sfo->GetKeySTR("TITLE");
	auto s_appverSTR = s_sfo->GetKeySTR("APP_VER");

	if (!ConfirmValidTitle(s_title, s_appverSTR))
		return;

	if (!xUtilty::Trampoline::get(xUtilty::Trampoline::kBranch).create(1024 * 64, 0, nullptr) || !xUtilty::Trampoline::get(xUtilty::Trampoline::kLocal).create(1024 * 64, 0xDEADBEEF, nullptr))
	{
		xUtilty::Notify("[Fatal] Failed to allocate memory pool for trampolines");
		return;
	}

	SceRtcDateTime now;
	xUtilty::SystemWrapper::UpdateRTC(&now);

	xUtilty::Log::GetSingleton()->Write(xUtilty::Log::logLevel::kInfo, "Welcome, App Title \"%s\", App Versiion \"%s\" Firmware Version \"%lx\", Current RTC \"%d:%d:%d:%d:%d\"", s_title, s_appverSTR, xUtilty::SystemWrapper::GetFirmwareVersion(nullptr), now.month, now.day, now.year, now.hour, now.minute);
	Internal::PluginManger::GetSingleton()->InitializePlugins();

	Runetime::Hooks::ApplyOrbisHooks();
	Runetime::Hooks::ApplyVersionHook();
	Runetime::Hooks::ApplyPapyrusHook();

	Runetime::Hooks::ApplyVMLoadGameHook();
	Runetime::Hooks::ApplyVMReverGameHook();
	Runetime::Hooks::ApplyVMSaveGameHook();
	Runetime::Hooks::ApplyVMFormDeletionHook();
	Runetime::Hooks::ApplySaveGameHistorySaver();

	Runetime::Hooks::ApplyFormLoadHook();
	Runetime::Hooks::ApplyScaleFormHook2();
	Runetime::Hooks::ApplyGFxHook();
	Runetime::Hooks::ApplyPlayerControlsHook();
	Runetime::Hooks::ApplyLogHook();
	Runetime::Hooks::ApplyUIQueue();
	Runetime::Hooks::ApplyEquipmentHook();
	Runetime::Hooks::ApplyRenderTargetHook();
	Runetime::Hooks::ApplyCameraStateHook();
	Runetime::Hooks::ApplyStandardItemDataHook();
	Runetime::Hooks::ApplyMagicItemDataHook();
	Runetime::Hooks::ApplySmithingMenuSetHook();
	Runetime::Hooks::ApplyCraftingSubMenuSetHook();
	Runetime::Hooks::ApplyAlchemyMenuSetHook();
	Runetime::Hooks::ApplyEnchantConstructMenuSetHook();
	Runetime::Hooks::ApplyAlchemyMenuIndexFixUpHook();
	Runetime::Hooks::ApplyItemFavoritesMenuSetHook();
	Runetime::Hooks::ApplyMagicFavoritesMenuSetHook();
	Runetime::Hooks::ApplyVampireFavoritesMenuSetHook();

#if true
	Runetime::Hooks::ApplyContainerCategorizationHook();
	Runetime::Hooks::ApplyMapMenuMouseWheelHook();
#endif

	Runetime::Hooks::ApplyNewGameHook();
	Runetime::Hooks::ApplySaveGameHook();
	Runetime::Hooks::ApplyLoadGameHook();
	Runetime::Hooks::ApplyDeleteGameHook();
	Runetime::Hooks::ApplySaveQueueProcessorHook();
	Runetime::Hooks::ApplyTaskPoolHook();
	Runetime::Hooks::ApplyHandleHooks();

	Runetime::Hooks::Init();

	Serialization::SerializationHandler::RegisterInternal();

	Runetime::Debug::Init();
	Runetime::Enderal::Init();

	goto exit;

exit:
	if (xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions()->SpawnCCE)
		Runetime::CCE::GetSingleton()->StartCCET();

	Internal::PluginManger::DispatchMessageToListener(0, Interface::MessagingInterface::kMAIN_LOADED, 0, 0, 0);
}

EXPORT int module_start(size_t argc, const void* argv)
{
	//
	xUtilty::RelocationManager::RelocationManager();

	//
	xUtilty::INIHandler::INIHandler::GetSingleton()->Parse();
	
	//
	auto INI = xUtilty::INIHandler::INIHandler::GetSingleton()->GetINIOptions();
	if (INI->PathType == xUtilty::FileSystem::Net)
	{
		xUtilty::Log::GetSingleton()->Connect((char*)INI->Path);
	}
	else
	{
		xUtilty::Log::GetSingleton()->OpenRelitive(INI->PathType, (char*)INI->Path);
	}

	if (INI->IsDebugMode)
	{
		xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kInputOutputLog)->OpenRelitive(INI->PathType, (char*)"OSEL/IO.txt");
	}

	if (INI->EnableVirtualMachineLog)
	{
		xUtilty::Log::GetSingleton(xUtilty::Log::LoggerInstance::kVirtualMachineLog)->OpenRelitive(INI->PathType, (char*)"OSEL/VM.txt");
	}
	
	// not using mira?, init.
	if (INI->UseModuleStartAsEntryPoint)
	{
		ConsoleLibInitialize();
	}

	return 0;
}

EXPORT int module_stop(size_t argc, const void* argv) { return 0; }

// Mira's trainer entry point.
EXPORT bool trainer_load()
{
	//
	ConsoleLibInitialize();

	return true;
}

#elif PLATFORM_NX
#endif