#include "QueryInterface.h"

#include "../MessagingInterface/MessagingInterface.h"
#include "../PapyrusInterface/PapyrusInterface.h"
#include "../QueryInterface/QueryInterface.h"
#include "../ScaleformInterface/ScaleformInterface.h"
#include "../SerializationInterface/SerializationInterface.h"
#include "../SerializationInterface/Serialization/Serialization.h"
#include "../TaskInterface/TaskInterface.h"
#include "../TrampolineInterface/TrampolineInterface.h"

#include "../../PluginManger.h"
#include "../../../Version.h"

#include "../../../../Build/Flags.h"

#if USE_SKSE_ADDON
#include "../../../../EXTERNAL/SKSE/SKSE.h"
#endif

// 
static Interface::PapyrusInterface			g_PapyyrusInterface			= { };
static Interface::TaskInterface				g_TaskInterface				= { };
static Interface::ScaleformInterface		g_ScaleformInterface		= { };
static Interface::MessagingInterface		g_MessagingInterface		= { };
static Interface::TrampolineInterface		g_TrampolineInterface		= { };
static Interface::SerializationInterface	g_SerializationInterface	= { };

namespace Interface
{
	//
	void* InternalQueryInterfaceFromID(int32_t a_interfaceType)
	{
		switch (a_interfaceType)
		{
		case PapyrusInterface::TypeID:
			return (void*)&g_PapyyrusInterface;
		case TaskInterface::TypeID:
			return (void*)&g_TaskInterface;
		case ScaleformInterface::TypeID:
			return (void*)&g_ScaleformInterface;
		case MessagingInterface::TypeID:
			return (void*)&g_MessagingInterface;
		case TrampolineInterface::TypeID:
			return (void*)&g_TrampolineInterface;
		case SerializationInterface::TypeID:
			return (void*)&g_SerializationInterface;
		default:
			return 0;
		}
	}
	//

	size_t	QueryInterface::GetModuleVersion()		{ return CSEL_VERSION_UINT32; }
	int		QueryInterface::GetInterfaceVersion()	{ return Version; }
	size_t	QueryInterface::QueryHandle()			{ return Internal::PluginManger::QueryPluginHandle(); }

	void*	QueryInterface::QueryInterfaceFromID(uint32_t a_interfaceType)
	{
		return InternalQueryInterfaceFromID(a_interfaceType);
	}

	void* QueryInterface::QueryEventSource(uint32_t a_DispatcherType)
	{
		switch (a_DispatcherType)
		{
#if USE_SKSE_ADDON
		case Interface::MessagingInterface::EventSourceType::kModEvent:
			return (void*)SKSE::ModCallbackEventDispatcher::GetSingleton();
		case Interface::MessagingInterface::EventSourceType::kCameraEvent:
			return (void*)SKSE::CameraEventDispatcher::GetSingleton();
		case Interface::MessagingInterface::EventSourceType::kCrosshairEvent:
			return (void*)SKSE::CrosshairRefDispatcher::GetSingleton();
		case Interface::MessagingInterface::EventSourceType::kActionEvent:
			return (void*)SKSE::ActionEventDispatcher::GetSingleton();
		case Interface::MessagingInterface::EventSourceType::kNiNodeUpdateEvent:
			return (void*)SKSE::NinodeUpdateDispatcher::GetSingleton();
#endif
		default:
			return 0;
		}
	}

}