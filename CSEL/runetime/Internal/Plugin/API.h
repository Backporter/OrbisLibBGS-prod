#pragma once

// Trampoline::Trampoline
#include "../../../../OrbisUtil/include/Mutex.h"
#include "../../../../OrbisUtil/include/Trampoline.h"

#include "../Interfaces/MessagingInterface/MessagingInterface.h"
#include "../Interfaces/PapyrusInterface/PapyrusInterface.h"
#include "../Interfaces/QueryInterface/QueryInterface.h"
#include "../Interfaces/ScaleformInterface/ScaleformInterface.h"
#include "../Interfaces/SerializationInterface/SerializationInterface.h"
#include "../Interfaces/TaskInterface/TaskInterface.h"
#include "../Interfaces/TrampolineInterface/TrampolineInterface.h"

//
#include "../../../Build/Flags.h"
#include "../../../EXTERNAL/SKSE/SKSE.h"
//

#include <mutex>
#include <shared_mutex>
#include <functional>
#include <memory>

namespace API
{
	void initialize(Interface::QueryInterface* a_interface);
	void RegisterForAPIInitEvent(std::function<void()> a_func);

	size_t GetPluginHandle();
	
	Interface::ScaleformInterface*     GetScaleformInterface();
	Interface::PapyrusInterface*       GetPapyrusInterface();
	Interface::SerializationInterface* GetSerializationInterface();
	Interface::TaskInterface*          GetTaskInterface();
	Interface::TrampolineInterface*    GetTrampolineInterface();
	Interface::MessagingInterface*     GetMessagingInterface();

	ConsoleRE::BSTEventSource<SKSE::ModCallbackEvent>*  GetModCallbackEventSource();
	ConsoleRE::BSTEventSource<SKSE::CameraEvent>*       GetCameraEventSource();
	ConsoleRE::BSTEventSource<SKSE::CrosshairRefEvent>* GetCrosshairRefEventSource();
	ConsoleRE::BSTEventSource<SKSE::ActionEvent>*       GetActionEventSource();
	ConsoleRE::BSTEventSource<SKSE::NiNodeUpdateEvent>* GetNiNodeUpdateEventSource();

	xUtilty::Trampoline& GetTrampoline();

	void AllocateTrampoline(size_t a_size, bool a_tryRerserve = true);
}